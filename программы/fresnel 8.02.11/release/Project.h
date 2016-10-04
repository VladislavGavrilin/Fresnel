#ifndef ProjectH
#define ProjectH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>


#include "GuiControl.h"   // for struct WidgetsData 

class Project
{
// The class is responsible for project open/close/new operations.
// It doesn't ask qustions (question are in Program-class).

public:
    void OpenProjectFrom (String projectFileName);
    void SaveProjectTo (String projectFileName);
    void NewProject ();

private:          
    // private data types
    struct StatusIniVars        // used to be ProgramState
    {
        // use it to read/write program state data to '.prj'-files
        bool rpOutOfDate;
        bool preparationOutOfDate;
        bool resultExists;
    };

    // private methods
    Project::StatusIniVars ReadProjectIniForState (TIniFile* ini);     // r/w to TIniFile
    void WriteProjectIniForState (TIniFile* ini, StatusIniVars statusVars);
    
    WidgetsData ReadProjectIniForWidgets (TIniFile* ini, String filesDirWithSlash);
    void WriteProjectIniForWidgets (TIniFile* ini,WidgetsData widgetsData);

    bool CheckIniFileConsistency (TIniFile* ini);

    bool CheckProjectFileName (String fileName);        // file system r/w, checks
    bool CheckInputFilesExist (WidgetsData widgetsData);
    String ProjectDirectoryWithSlash (String projectFileName);
    bool CreateOrFindDirectory (String dirNameWithSlash);
    bool CopyInputFiles(const WidgetsData& widgetsData, String dirWithSlash);
    bool CopyFileToDirWithCheck (String oldFile, String newDirWithSlash);

    WidgetsData ChangeWidgetsDataPath (const WidgetsData& widgetsData, String newDir);

    String AmpCalibrFileName (WidgetsData widgetsData);    // the design is not perfect...
    String PhaseCalibrFileName (WidgetsData widgetsData);

    // constants  - they are defined in the cpp-file
    // Maybe it would be better to use global constants... (m.b. with a prefix)
    const static String statusVars_sec;         // section names from ini
    const static String edits_sec;
    const static String labels_sec;
    const static String ampGrid_sec;
    const static String phaseGrid_sec;
    const static String others_sec;

    const static String rpOutOfDate_id;         // identifiers from ini
    const static String preparationOutOfDate_id;  // program state
    const static String resultExists_id;

    const static String strGridPrefix_id;         // string grids
    const static String count_id;

    const static String stepRbPosition_id;        // others1
    const static String stepRb_AntWidth_val;
    const static String stepRb_ByHand_val;

    const static String calibrRbPosition_id;      // others2
    const static String calibrRb_dat_val;
    const static String calibrRb_bln_val;

    const static String dirNameSuffix;            // project directory name suffix

    const static String calibrAmpEditName;        // names of Edits with calibr files
    const static String calibrPhaseEditName;

    const static String resultFileAmp;        // names of result-files
    const static String resultFilePhase;
};

extern Project* project;

//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
#endif
