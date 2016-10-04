//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "PlotFrame"
#pragma resource "*.dfm"



#include "Project.h"
#include "GuiControl.h"
#include "ProgramState.h"
#include "MathControl.h"
#include "StrGrid.h"
#include "Program.h"
#include "Settings.h"



TForm1 *Form1;


// global objects
Project* project = NULL;
GuiControl* guiControl = NULL;
ProgramState* programState = NULL;
Math* math = NULL;
Program* program;
Settings* settings;

StrGrid* strGridAmp;
StrGrid* strGridPhase;

extern bool s2d (String s, double& d);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
// Creating global controller objects.
// It would be better to do it in "Program" class constructor.

    plot = plot1;

    
    project = new Project();
    guiControl = new GuiControl();
    programState = new ProgramState ();
    math = new Math();
    program = new Program();
    settings = new Settings();

    strGridAmp = new StrGrid(sg_amp);
    strGridPhase = new StrGrid(sg_phase);



     // command line arguments
     String projFileName = "";
     if (ParamCount()>0)
        projFileName = ParamStr(1);
     String exeFileName = ParamStr(0);
     program->StartUp(exeFileName, projFileName);


}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddAmpClick(TObject *Sender)
{
    strGridAmp->AddFileWithDialogAndSort();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonDelAmpClick(TObject *Sender)
{
    strGridAmp->RemoveFile();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    strGridAmp->SortFiles();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAddPhClick(TObject *Sender)
{
    strGridPhase->AddFileWithDialogAndSort();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonDelPhClick(TObject *Sender)
{
    strGridPhase->RemoveFile();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
    strGridPhase->SortFiles();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonGoClick(TObject *Sender)
{
    program->RPCalculateAndPlot();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioBLNClick(TObject *Sender)
{

    BoxDatBln->Visible = (RadioDAT->Checked);
    program->SetRPInputModified();

    if (RadioDAT->Checked)
    {
        strGridAmp->SetDefaultExtention ("dat");
        strGridPhase->SetDefaultExtention ("dat");
    }
    else
    {
        strGridAmp->SetDefaultExtention ("bln");
        strGridPhase->SetDefaultExtention ("bln");
    }

    // check if there's something in strGrids
    StrList ampList = strGridAmp->ReadFileNames();
    StrList phaseList = strGridPhase->ReadFileNames();
    if ((ampList.size() + phaseList.size()) > 0)
        ShowMessage("Внимание! В проекте уже есть исходные файлы!\n"
            "Использование неподходящей калибровки может сделать\n"
            "проект недоступным при следующем открытии!");

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
// Calculate main preparation parameters.
// The code is from previous version of the program.

    double temp;
    // filling in InParams.
    if (!s2d(EditFreq->Text, temp))
    {
        ShowMessage("Не распознана частота.");
        return;
    }
    if (temp<=0)
    {
        ShowMessage("Параметры должны быть положительны.");
        return;
    }
    double lambda = 30/temp;
    // -----------

    if (!s2d(EditHVert->Text, temp))
    {
        ShowMessage("Не распознан вертикальный размер.");
        return;
    }
    if (temp<=0)
    {
        ShowMessage("Параметры должны быть положительны.");
        return;
    }
    double hVert = temp/10;
    // -----------

    if (!s2d(EditHHor->Text, temp))
    {
        ShowMessage("Не распознан горизонтальный размер.");
        return;
    }
    if (temp<=0)
    {
        ShowMessage("Параметры должны быть положительны.");
        return;
    }
    double hHor = temp/10;
    // -----------

    if (!s2d(EditResultSector->Text, temp))
    {
        ShowMessage("Не распознан сектор ДН.");
        return;
    }
    if (temp<=0)
    {
        ShowMessage("Параметры должны быть положительны.");
        return;
    }
    double sector = temp*M_PI/180;
    // -----------

    if (!s2d(EditR->Text, temp))
    {
        ShowMessage("Не распознана дистанция измерения.");
        return;
    }
    if (temp<=0)
    {
        ShowMessage("Параметры должны быть положительны.");
        return;
    }
    double r = temp*100;



    double dAlpha = lambda/hVert;

    int N = 2*floor(lambda/(2*r*dAlpha*dAlpha) + 0.5) + 1;

    double sectorNew = sector + (hHor/r);


    EditStep->Text = ceil(dAlpha/M_PI*180*1000)/1000;
    EditNOfSec->Text = N;
    EditMeasSector->Text = ceil(sectorNew/M_PI*180*10)/10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAmpCalClick(TObject *Sender)
{
// Add amp. calibration file

    if (!openCalFiles->Execute())
        return;

    calibrAmpEdit->Text = openCalFiles->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonPhaseCalClick(TObject *Sender)
{
// Add phase calibration file

    if (!openCalFiles->Execute())
        return;

    calibrPhaseEdit->Text = openCalFiles->FileName;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
// Go to tab 2 (vosst) with edit values. callback.
// Reusing the code from previous version.

    Edit2->Text = EditFreq->Text;
    Edit3->Text = EditHVert->Text;
    Edit4->Text = EditHHor->Text;
    Edit5->Text = EditR->Text;    

    if(EditStepMan->Text != "")
        Edit6->Text = EditStepMan->Text;
    else
        Edit6->Text = EditStep->Text;

    if(EditStepMan->Text != "")
        Edit7->Text = EditStepMan->Text;
    else
        Edit7->Text = EditStep->Text;

    PageControl1->ActivePageIndex = 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    bool close = program->BeforeExit();
    if (!close)
        Action = caNone;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::prepInputChanged(TObject *Sender)
{
    program->SetPreparationInputModified();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
    program->NewProject();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
    program->OpenProject();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
    program->SaveCurrentProject();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
    program->SaveProjectAs();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rpInputChanged(TObject *Sender)
{
    program->SetRPInputModified();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button2Click(TObject *Sender)
{
// Calculate the amount of sections for manual angular step.
// Reusing the code from the previous version.

    double freq, r, dAlpha, lambda ;

    // check different cases...
    if (EditStep->Color == clYellow)
    {
        ShowMessage("Входные параметры изменены.\nНеобходимо пересчитать выходные.");
        return;
    }
    if (EditStep->Text == "")
    {
        ShowMessage("Необходимо вычислить выходные параметры.");
        return;
    }

    // filling in InParams.
    if (!s2d(EditFreq->Text, freq))
    {
        ShowMessage("Не распознана частота.");
        return;
    }

   if (!s2d(EditR->Text, r))
    {
        ShowMessage("Не распознана дистанция измерения.");
        return;
    }
    r = r*100;

    if (!s2d(EditStepMan->Text, dAlpha))
    {
        ShowMessage("Не распознан шаг измерения по углу места.");
        return;
    }
    dAlpha = dAlpha*M_PI/180;



    // must be > 0
    if ((freq<=0) || (r<=0) || (dAlpha<=0))
    {
        ShowMessage("Параметры должны быть положительны.");
        return;
    }

    lambda = 30/freq;

    double dAlphaOld;
    s2d(EditStep->Text, dAlphaOld);
    dAlphaOld = dAlphaOld*M_PI/180;

    if (dAlpha > dAlphaOld)
    {
                ShowMessage("Заданный вручную шаг слишком большой\n"
                    "для корректного восстановления ДН.");
                return;
    }

    int N = 2*floor(lambda/(2*r*dAlpha*dAlpha) + 0.5) + 1;

    EditNOfSecMan->Text = N;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
    strGridAmp->Clear();
    strGridPhase->Clear();
    program->SetRPInputModified();      // project modified 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::plot1addExtButtonClick(TObject *Sender)
{
  plot1->addExtButtonClick(Sender);

}
//---------------------------------------------------------------------------

