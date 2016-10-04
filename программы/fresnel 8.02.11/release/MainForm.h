//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
#include <Chart.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "PlotFrame.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabPrepare;
    TLabel *Label27;
    TLabel *Label28;
    TLabel *Label29;
    TGroupBox *GroupBox1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *EditFreq;
    TEdit *EditHVert;
    TEdit *EditHHor;
    TEdit *EditResultSector;
    TEdit *EditR;
    TButton *Button1;
    TGroupBox *GroupBox2;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label14;
    TLabel *Label15;
    TEdit *EditStep;
    TEdit *EditNOfSec;
    TEdit *EditMeasSector;
    TEdit *EditStepMan;
    TEdit *EditNOfSecMan;
    TButton *Button2;
    TButton *Button3;
    TTabSheet *TabObrDn;
    TLabel *Label1;
    TRadioButton *RadioDAT;
    TRadioButton *RadioBLN;
    TTabSheet *TabMain;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
    TStringGrid *sg_amp;
    TStringGrid *sg_phase;
    TButton *ButtonAddAmp;
    TButton *ButtonDelAmp;
    TButton *ButtonAddPh;
    TButton *ButtonDelPh;
    TButton *ButtonGo;
    TButton *Button4;
    TButton *Button5;
    TTabSheet *TabResult;
    TPanel *Panel2;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TLabel *Label26;
    Tplot *plot1;
    TGroupBox *BoxDatBln;
    TEdit *calibrAmpEdit;
    TButton *ButtonAmpCal;
    TButton *ButtonPhaseCal;
    TEdit *calibrPhaseEdit;
    TLabel *Label23;
    TLabel *Label24;
    TLabel *Label25;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
    TEdit *Edit6;
    TEdit *Edit7;
    TEdit *Edit8;
    TLabel *Label30;
    TLabel *Label31;
    TLabel *Label32;
    TEdit *Edit9;
    TEdit *Edit10;
    TEdit *Edit11;
    TEdit *Edit12;
    TEdit *Edit13;
    TEdit *Edit14;
    TOpenDialog *openCalFiles;
    TLabel *Label21;
    TLabel *Label22;
    TButton *Button6;
    void __fastcall ButtonAddAmpClick(TObject *Sender);
    void __fastcall ButtonDelAmpClick(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall ButtonAddPhClick(TObject *Sender);
    void __fastcall ButtonDelPhClick(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall ButtonGoClick(TObject *Sender);
    void __fastcall RadioBLNClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall ButtonAmpCalClick(TObject *Sender);
    void __fastcall ButtonPhaseCalClick(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

    void __fastcall prepInputChanged(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall rpInputChanged(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall plot1addExtButtonClick(TObject *Sender);

private:	// User declarations



public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
