#ifndef ProgramStateH
#define ProgramStateH
//---------------------------------------------------------------------------

#include <vcl.h>

class ProgramState
{
// The class tracks and indicates any changes in the project.
//
// You can add some Gui update with preparation-/RP- input changed/not changed.

public:
    ProgramState();      // set all to 0.

    void SetProjectName (String newName);
    String GetProjectName ();

    void SetRPInputModified (bool isModified);
    bool GetRPInputModified ();

    void SetPreparationInputModified (bool isModified);
    bool GetPreparationInputModified ();

    void SetProjectModified (bool isModified);
    bool GetProjectModified ();

    bool GetProjectExists ();

private:
    // private data
    String projectFileName;
    bool projectFilesOutOfDate;
    bool rpOutOfDate;
    bool preparationOutOfDate;

    // private functions
    void UpdateGuiProjectName ();
};

extern ProgramState* programState;





//---------------------------------------------------------------------------
#endif
