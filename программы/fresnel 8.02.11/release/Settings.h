#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------

#include <vcl>

class Settings
{
// Save and restore program settings (window size, strGrid lengths, so on)

public:
    bool ReadAndApplyGraphicSettings (String iniFile);
    String ReadLastProject(String iniFile);
    void WriteSettings(String lastProjectFile, String iniFile);

};

extern Settings* settings;

//---------------------------------------------------------------------------
#endif

 