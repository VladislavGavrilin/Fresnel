#ifndef GuiControlH
#define GuiControlH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include "StrGrid.h"    // StrList typedef

struct WidgetsData;
struct RPInput;

class GuiControl
{
// A dummy class for tests.
// The real GuiControl handles txt r/w operations with widgets

public:
    GuiControl();
    void SetWindowTitle (String newTitle);
    WidgetsData ReadWidgetsData();
    void WriteWidgetsData(WidgetsData widgetsData);
    void SetWidgetsToDefault();
    RPInput ReadRPInputData(bool * ok);
    void SetRPTxtResult(double maxRPValue, double horShift, double vertShift);

private:
    // private data
    std::vector<TEdit*> projectEdits;    // Widgets to be saved to .prj
    std::vector<TLabel*> projectLabels;

    // private functions
    int GetProjectEditsCount();          // Widgets to be saved to .prj
    TEdit* GetProjectEdit (int i);
    int GetProjectLabelsCount();     
    TLabel* GetProjectLabel (int i);

    friend struct WidgetsData;          // Accessing GetProjectEdit and others...
};

extern GuiControl* guiControl;

//------------------------- WidgetsData --------------------------------

enum PlotStepRbPosition
{
// Indicates the position of the RadioButton "step of the RP data"
// It's used only in WidgetsData structure.

    basedOnAntennaWidth,
    byHand
};

enum CalibrationRbPosition
{
// Indicates the position of the RadioButton "dat/bln - calibration"
// It's used only in WidgetsData structure.

    dat,
    bln
};
//---------------------------------------------------------------------------

struct WidgetsData
{
// The data directly from project-level text-widgets and radio-buttons.
// Some fields must be preprocessed before r/w to ini (StrGrids)
//
// To add new Edits/ Labels - add their ptrs to GuiControl's arrays of ptrs.

    // fill in the names of Edits and Labels in constructor
    WidgetsData ();

    // data
    StrList ampFiles;    // StringGrids
    StrList phaseFiles;

    StrList editNames;   // all Edits and Labels
    StrList editValues;   // Name ~ widget ID, Value - its value.

    StrList labelNames;
    StrList labelValues;

    PlotStepRbPosition stepRbPosition;
    CalibrationRbPosition calRbPosition;
};
//---------------------------- OTHER STRUCTURES ------------------------------

struct RPInput
{
// Data for RP calculations. (WidgetsData presents only Strings, this one - values)
// Data is stored in cantimeters, degrees and GHz!!!!

    double r;
    double f;

    double dXCenter;
    double dXHalfLength;
    double dYCenter;
    double dYHalfLength;
    double dXdYStep;

    int kHalfAmount;
    double stepAlpha;
    double stepBeta;
    double stepBetaSmall;

    StrList ampFiles;
    StrList phaseFiles;

    CalibrationRbPosition calibr;

    String ampCalFile;
    String phaseCalFile;
};

//---------------------------------------------------------------------------
#endif
 