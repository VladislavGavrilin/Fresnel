#include "ProgramState.h"
#include "GuiControl.h"        // for updating GUI
#include "MainForm.h"       // updating widgets too
#include "PlotFrame.h"      // -||-
#include "MathControl.h"    // ResultExists

const String prefix = "Fresnel: ";


ProgramState::ProgramState ()
{
// set all member data to 0.

    projectFileName = "";
    projectFilesOutOfDate = false;
    rpOutOfDate = false;
    preparationOutOfDate = false;
}

// ---------------------- ProjectName ---------------------------

void ProgramState::SetProjectName (String newName)
{
    projectFileName = newName;
    UpdateGuiProjectName();
}
// ---------------------------------------------------------------

String ProgramState::GetProjectName ()
{
    return projectFileName;
}

// -------------------- RPInputModified  -------------------------

void ProgramState::SetRPInputModified (bool isModified)
{
    rpOutOfDate = isModified;

    if (isModified)     // projects gets modified when input gets
        SetProjectModified(true);

    plot->rpInputChangeIndicator->Visible = isModified && math->ResultExists();
}
// ---------------------------------------------------------------

bool ProgramState::GetRPInputModified ()
{
    return rpOutOfDate;
}
// ---------------- PreparationInputModified ---------------------


void ProgramState::SetPreparationInputModified (bool isModified)
{
    preparationOutOfDate = isModified;

    if (isModified)     // projects gets modified when input gets
        SetProjectModified(true);
}
// ---------------------------------------------------------------

bool ProgramState::GetPreparationInputModified ()
{
    return preparationOutOfDate;
}

// -------------------- ProjectModified -------------------------

void ProgramState::SetProjectModified (bool isModified)
{
    projectFilesOutOfDate = isModified;
    UpdateGuiProjectName();
}
// ---------------------------------------------------------------

bool ProgramState::GetProjectModified ()
{
    return projectFilesOutOfDate;
}
// --------------------- ProjectExists -------------------------

bool ProgramState::GetProjectExists ()
{
    if (projectFileName == "")
        return false;
    else
        return true;
}


// --------------------- PRIVATE FUNCTIONS -------------------------

void ProgramState::UpdateGuiProjectName ()
{
// Use this function to update GUI window title
// (where we show the project's name)

    // If the projet is changed, display prefix+name+"*"
    String nameDisplayed;
    if (projectFilesOutOfDate)
        nameDisplayed = prefix + projectFileName + " *";
    else
        nameDisplayed = prefix + projectFileName;

    // Display name
    guiControl->SetWindowTitle(nameDisplayed);
}
