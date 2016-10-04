#include "GuiControl.h"
#include "MainForm.h" // GUI widgets.
#include "StrGrid.h"
#include "PlotFrame.h"

#include <math>


bool s2d (String s, double& d)
{
    // Converts a string to a double.
    // Tested on RUS and US locales.
    try
    {
        d = StrToFloat(s);
    }
    catch(...)
    {
        String s2;
        int pos = s.Pos(".");
        if (pos > 0)      // "." -> ","
            s2 = s.SubString(1,pos-1)+","+s.SubString(pos+1,s.Length());
        else              // "," -> "."
        {
            pos = s.Pos(",");
            if (pos == 0) return false;
            s2 = s.SubString(1,pos-1)+"."+s.SubString(pos+1,s.Length());
        }

        try
        {
            d = StrToFloat(s2);
        }
        catch(...)
        {
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------


GuiControl::GuiControl ()
{
// Making a list of Edits and Labels to be saved in the PRJ-files.

    TEdit* projectEdits_temp [] =
    {
    // The array of Edits to be saved to project files
    // To add/ delete Edits to prj-files, just insert its ptr here.

        //Form1->Edit1,
        Form1->calibrAmpEdit,
        Form1->calibrPhaseEdit,
        Form1->Edit2,
        Form1->Edit3,
        Form1->Edit4,
        Form1->Edit5,
        Form1->Edit6,
        Form1->Edit7,
        Form1->Edit8,
        Form1->Edit9,
        Form1->Edit10,
        Form1->Edit11,
        Form1->Edit12,
        Form1->Edit13,
        Form1->Edit14,

        Form1->EditFreq,
        Form1->EditHVert,
        Form1->EditHHor,
        Form1->EditResultSector,
        Form1->EditR,

        Form1->EditStep,
        Form1->EditNOfSec,
        Form1->EditMeasSector,
        Form1->EditStepMan,
        Form1->EditNOfSecMan
    };
    const int projectEditsCount = sizeof(projectEdits_temp)/ sizeof(TEdit*);

    TLabel* projectLabels_temp [] =
    {
    // The array of Labels to be saved to project files
    // To add/ delete Labels to prj-files, just insert its ptr here.

        plot->maxRP,
        plot->shiftVert,
        plot->shiftHor
    };
    const int projectLabelsCount = sizeof(projectLabels_temp)/ sizeof(TLabel*);

    // saving the lists to member variables
    for (int i=0; i<projectEditsCount; i++)
        projectEdits.push_back(projectEdits_temp[i]);

    for (int i=0; i<projectLabelsCount; i++)
        projectLabels.push_back(projectLabels_temp[i]);

}             

//---------- access functions for project's edits and labels ----------

int GuiControl::GetProjectEditsCount()
{
// Access function
    return projectEdits.size();
}

int GuiControl::GetProjectLabelsCount()
{
// Access function
    return projectLabels.size();
}

TEdit* GuiControl::GetProjectEdit(int index)
{
// Access function
    return projectEdits[index];
}

TLabel* GuiControl::GetProjectLabel(int index)
{
// Access function
    return projectLabels[index];
}

//---------------------------------------------------------------------------



void GuiControl::SetWindowTitle (String newTitle)
{
// Update window title.
    Form1->Caption = newTitle;
}
//---------------------------------------------------------------------------

WidgetsData GuiControl::ReadWidgetsData()
{
// Reads the txt and other project-related data from GUI.

    WidgetsData data;

    // edits
    for (int i=0; i<(guiControl->GetProjectEditsCount()); i++)       // Edits
    {
        String value = ((TEdit*)guiControl->GetProjectEdit(i)) ->Text;
        data.editValues.push_back (value);
    }

    // labels
    for (int i=0; i<(guiControl->GetProjectLabelsCount()); i++)        // Labels
    {
        String value = ((TLabel*)GetProjectLabel(i)) ->Caption;
        data.labelValues.push_back (value);
    }

    // others
    data.ampFiles = strGridAmp->ReadFileNames();
    data.phaseFiles = strGridPhase->ReadFileNames();

    // dat-bln
    if (Form1->RadioDAT->Checked)
        data.calRbPosition = dat;
    else
        data.calRbPosition = bln;


    return data;
}
//---------------------------------------------------------------------------

void GuiControl::WriteWidgetsData(WidgetsData data)
{
// Write the txt and other project-related data to GUI.

    // dat-bln                        --   it goes before writing to stringGrid
    //                                     because it would cause a user message to appear
    strGridAmp->Clear();  // clear StrGrids to suppress user alert message.
    strGridPhase->Clear();
    if (data.calRbPosition == dat)   // the dat-bln itself
        Form1->RadioDAT->Checked = true;
    else
        Form1->RadioBLN->Checked = true;

    // edits
    for (int i=0; i<(guiControl->GetProjectEditsCount()); i++)       // Edits
    {
        String value = data.editValues[i];
        ((TEdit*)guiControl->GetProjectEdit(i)) ->Text = value;
    }

    // labels
    for (int i=0; i<(guiControl->GetProjectLabelsCount()); i++)        // Labels
    {
        String value = data.labelValues[i];
        ((TLabel*)GetProjectLabel(i)) ->Caption = value;
    }

    // strGrids
    strGridAmp->WriteAndClearFileNames(data.ampFiles);
    strGridPhase->WriteAndClearFileNames(data.phaseFiles);
}
//---------------------------------------------------------------------------

void GuiControl::SetWidgetsToDefault()
{
// Clear most of widgets...

    // strGrids
    strGridAmp->Clear();
    strGridPhase->Clear();

    // edits
    for (int i=0; i<(guiControl->GetProjectEditsCount()); i++)     // project-related edits
        ((TEdit*)guiControl->GetProjectEdit(i)) ->Text = "";

    Form1->Edit8->Text = "0.1";             // custom edit values
    Form1->Edit9->Text = "0";
    Form1->Edit10->Text = "0";
    Form1->Edit11->Text = "0";
    Form1->Edit12->Text = "0";
    Form1->Edit13->Text = "0";
    Form1->Edit14->Text = "50";

    // labels
    for (int i=0; i<(guiControl->GetProjectLabelsCount()); i++)
        ((TLabel*)GetProjectLabel(i)) ->Caption = "";

    // dat-bln => bln
    Form1->RadioBLN->Checked = true;
}


//-------------------- STRUCT WIDGETS_DATA CONSTRUCTOR ----------------------

// create and delete StringLists in constructor/destructor
// fill in the names of Edits and Labels
WidgetsData::WidgetsData ()
{
    for (int i=0; i<(guiControl->GetProjectEditsCount()); i++)       // Edits
    {
        String name = (guiControl->GetProjectEdit(i)) ->Name;
        editNames.push_back (name);
    }

    for (int i=0; i<(guiControl->GetProjectLabelsCount()); i++)        // Labels
    {
        String name = (guiControl->GetProjectLabel(i)) ->Name;
        labelNames.push_back (name);
    }
}
//---------------------------------------------------------------------------



RPInput GuiControl::ReadRPInputData(bool * ok)
{
// Read input data for RP calculations.
// On error, report it and *ok=false.
// Return values in cantimeters, degrees and GHz

    RPInput data;
    bool done;
    double value;

    done = s2d(Form1->Edit5->Text, value);
    if (!done)
    {
        ShowMessage("Не распознано расстояние наблюдения");
        *ok = false;
        return data;
    }
    data.r = value*100;

    done = s2d(Form1->Edit2->Text, value);
    if (!done)
    {
        ShowMessage("Не распознана частота");
        *ok = false;
        return data;
    }
    data.f = value;

    done = s2d(Form1->Edit9->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан верт. сдвиг фаз. центра");
        *ok = false;
        return data;
    }
    data.dXCenter = value/10;       // millimeters -> cantimeters

    done = s2d(Form1->Edit10->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан дианазон верт. сдвига");
        *ok = false;
        return data;
    }
    data.dXHalfLength = value/10;       // millimeters -> cantimeters

    done = s2d(Form1->Edit11->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан гор. сдвиг фаз. центра");
        *ok = false;
        return data;
    }
    data.dYCenter = value/10;       // millimeters -> cantimeters

    done = s2d(Form1->Edit12->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан диапазон гор. сдвига");
        *ok = false;
        return data;
    }
    data.dYHalfLength = value/10;       // millimeters -> cantimeters

    done = s2d(Form1->Edit13->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан шаг поиска фаз. центра");
        *ok = false;
        return data;
    }
    data.dXdYStep = value/10;       // millimeters -> cantimeters

    done = s2d(Form1->Edit7->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан шаг по углу места");
        *ok = false;
        return data;
    }
    data.stepAlpha = value;

    done = s2d(Form1->Edit6->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан шаг по азимуту");
        *ok = false;
        return data;
    }
    data.stepBeta = value;

    done = s2d(Form1->Edit8->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан шаг графика");
        *ok = false;
        return data;
    }
    data.stepBetaSmall = value;

    done = s2d(Form1->Edit14->Text, value);
    if (!done)
    {
        ShowMessage("Не распознан количество коэффициентов");
        *ok = false;
        return data;
    }
    data.kHalfAmount = value;

    if (Form1->RadioDAT->Checked)
    {
        data.calibr = dat;
        data.ampCalFile = Form1->calibrAmpEdit->Text;
        data.phaseCalFile = Form1->calibrPhaseEdit->Text;
    }
    else
    {
        data.calibr = bln;
        data.ampCalFile = "";
        data.phaseCalFile = "";
    }

    data.ampFiles = strGridAmp->ReadFileNames();
    data.phaseFiles = strGridPhase->ReadFileNames();

    *ok = true;
    return data;
}


void GuiControl::SetRPTxtResult(double maxRPValue, double horShift, double vertShift)
{
// Set 3 labels in "plot"

    plot->maxRP->Caption = floor(maxRPValue*100+0.5)/100;
    plot->shiftVert->Caption = floor(vertShift*100+0.5)/100;
    plot->shiftHor->Caption = floor(horShift*100+0.5)/100;
}
