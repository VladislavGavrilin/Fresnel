#ifndef StrGridH
#define StrGridH

#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Classes.hpp>
#include <Grids.hpp>
#include <vcl>

#include <vector.h>

typedef vector<String> StrList;   // instead of TStringList
                                  // it was only available through heap memory
class StrGrid
{
// The class controls a StringGrid widget.
// One could have inherited from a StringGrid instead.

public:
    StrGrid (TStringGrid* strGridIn);
    ~StrGrid ();

    StrList ReadFileNames ();   // public functions
    void WriteAndClearFileNames  (StrList fileNames);
    void Clear ();
    void SetDefaultExtention (String ext);

    void AddFileWithDialogAndSort ();         // functions for buttons
    void RemoveFile ();
    void SortFiles ();

                         // callback for StringGrid - change indices of files
    void __fastcall OnRowMoved(TObject *Sender, int FromIndex,
      int ToIndex);


private:
    TStringGrid* strGrid;    // private vars
    int filesCount;
    static TOpenDialog* openDialog;

    void UpdateIndices();    // private functions
    String ReadFileName (int index);
    void AddFileName (String newFileName);
    void DeleteFileName (int index);

    int FindNumber(String fileName, bool* ok);

};

extern StrGrid* strGridAmp;
extern StrGrid* strGridPhase;


class SortingClass 
{
// use this class to sort integers

public:
    int number;
    int value;
    bool operator < (const SortingClass & rhs)
    {
        return value < rhs.value;
    }
};






//---------------------------------------------------------------------------
#endif

