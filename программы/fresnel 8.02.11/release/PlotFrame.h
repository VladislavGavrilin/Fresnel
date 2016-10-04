//---------------------------------------------------------------------------


#ifndef PlotFrameH
#define PlotFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <CheckLst.hpp>
#include "CSPIN.h"
#include <Dialogs.hpp>

#include <vector>
//---------------------------------------------------------------------------
class Tplot : public TFrame
{
// The class interface performs high-level operations on the Gui plot.
// The class interior is a frame implementing all plot-related operations.



__published:	// IDE-managed Components
    TChart *chart;
    TPanel *Panel1;
    TCheckListBox *listAmp;
    TRadioButton *radioAmp;
    TRadioButton *radioPhase;
    TCheckListBox *listExt;
    TLabel *Label1;
    TColorBox *colorBox;
    TCSpinEdit *lineWidth;
    TCSpinEdit *minRP;
    TCheckBox *phaseStraight;
    TCheckBox *normRP;
    TCheckListBox *listPhase;
    TButton *addExtButton;
    TButton *removeExtButton;
    TOpenDialog *extDataDialog;
    TLabel *Label2;
    TLabel *Label3;
    TButton *saveAmp;
    TButton *savePhase;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *maxRP;
    TLabel *shiftVert;
    TLabel *shiftHor;
    TLabel *rpInputChangeIndicator;
    void __fastcall radioClick(TObject *Sender);
    void __fastcall addExtButtonClick(TObject *Sender);
    void __fastcall removeExtButtonClick(TObject *Sender);
    void __fastcall listExtClickCheck(TObject *Sender);
    void __fastcall listAmpClickCheck(TObject *Sender);
    void __fastcall listPhaseClickCheck(TObject *Sender);
    void __fastcall PlotSettingsChange(TObject *Sender);
    void __fastcall lineWidthChange(TObject *Sender);
    void __fastcall listAmpClick(TObject *Sender);
    void __fastcall listExtClick(TObject *Sender);
    void __fastcall listPhaseClick(TObject *Sender);
    void __fastcall colorBoxChange(TObject *Sender);
    void __fastcall saveAmpClick(TObject *Sender);
    void __fastcall savePhaseClick(TObject *Sender);

public:
    __fastcall Tplot(TComponent* Owner);
    __fastcall ~Tplot();

    void AddAllInputAndRP();
    void RemoveAllInputAndRP();
    void AddExternal(int dataID, String fileName);
    void RemoveExternal(int index);
    void RemoveAllExternal();
    void AddExternal_action();
    void RemoveExternal_action();



private:
    std::vector<TLineSeries*> inputAmp;     // input plot ptrs
    std::vector<TLineSeries*> inputPhase;
    TLineSeries* rpAmp;                     // RP plot ptrs
    TLineSeries* rpPhase;

    std::vector<TLineSeries*> extData;      // external plot ptrs
    std::vector<int> extIDs;

    // private routines
    void PlotAmpInputAndRP ();
    void PlotPhaseInputAndRP ();

    void UpdateCBoxColor();
    void UpdatePlotColor();
    void FocusExt();
    void FocusAmp();
    void FocusPhase();
    TLineSeries* FindFocusedPlot();

};
//---------------------------------------------------------------------------
extern PACKAGE Tplot *plot;
//---------------------------------------------------------------------------
#endif
