#ifndef PlotH
#define PlotH
//---------------------------------------------------------------------------

#include <vcl.h>

class Plot
{
// The class performs high-level operations on the Gui plot.

    


public:
    void AddAllInputAndRP();
    void RemoveAllInputAndRp();
    void AddExternal(int dataID);
    void RemoveExternal(int dataID);
    void RemoveAllExternal();

};

extern Plot* plot;





//---------------------------------------------------------------------------
#endif

 