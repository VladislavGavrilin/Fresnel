#ifndef ProgramH
#define ProgramH
//---------------------------------------------------------------------------

#include <vcl>

class Program
{
// Class performs most high-level functions.

public:
    // create/ delete SaveDialog.
    Program();
    ~Program();
    // public routines
    void StartUp(String exeFileName, String projFileName);
    bool BeforeExit();
    void NewProject();
    void OpenProject();
    void SaveProjectAs();
    void SaveCurrentProject();
    void RPCalculateAndPlot();
    void SaveAmpAs();
    void SavePhaseAs();
    void SetRPInputModified();
    void SetPreparationInputModified();

private:
    TSaveDialog* saveDialog;
    TSaveDialog* saveProjDialog;
    TOpenDialog* openProjDialog;
    String iniFile;
    bool CurrProjChangedQuestion();
    bool NewProjChangedQuestion();

};

extern Program* program;




//---------------------------------------------------------------------------
#endif

 