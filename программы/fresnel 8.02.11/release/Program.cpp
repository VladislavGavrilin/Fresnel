#include "Program.h"
#include "MathControl.h"
#include "GuiControl.h"
#include "PlotFrame.h"
#include "Project.h"
#include "ProgramState.h"
#include "StrGrid.h"
#include "Settings.h"

#include "MainForm.h"

#include <assert>

//---------------------------- CONSTRUCTOR ----------------------------------

Program::Program()
{
// Initialize saveDialog.

    saveDialog = new TSaveDialog(NULL);
    saveDialog->Options << ofOverwritePrompt;
    saveDialog->Title = "Задайте имя файла";
    saveDialog->Filter = "Файлы данных (*.dat)|*.dat|Все файлы|*.*";
    saveDialog->DefaultExt = "dat";

    saveProjDialog = new TSaveDialog(NULL);
    saveProjDialog->Options << ofOverwritePrompt;
    saveProjDialog->Title = "Задайте имя проекта";
    saveProjDialog->Filter = "Файлы проектов (*.prj)|*.prj|Все файлы|*.*";
    saveProjDialog->DefaultExt = "prj";

    openProjDialog = new TOpenDialog(NULL);
    openProjDialog->Filter = "Файлы проектов (*.prj)|*.prj|Все файлы|*.*";
    openProjDialog->Options.Clear();
    openProjDialog->Options << ofHideReadOnly << ofFileMustExist << ofEnableSizing;
    openProjDialog->Title = "Укажите файл проекта";

}

Program::~Program()
{
    delete saveDialog;
    delete saveProjDialog;
    delete openProjDialog;
}



//--------------------------- PUBLIC ROUTINES -------------------------------

void Program::StartUp(String exeFileName, String projFileName)
{
// The startup code: read ini, open last project or a file passed in command line.
// The Form and global objects must exist.

    // find out ini-file name, store it to private field
    String dir = ExtractFilePath(exeFileName);
    String iniFileName = dir + "fresnel.ini";
    Program::iniFile = iniFileName;

    // apply ini-file settings
    settings->ReadAndApplyGraphicSettings (iniFile);

    // check if projFileName exists. no=> read lastProject
    String loadProject;
    if (projFileName != "")
        loadProject = projFileName;
    else
        loadProject = settings->ReadLastProject(iniFile);

    // if we have a project to load, do it. else, create new one.
    project->NewProject();
    if (loadProject != "")
        project->OpenProjectFrom(loadProject);

}
//---------------------------------------------------------------------------

bool Program::BeforeExit()
{
// It's called in Form->onClose.
// If return true, close the app. If false, cancel closing.

    // check if we have unsaved changes
    bool hasChanges = programState->GetProjectModified();

    // ask if the user wants to save changes.
    if (hasChanges)
    {
        bool projExists = programState->GetProjectExists();
        // if project exists
        if (projExists)
        {
            bool notCancelled = CurrProjChangedQuestion();
            if (!notCancelled)     // cancelled
                return false;
        }

        // if project doesn't exist
        else
        {
            bool notCancelled = NewProjChangedQuestion();
            if (!notCancelled)     // cancelled
                return false;
        }

    }



    // if changes saved/cancelled or no changes, save ini and return true.
    String currProject = programState->GetProjectName();
    settings->WriteSettings(currProject, iniFile);
    return true;                      
}
//---------------------------------------------------------------------------

void Program::NewProject()
{
// A routine for NewProject button.

    // check if we have unsaved changes
    bool hasChanges = programState->GetProjectModified();

    // ask if the user wants to save changes.
    if (hasChanges)
    {
        bool projExists = programState->GetProjectExists();
        // if project exists
        if (projExists)
        {
            bool notCancelled = CurrProjChangedQuestion();
            if (!notCancelled)     // cancelled
                return;
        }

        // if project doesn't exist
        else
        {
            bool notCancelled = NewProjChangedQuestion();
            if (!notCancelled)     // cancelled
                return;
        }
    }

    // if not cancelled, clear the project
    project->NewProject();
}
//---------------------------------------------------------------------------

void Program::OpenProject()
{
// A routine for OpenProject button.

    // check if we have unsaved changes
    bool hasChanges = programState->GetProjectModified();

    // ask if the user wants to save changes.
    if (hasChanges)
    {
        bool projExists = programState->GetProjectExists();
        // if project exists
        if (projExists)
        {
            bool notCancelled = CurrProjChangedQuestion();
            if (!notCancelled)     // cancelled
                return;
        }

        // if project doesn't exist
        else
        {
            bool notCancelled = NewProjChangedQuestion();
            if (!notCancelled)     // cancelled
                return;
        }
    }

    // if not cancelled, try to open project
    if (!openProjDialog->Execute())
        return;
    String openProjName = openProjDialog->FileName;
    project->OpenProjectFrom(openProjName);
    
}
//---------------------------------------------------------------------------

void Program::SaveProjectAs()
{
// A routine for SaveProjectAs button.

    if (!saveProjDialog->Execute())
        return;               // save dialog cancelled
    String newName = saveProjDialog->FileName;
    project->SaveProjectTo(newName);

}
//---------------------------------------------------------------------------

void Program::SaveCurrentProject()
{
// A routine for SaveCurrentProject button.

    bool projChanged = programState->GetProjectModified();
    if (!projChanged)
        return;         // no changes => no need to save

    bool projExists = programState->GetProjectExists();

    // if project exists
    if (projExists)
    {
        String projFile = programState->GetProjectName();
        int ans =  Application->MessageBox( "Вы подтверждаете сохранение текущего проекта?",
             "Сохранение изменений", MB_YESNOCANCEL);
        if (ans==IDYES)
            project->SaveProjectTo(projFile);
    }

    // if project doesn't exit
    else
    {
        if (!saveProjDialog->Execute())
            return;               // save dialog cancelled
        String newName = saveProjDialog->FileName;
        project->SaveProjectTo(newName);
    }
}
//---------------------------------------------------------------------------

void Program::RPCalculateAndPlot()
{
// Calculate RP and draw the plots

    bool ok=false;
    RPInput rpInput = guiControl->ReadRPInputData(&ok);
    if (!ok)
        return;
        
    double maxRP, horShift, vertShift;
    Math* mathNew = new Math;
    ok = mathNew->CalculateAndReplaceInputAndRPData(rpInput,
                                            &vertShift, &horShift, &maxRP);
    if (!ok)
        return;

    // math->new math
    mathNew->CopyExtDataFrom(math);
    delete math;
    math = mathNew;


    plot->AddAllInputAndRP();
    guiControl->SetRPTxtResult(maxRP, horShift, vertShift);
    Form1->PageControl1->ActivePageIndex = 3;

    // if all went well project gets changed
    programState->SetProjectModified(true);
    programState->SetRPInputModified(false);
}
//---------------------------------------------------------------------------

void Program::SaveAmpAs()
{
// Save amplitude result, if it exists. Save dialog, etc.

    // find out if the RP exists
    bool rpExists = math->ResultExists();
    if (!rpExists)
    {
        ShowMessage("Отсутствует восстановленная ДН");
        return;
    }

    // open the SaveDialog
    if(!saveDialog->Execute())
        return;
    String fileName = saveDialog->FileName;

    // save file to the given location
    bool ok = math->SaveRPDataAsInPlot(amp, fileName);
    if (!ok)
        ShowMessage("Ошибка при сохранении файла");
}
//---------------------------------------------------------------------------

void Program::SavePhaseAs()
{
// Save phase result, if it exists. Open dialog, etc.

    // find out if the RP exists
    bool rpExists = math->ResultExists();
    if (!rpExists)
    {
        ShowMessage("Отсутствует восстановленная ДН");
        return;
    }

    // open the SaveDialog
    if(!saveDialog->Execute())
        return;
    String fileName = saveDialog->FileName;

    // save file to the given location
    bool ok = math->SaveRPDataAsInPlot(phase, fileName);
    if (!ok)
        ShowMessage("Ошибка при сохранении файла");

}
//---------------------------------------------------------------------------

void Program::SetRPInputModified()
{
// A function to be called when RP-input widgets get modified.

    programState->SetRPInputModified(true);
}
//---------------------------------------------------------------------------

void Program::SetPreparationInputModified()
{
// A function to be called when preparation-input widgets get modified.

    programState->SetPreparationInputModified(true);

}
//---------------------------------------------------------------------------




//------------------------- PRIVATE ROUTINES --------------------------------

bool Program::CurrProjChangedQuestion()
{
// Ask user, whether he wants to save curr (existing) project.
// If cancelled return false, else - true.

    String projFile = programState->GetProjectName();

    int ans =  Application->MessageBox( "В текущем проекте были произведены изменения."
        "Сохранить изменения?", "Сохранение изменений", MB_YESNOCANCEL);

    switch (ans)
    {
        case IDYES:      // save project.
            project->SaveProjectTo(projFile);
            break;
        case IDNO:       // do nothing.
            break;
        case IDCANCEL:   // abort saving and closing
            return false;
        default:
            assert(false);
    }
    return true;
}

bool Program::NewProjChangedQuestion()
{
// Ask user, whether he wants to save new (non-saved) project.
// If cancelled return false, else - true.

    int ans =  Application->MessageBox( "В проекте были произведены изменения."
        "Сохранить проект?", "Сохранение изменений", MB_YESNOCANCEL);

    String newName;
    switch (ans)
    {
        case IDYES:      // save project.
            if (!saveProjDialog->Execute())
                return false;               // save dialog cancelled
            newName = saveProjDialog->FileName;
            project->SaveProjectTo(newName);
            break;
        case IDNO:       // do nothing.
            break;
        case IDCANCEL:   // abort saving and closing
            return false;
        default:
            assert(false);
    }

    return true;
}
