#include "Project.h"
#include "GuiControl.h"         // r/w to widgets
#include "ProgramState.h"       // write programState
#include "MathControl.h"        // r/w math data
#include "PlotFrame.h"          // drawing/ deleting plots
#include "StrGrid.h"            // StrList typedef

// constants
const String Project::statusVars_sec = "statusVars";    // sections from ini
const String Project::edits_sec = "edits";
const String Project::labels_sec = "labels";
const String Project::ampGrid_sec = "ampGrid";
const String Project::phaseGrid_sec = "phaseGrid";
const String Project::others_sec = "otherWidgets";    //  programState_sec

const String Project::rpOutOfDate_id = "rpOutOfDate";         // identifiers from ini
const String Project::preparationOutOfDate_id = "preparationOutOfDate";
const String Project::resultExists_id = "resultExists";

const String Project::strGridPrefix_id = "file";         // string grids
const String Project::count_id = "count";

const String Project::stepRbPosition_id = "stepRbPosition";        // others
const String Project::stepRb_AntWidth_val = "antennaWidth";
const String Project::stepRb_ByHand_val = "byHand";

const String Project::calibrRbPosition_id = "calibrRbPosition";
const String Project::calibrRb_dat_val = "dat";
const String Project::calibrRb_bln_val = "bln";

const String Project::dirNameSuffix = "_data";                   // project directory name suffix

const String Project::calibrAmpEditName = "calibrAmpEdit";        // names of Edits with calibr files
const String Project::calibrPhaseEditName = "calibrPhaseEdit";

const String Project::resultFileAmp = "result_amp.dat";        // names of result-files
const String Project::resultFilePhase = "result_phase.dat";



// ---------------------------------------------------------------

void Project::OpenProjectFrom (String projectFileName)
{
// Open the given project.
// Doesn't ask qustions (questions are in Program-class).

    // STAGE 1. READING AND CHECKING THE PROJECT BEING OPENED.
    // On error, tell the user and quit the function.
    // Old project will not be affected in any way.
    // Don't forget to delete ini after it's created! (and newMath too!)


    // try to open ini- file: handle BadFileName(not .prj/.pRj/...),
    //   FileExist- and BadFormat- errors
    if (!CheckProjectFileName (projectFileName))
    {
        ShowMessage("Файл проекта должен иметь расширение .prj!");
        return;
    }
    if (!FileExists(projectFileName))
    {
        ShowMessage("Указанный файл проекта не существует!");
        return;
    }
    TIniFile* ini = new TIniFile(projectFileName);
    if (!CheckIniFileConsistency(ini))
    {
        ShowMessage("Указанный файл не является файлом проекта, либо испорчен.");
        delete ini;
        return;
    }

    // find out project data directory
    String projectDataDir = ProjectDirectoryWithSlash (projectFileName);

    // read StatusIniVars and widgetsData (we'll use its input files next step)
    WidgetsData widgetsData = ReadProjectIniForWidgets (ini,projectDataDir);
    StatusIniVars statusIniVars = ReadProjectIniForState (ini);

    // check if the input files specified exist.
    // The files include: StrGrids and CalibrationFiles (if using DAT-calibr)
    if (!CheckInputFilesExist(widgetsData))
    {
        ShowMessage("Невозможно открыть файлы данных, относящиеся к проекту.\n"
                "Возможно, удалена вся директория с файлами?");
        delete ini;
        return;
    }


    // create a new Math-object
    // If no errors occur, we'll use this object instead of the previous one.
    // If we had the result, read the data: inputs and resuls.
    Math* newMath = new Math();

    if (statusIniVars.resultExists) // need to load files
    {
        StrList ampFiles = widgetsData.ampFiles;
        StrList phaseFiles = widgetsData.phaseFiles;

        bool inputIsCorrect;
        if (widgetsData.calRbPosition == bln)
            inputIsCorrect = newMath->ReadAndReplaceInputData(ampFiles, phaseFiles, "", "", BLN);
        else if (widgetsData.calRbPosition == dat)
        {
            String ampCal = AmpCalibrFileName (widgetsData);
            String phaseCal = PhaseCalibrFileName(widgetsData);
            inputIsCorrect = newMath->ReadAndReplaceInputData(ampFiles, phaseFiles, ampCal, phaseCal, DAT);
        }
        // else error - new type of calibration.

        String ampFileFull = projectDataDir + resultFileAmp;
        String phaseFileFull = projectDataDir + resultFilePhase;
        bool resultIsCorrect =
            newMath->ReadAndRelpaceRPData(ampFileFull, phaseFileFull);

        if ((!resultIsCorrect) || (!inputIsCorrect))
        {
            ShowMessage ("Файлы данных, относящиеся к проекту, не могут быть прочитаны.");
            delete ini;
            delete newMath;
            return;
        }
    }

    // clean up
    delete ini;

    // STAGE 2. APPLYING CHANGES TO THE PROGRAM.
    // If we are here, then all the data it correct.
    // We can now close the old project and open the new one.


    // write widgets data.
    guiControl->WriteWidgetsData (widgetsData);

    // delete old Math object, re-reference the pointer to the new one
    delete math;
    math = newMath;
    newMath = NULL;

    // delete old plots, draw new ones (if results are present).
    plot->RemoveAllInputAndRP();
    plot->RemoveAllExternal();
    if (statusIniVars.resultExists)
        plot->AddAllInputAndRP();

    // write StatusIniVars and projectName  and projectChanged
    // (projectChanged goes last because other vars' change affect it).
    bool prepInModified = statusIniVars.preparationOutOfDate;
    programState->SetPreparationInputModified (prepInModified);

    bool rpInModified = statusIniVars.rpOutOfDate;
    programState->SetRPInputModified (rpInModified);

    programState->SetProjectName (projectFileName);
    programState->SetProjectModified (false);
}

// ---------------------------------------------------------------

void Project::SaveProjectTo (String projectFileName)
{
// Saves the project with a given name          
// Doesn't ask questions (questions are in Program-class).

    // check BadFileName case. on error abort.
    if (!CheckProjectFileName(projectFileName))
    {
        ShowMessage("Файл проекта должен иметь расширение .prj!");
        return;
    }

    // find out dirName (projectName_data), create (find) it, on error abort.
    String dirName = ProjectDirectoryWithSlash (projectFileName);
    if (!CreateOrFindDirectory(dirName))
    {
        ShowMessage("Невозможно создать директорию для файлов данных проекта.");
        return;
    }

    // read widgets (to read fileNames from them at the next step)
    WidgetsData widgetsData = guiControl->ReadWidgetsData();

    // Copy files to the directory and change StrGrid (and Edit) contents. on error abort.
    if (!CopyInputFiles(widgetsData,dirName))
    {
        ShowMessage("Ошибка при копировании файлов в директорию проекта");
        return;
    }

    WidgetsData widgDataNewPath = ChangeWidgetsDataPath (widgetsData, dirName);
    guiControl->WriteWidgetsData(widgDataNewPath);

    // save result-files, if any. on error abort.
    if (math->ResultExists())
    {
        String ampFullName = dirName + resultFileAmp;
        String phaseFullName = dirName + resultFilePhase;
        bool ampSaved =  math->SaveRPDataRaw(amp, ampFullName);
        bool phaseSaved = math->SaveRPDataRaw(phase, phaseFullName);
        if ((!ampSaved) || (!phaseSaved))
        {
            ShowMessage ("Ошибка при сохранении файлов резульатата");
            return;
        }
    }

    // generate and save ini-file, on error abort.
    // ini includes: widgets, StatusIniVars
    TIniFile* ini = new TIniFile(projectFileName);

    WriteProjectIniForWidgets (ini, widgDataNewPath);

    StatusIniVars statusIniVars;
    statusIniVars.rpOutOfDate = programState->GetRPInputModified();
    statusIniVars.preparationOutOfDate = programState->GetPreparationInputModified();
    statusIniVars.resultExists = math->ResultExists();
    WriteProjectIniForState (ini, statusIniVars);

    // update StatusIniVars bools, projectName and projectExist
    programState->SetProjectName(projectFileName);
    programState->SetProjectModified(false);
}

// ---------------------------------------------------------------

void Project::NewProject ()
{
// Creates new project, deleting all RAM data from old project.
// Doesn't ask questions (questions are in Program-class).

    // delete input, RP and external data and their plots
    math->RemoveInputAndRPData();
    math->RemoveAllExternalData();
    plot->RemoveAllInputAndRP();
    plot->RemoveAllExternal();

    // set widgets to default
    guiControl->SetWidgetsToDefault();

    // update StatusIniVars bools, projectName and projectExist
    programState->SetPreparationInputModified(false);
    programState->SetRPInputModified(false);
    programState->SetProjectName("");
    programState->SetProjectModified(false);
}





// -------------------- PRIVATE ROUTINES -------------------------



// -------------------------- TIniFile ---------------------------

Project::StatusIniVars Project::ReadProjectIniForState (TIniFile* ini)
{
// Reading TIniFile's StatusIniVars section
// On errors reads false everywhere.

    StatusIniVars state;

    state.rpOutOfDate =
        ini->ReadBool(statusVars_sec, rpOutOfDate_id, false);

    state.preparationOutOfDate =
        ini->ReadBool(statusVars_sec, preparationOutOfDate_id, false);

    state.resultExists =
        ini->ReadBool(statusVars_sec, resultExists_id, false);

    return state;
}
// ---------------------------------------------------------------

void Project::WriteProjectIniForState (TIniFile* ini, StatusIniVars state)
{
// writing StatusIniVars to ini-file. Ini must exist and be initialized.

    // clean the StatusIniVars section
    ini->EraseSection(statusVars_sec);
    // write bools
    ini->WriteBool(statusVars_sec, rpOutOfDate_id, state.rpOutOfDate);
    ini->WriteBool(statusVars_sec, preparationOutOfDate_id, state.preparationOutOfDate);
    ini->WriteBool(statusVars_sec, resultExists_id, state.resultExists);
}

// ---------------------------------------------------------------

WidgetsData Project::ReadProjectIniForWidgets (TIniFile* ini, String filesDirWithSlash)
{
// Reading TIniFile's WidgetsData section
// On errors reads false (or "") everywhere.
// StrGrids' values are prefixed with 'filesDirWithSlash'.
// So are calibr Edits (if DAT and if !="", otherwise writes "").

    WidgetsData data;

    // reading strGrids: count (a/ph) = amount of entries, then reading them:
    // name = pefix+ "1","2", etc.

    // amplitude
    int countAmp =
        ini->ReadInteger (ampGrid_sec, count_id, 0);
    for (int i=0; i<countAmp; i++)
    {
        String fieldName, fieldValue, resultValue;
        fieldName = strGridPrefix_id + IntToStr(i);
        fieldValue = ini->ReadString (ampGrid_sec, fieldName, "");
        resultValue = filesDirWithSlash + fieldValue;
        data.ampFiles.push_back (resultValue);
    }
    // phase
    int countPhase =
        ini->ReadInteger (phaseGrid_sec, count_id, 0);
    for (int i=0; i<countPhase; i++)
    {
        String fieldName, fieldValue, resultValue;
        fieldName = strGridPrefix_id + IntToStr(i);
        fieldValue = ini->ReadString (phaseGrid_sec, fieldName, "");
        resultValue = filesDirWithSlash + fieldValue;
        data.phaseFiles.push_back (resultValue);
    }

    // reading others: stepRbPosition and calibrRbPosition - RadioButtons
    String stepRbString =
        ini->ReadString (others_sec, stepRbPosition_id, "");
    if (stepRbString == stepRb_AntWidth_val)
        data.stepRbPosition = basedOnAntennaWidth;
    else if (stepRbString == stepRb_ByHand_val)
        data.stepRbPosition = byHand;
    else                                // here it's possible to report error
        data.stepRbPosition = byHand;

    String calibrRbString =
        ini->ReadString (others_sec, calibrRbPosition_id, "");
    if (calibrRbString == calibrRb_bln_val)
        data.calRbPosition = bln;
    else if (calibrRbString == calibrRb_dat_val)
        data.calRbPosition = dat;
    else                                // here it's possible to report error
        data.calRbPosition = bln;

    // reading edits (scanning all StringList of names)
    // For calibrAmp/PhaseEditName-Edits prefix the path!!! (for DAT and !="")
    // the section relies on data.calRbPosition (it must be calculated here)
    int editsCount = data.editNames.size();
    for (int i=0; i<editsCount; i++)
    {
        String fieldName, fieldValue;
        fieldName = data.editNames[i];
        fieldValue = ini->ReadString(edits_sec, fieldName, "");
        String resultValue;

        if ((fieldName!=calibrAmpEditName) && (fieldName!=calibrPhaseEditName))
           resultValue = fieldValue;   // most Edits go here
        else                           // the calibr Edits
        {
            if ((data.calRbPosition == dat) && (fieldValue != ""))
                resultValue = filesDirWithSlash + fieldValue;
            else
                resultValue = "";
        }
        data.editValues.push_back (resultValue);
    }

    // reading labels (same as edits)
    int labelsCount = data.labelNames.size();
    for (int i=0; i<labelsCount; i++)
    {
        String fieldName, fieldValue;
        fieldName = data.labelNames[i];
        fieldValue = ini->ReadString(labels_sec, fieldName, "");
        data.labelValues.push_back (fieldValue);
    }

    // return the result
    return data;
}
// ---------------------------------------------------------------

void Project::WriteProjectIniForWidgets (TIniFile* ini,WidgetsData data)
{
// writing StatusIniVars to ini-file. Ini must exist and be initialized.
// StrGrid files are written without path. And calibr too (and only if using DAT).

    // clean the widget-related sections
    ini->EraseSection(ampGrid_sec);
    ini->EraseSection(phaseGrid_sec);
    ini->EraseSection(edits_sec);
    ini->EraseSection(labels_sec);
    ini->EraseSection(others_sec);

    // writing strGrids: count (a/ph) = amount of entries, then writing them
    // name = pefix+ "1","2", etc.

    // amplitude
    int countAmp = data.ampFiles.size();
    ini->WriteInteger (ampGrid_sec, count_id, countAmp);
    for (int i=0; i<countAmp; i++)
    {
        String fieldName, fieldValue, fileAndPath;
        fieldName = strGridPrefix_id + IntToStr(i);
        fileAndPath = data.ampFiles[i];
        fieldValue = ExtractFileName (fileAndPath);
        ini->WriteString (ampGrid_sec, fieldName, fieldValue);
    }
    // phase
    int countPhase = data.phaseFiles.size();
    ini->WriteInteger (phaseGrid_sec, count_id, countPhase);
    for (int i=0; i<countPhase; i++)
    {
        String fieldName, fieldValue, fileAndPath;
        fieldName = strGridPrefix_id + IntToStr(i);
        fileAndPath = data.phaseFiles[i];
        fieldValue = ExtractFileName (fileAndPath);
        ini->WriteString (phaseGrid_sec, fieldName, fieldValue);
    }

    // writing edits (scanning all StringList of names)
    //  calibrAmp/PhaseEditName-Edits are written without path (for DAT...)
    int editsCount = data.editNames.size();
    for (int i=0; i<editsCount; i++)
    {
        String fieldName, fieldValue;
        fieldName = data.editNames[i];
        fieldValue = data.editValues[i];

        String resultValue;

        if ((fieldName!=calibrAmpEditName) && (fieldName!=calibrPhaseEditName))
           resultValue = fieldValue;   // most Edits go here
        else                           // the calibr Edits
        {
            if ((data.calRbPosition == dat) && (fieldValue != ""))
                resultValue = ExtractFileName(fieldValue);
            else
                resultValue = "";
        }

        ini->WriteString(edits_sec, fieldName, resultValue);
    }

    // writing labels (same as edits)
    int labelsCount = data.labelNames.size();
    for (int i=0; i<labelsCount; i++)
    {
        String fieldName, fieldValue;
        fieldName = data.labelNames[i];
        fieldValue = data.labelValues[i];
        ini->WriteString(labels_sec, fieldName, fieldValue);
    }

    // writing others: stepRbPosition and calRbPosition - RadioButtons
    if (data.stepRbPosition == basedOnAntennaWidth)
        ini->WriteString (others_sec, stepRbPosition_id, stepRb_AntWidth_val);
    else if (data.stepRbPosition == byHand)
        ini->WriteString (others_sec, stepRbPosition_id, stepRb_ByHand_val);
    // else error. you can put an assert here.

    if (data.calRbPosition == bln)
        ini->WriteString (others_sec, calibrRbPosition_id, calibrRb_bln_val);
    else if (data.calRbPosition == dat)
        ini->WriteString (others_sec, calibrRbPosition_id, calibrRb_dat_val);
    // else error. you can put an assert here.
}
// ---------------------------------------------------------------

bool Project::CheckIniFileConsistency (TIniFile* ini)
{
// check if the basic items are present in the ini-file
// Ini-file must exist.

    bool sec1 = ini->SectionExists(statusVars_sec);
    bool sec2 = ini->SectionExists(edits_sec);
    bool sec3 = ini->SectionExists(labels_sec);
    bool sec4 = ini->SectionExists(others_sec);

    bool result = sec1 && sec2 && sec3 && sec4;

    return result;
}

// ----------------------- FILE OPERATIONS ------------------------

bool Project::CheckProjectFileName (String fileName)
{
// Check if the name is ____.prj or ___.pRj or ....

    String nameNoPath = ExtractFileName(fileName);
    if (nameNoPath.Length() <= 4) // less than ".prj" or equal
        return false;

    String ext = ExtractFileExt (fileName);
    ext = LowerCase(ext);
    if (ext == ".prj")
        return true;
    else
        return false;
}
// ---------------------------------------------------------------

bool Project::CheckInputFilesExist (WidgetsData data)
{
// Checks if the files in StringGrids exist.
// If using DAT-calibr and DAT-files are specified, also checks them.

    // iterate over Amp files
    int ampCount = data.ampFiles.size();
    for (int i=0; i<ampCount; i++)
    {
        String fileName = data.ampFiles[i];
        bool exist = FileExists(fileName);
        if (!exist) return false;
    }

    // iterate over Phase files
    int phaseCount = data.phaseFiles.size();
    for (int i=0; i<phaseCount; i++)
    {
        String fileName = data.phaseFiles[i];
        bool exist = FileExists(fileName);
        if (!exist) return false;
    }

    // check whether calibr is DAT and its edits != "".
    // in that case, check those files
    if (data.calRbPosition == dat)
    {
        String ampFile = AmpCalibrFileName(data);
        if (ampFile != "")
        {
            bool exist = FileExists(ampFile);
            if (!exist) return false;
        }

        String phaseFile = PhaseCalibrFileName(data);
        if (phaseFile != "")
        {
            bool exist = FileExists(phaseFile);
            if (!exist) return false;
        }
    }
    // no errors found
    return true;
}
// ---------------------------------------------------------------

String Project::ProjectDirectoryWithSlash (String projectFileName)
{
// Returns project directory (projectName_files) based on the file name
// Assuming that fileNameLength is more than 4.

    String fileDirWithSlash = ExtractFilePath(projectFileName);
    String onlyFileName = ExtractFileName(projectFileName);
    int nameLength = onlyFileName.Length();
    String nameWithoutExt = onlyFileName.SubString(1,nameLength-4);
    String result = fileDirWithSlash + nameWithoutExt + dirNameSuffix + "\\";
    return result;
}
// ---------------------------------------------------------------


bool Project::CreateOrFindDirectory (String dirNameWithSlash)
{
// try to find or create the directory

    if (DirectoryExists(dirNameWithSlash))
        return true;
    else
    {
        if (ForceDirectories(dirNameWithSlash))
            return true;
        else
            return false;
    }
}
// ---------------------------------------------------------------

bool Project::CopyInputFiles(const WidgetsData& data, String dir)
{
// Copy input files to the directory specified.
// Note, that they may already be there.
// Copy cal-files if using DAT-calibr and if the fileNames!="".

    // if we missed the slash at the end of the dir...
    String dirWithSlash = IncludeTrailingPathDelimiter(dir);

    // iterate over amp StrGrid. check, if the file directory is already 'dir',
    // if not - copy it to dir.
    int ampCount = data.ampFiles.size();
    for (int i=0; i<ampCount; i++)
    {
        String oldFileName = data.ampFiles[i];
        bool copied =
            CopyFileToDirWithCheck (oldFileName, dirWithSlash);
        if (!copied)
            return false;
    }

            
    // iterate over phse StrGrid. same thing.
    int phaseCount = data.phaseFiles.size();
    for (int i=0; i<phaseCount; i++)
    {
        String oldFileName = data.phaseFiles[i];
        bool copied =
            CopyFileToDirWithCheck (oldFileName, dirWithSlash);
        if (!copied)
            return false;
    }

    // check if we need the files (cal=DAT, names!="").
    // check if their dir is 'dir', then copy.
    if (data.calRbPosition == dat)
    {
        String ampFile = AmpCalibrFileName(data);
        if (ampFile != "")
        {
            bool copied =
                CopyFileToDirWithCheck (ampFile, dirWithSlash);
            if (!copied)
                return false;
        }
        String phaseFile = PhaseCalibrFileName(data);
        if (phaseFile != "")
        {
            bool copied =
                CopyFileToDirWithCheck (phaseFile, dirWithSlash);
            if (!copied)
                return false;
        }
    }

    // no errors found
    return true;
}
// ---------------------------------------------------------------

bool Project::CopyFileToDirWithCheck (String oldFileName, String newDir)
{
// Copy file 'oldFile' to dir 'newDir'.
// If file's dir is already 'newDir', just return true.

    // if we missed the slash at the end of the dir...
    String dirWithSlash = IncludeTrailingPathDelimiter(newDir);

    String oldDir = ExtractFilePath(oldFileName);
    if (oldDir == dirWithSlash)  // file is at the right place
        return true;
    else
    {
        String newFileName = dirWithSlash + ExtractFileName(oldFileName);
        bool copied = CopyFileA(oldFileName.c_str(), newFileName.c_str(), false); // false=overwrite
        if (copied)
            return true;
        else
        return false;
    }
}



// ----------------------- OTHERS ---------------------------


String Project::AmpCalibrFileName (WidgetsData data)    // the design is not perfect...
{
// find out the text of the AmpCalibration edit

    // iterate over all names. search for calibrAmpEditName
    int count = data.editNames.size();
    for (int i=0; i<count; i++)
    {
        String editName = data.editNames[i];
        if (editName == calibrAmpEditName)
            return data.editValues[i];
    }
    // if name not found return ""
    return "";
}
// ---------------------------------------------------------------

String Project::PhaseCalibrFileName (WidgetsData data)
{
// find out the text of the PhaseCalibration edit

    // iterate over all names. search for calibrPhaseEditName
    int count = data.editNames.size();
    for (int i=0; i<count; i++)
    {
        String editName = data.editNames[i];
        if (editName == calibrPhaseEditName)
            return data.editValues[i];
    }
    // if name not found return ""
    return "";
}

// ---------------------------------------------------------------
WidgetsData Project::ChangeWidgetsDataPath (const WidgetsData& widgetsData, String newDir)
{
// Changes paths to all files (in StrGrids and, if need, in 2 Edits)

    WidgetsData newWidData = widgetsData;
    String dirWithSlash = IncludeTrailingPathDelimiter(newDir);

    // iterate over all amp files
    int ampCount = widgetsData.ampFiles.size();
    for (int i=0; i<ampCount; i++)
    {
        String oldFileFull = newWidData.ampFiles[i];
        String fileNameOnly = ExtractFileName(oldFileFull);
        String newFileFull = dirWithSlash + fileNameOnly;
        newWidData.ampFiles[i] = newFileFull;
    }

    // iterate over all phase files
    int phaseCount = newWidData.phaseFiles.size();
    for (int i=0; i<phaseCount; i++)
    {
        String oldFileFull = widgetsData.phaseFiles[i];
        String fileNameOnly = ExtractFileName(oldFileFull);
        String newFileFull = dirWithSlash + fileNameOnly;
        newWidData.phaseFiles[i] = newFileFull;
    }

    // change cal-files, if need
    if (newWidData.calRbPosition == dat)
    {
        String ampFile = AmpCalibrFileName(newWidData);
        if (ampFile != "")
        {
            String fileNameOnly = ExtractFileName(ampFile);
            String newFileFull = dirWithSlash + fileNameOnly;

            // find and change Edit text to newFileFull
            int count = newWidData.editNames.size();
            for (int i=0; i<count; i++)
            {
                String editName = newWidData.editNames[i];
                if (editName == calibrAmpEditName)
                    newWidData.editValues[i] = newFileFull;
            }
        }
        String phaseFile = PhaseCalibrFileName(newWidData);
        if (phaseFile != "")
        {
            String fileNameOnly = ExtractFileName(phaseFile);
            String newFileFull = dirWithSlash + fileNameOnly;

            // find and change Edit text to newFileFull
            int count = newWidData.editNames.size();
            for (int i=0; i<count; i++)
            {
                String editName = newWidData.editNames[i];
                if (editName == calibrPhaseEditName)
                    newWidData.editValues[i] = newFileFull;
            }
        }
    }

    return newWidData;
}
