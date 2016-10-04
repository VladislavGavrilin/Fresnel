#include "Settings.h"

#include "MainForm.h"

#include <IniFiles.hpp>



bool Settings::ReadAndApplyGraphicSettings (String iniFile)
{
// Try to read settings from the file specified.
// On error just don't do anything.

    // check if the file exists
    if (!FileExists(iniFile))
        return false;

    // create ini-object, test if the file is OK
    TIniFile* ini = new TIniFile (iniFile);
    bool sec1 = ini->SectionExists("Window");
    bool sec2 = ini->SectionExists("Plot");
    bool sec3 = ini->SectionExists("StrGridLength");
    bool sec4 = ini->SectionExists("Project");

    if (!(sec1 && sec2 && sec3 && sec4))
        return false;

    // read and apply settings
    
    // [Window] section
    if (ini->ReadInteger("Window","height", -1) != -1)
        Form1->Height = ini->ReadInteger("Window","height", -1);
    if (ini->ReadInteger("Window","width", -1) != -1)
        Form1->Width = ini->ReadInteger("Window","width", -1);
    if (ini->ReadInteger("Window","left", -1) != -1)
        Form1->Left = ini->ReadInteger("Window","left", -1);
    if (ini->ReadInteger("Window","top", -1) != -1)
        Form1->Top = ini->ReadInteger("Window","top", -1);

    if (ini->ReadString("Window","state","") == "maximized")
        Form1->WindowState = wsMaximized;


    // [Plot] section
    if (ini->ReadInteger("Plot","minRP", -1) != -1)
        plot->minRP->Value = ini->ReadInteger("Plot","minRP", -1);
    if (ini->ReadInteger("Plot","lineWidth", -1) != -1)
        plot->lineWidth->Value = ini->ReadInteger("Plot","lineWidth", -1);

    plot->phaseStraight->Checked = ini->ReadBool("Plot","phaseStraight", false);
    plot->normRP->Checked = ini->ReadBool("Plot","normRP", false);
    


    // [StrGridLength] section
    if (ini->ReadInteger("StrGridLength","col1Amp", -1) != -1)
        Form1->sg_amp->ColWidths[1] = ini->ReadInteger("StrGridLength","col1Amp", -1);
    if (ini->ReadInteger("StrGridLength","col2Amp", -1) != -1)
        Form1->sg_amp->ColWidths[2] = ini->ReadInteger("StrGridLength","col2Amp", -1);
    if (ini->ReadInteger("StrGridLength","col1Phase", -1) != -1)
        Form1->sg_phase->ColWidths[1] = ini->ReadInteger("StrGridLength","col1Phase", -1);
    if (ini->ReadInteger("StrGridLength","col2Phase", -1) != -1)
        Form1->sg_phase->ColWidths[2] = ini->ReadInteger("StrGridLength","col2Phase", -1);


    return true;
}
//---------------------------------------------------------------------------

String Settings::ReadLastProject (String iniFile)
{
// Try to read lastProjectFile from the ini-file specified.
// On error return "".

    TIniFile* ini = new TIniFile (iniFile);

    String file = ini->ReadString("Project", "lastProject", "");

    delete ini;
    return file;
}
//---------------------------------------------------------------------------

void Settings::WriteSettings(String lastProjectFile, String iniFile)
{
// Try to write settings to the file specified.
// On error just don't do anything.

    // create ini-file object
    TIniFile* ini = new TIniFile (iniFile);

    // write data to object
    // [Window] section
    if (Form1->WindowState == wsMaximized)
        ini->WriteString("Window","state", "maximized");
    else
    {
        ini->WriteString("Window","state", "normal");
        ini->WriteInteger("Window","height", Form1->UndockHeight);
        ini->WriteInteger("Window","width", Form1->Width);
        ini->WriteInteger("Window","left", Form1->Left);
        ini->WriteInteger("Window","top", Form1->Top);
    }


    // [Plot] section
    ini->WriteInteger("Plot","minRP", plot->minRP->Value);
    ini->WriteInteger("Plot","lineWidth", plot->lineWidth->Value);
    ini->WriteBool("Plot","phaseStraight",plot->phaseStraight->Checked);
    ini->WriteBool("Plot","normRP",plot->normRP->Checked);

    // [StrGridLength] section
    ini->WriteInteger("StrGridLength","col1Amp", Form1->sg_amp->ColWidths[1] );
    ini->WriteInteger("StrGridLength","col2Amp", Form1->sg_amp->ColWidths[2]);
    ini->WriteInteger("StrGridLength","col1Phase", Form1->sg_phase->ColWidths[1] );
    ini->WriteInteger("StrGridLength","col2Phase", Form1->sg_phase->ColWidths[2]);

    // [Project] section
    ini->WriteString("Project","lastProject", lastProjectFile);

    // flush the data to disk
    ini->UpdateFile();

    // clean up
    delete ini;
}
//---------------------------------------------------------------------------

