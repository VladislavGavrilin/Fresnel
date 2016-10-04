#include "StrGrid.h"
#include "Program.h"
#include <algorithm>
#include <assert>


bool MyCompare(SortingClass s1, SortingClass s2)
{
// A non-member function used in sotring
    return s1.value<s2.value;
}

//---------------------------- CONTRUCTOR ------------------------------

TOpenDialog* StrGrid::openDialog = NULL;         // the static member initialization
                                                //  - to have the same dialog in all objects
StrGrid::StrGrid (TStringGrid* strGridIn)
{
// The constructor.
// Saving the TStringGrid-pointer and setting it up
// (properties: read-only,..., events: row-move).

    strGrid = strGridIn;            // private vars
    filesCount = 0;

    strGrid->Cells[0][0] = "№";
    strGrid->Cells[1][0] = "Путь к файлу";
    strGrid->Cells[2][0] = "Имя файла";

    strGrid->ColCount = 3;          // dimensions
    strGrid->RowCount = 2;
    strGrid->DefaultRowHeight = 20;
    strGrid->ColWidths[0] = 25;

    TGridRect sel= {1,1,2,1};       // select 1st cell
    strGrid->Selection = sel; 

    strGrid->Options.Clear();       // options
    strGrid->Options << goFixedVertLine << goFixedHorzLine << goVertLine <<
        goHorzLine << goColSizing << goRowMoving << goEditing << goRowSelect;


    strGrid->OnRowMoved = this->OnRowMoved;

    // open dialog + its settings    -- create only if not created by the other object
    if (openDialog == NULL)
    {
        openDialog = new TOpenDialog(strGrid);
        openDialog->Filter = "Результаты измерений (*.bln)|*.bln|Все файлы|*.*";
        openDialog->Options.Clear();
        openDialog->Options << ofHideReadOnly << ofAllowMultiSelect <<
            ofFileMustExist << ofEnableSizing;
        openDialog->Title = "Укажите добавляемые файл(ы) ";
    }
}
//---------------------------------------------------------------------------

StrGrid::~StrGrid ()
{
// Deallocate memory

    if (openDialog != NULL)   // it's static...
        delete openDialog;
}
//--------------------------- PUBLIC ROUTINES ------------------------------

StrList StrGrid::ReadFileNames ()
{
// Read file names from the StringGrid

    StrList files;
    for (int i=0; i<filesCount; i++)
    {
        String name = ReadFileName(i);
        files.push_back (name);
    }
    return files;
}
//---------------------------------------------------------------------------

void StrGrid::WriteAndClearFileNames  (StrList fileNames)
{
// Write file names to strGrid. All exitings names are deleted.
// The function DOESN'T SORT, because it is used to read old projects.

    Clear();

    int size = fileNames.size();
    for (int i=0; i<size; i++)
        AddFileName (fileNames[i]);

    UpdateIndices();
}
//---------------------------------------------------------------------------

void StrGrid::Clear ()
{
// clear contents of the grid

    // clear widget
    strGrid->RowCount = 2;
    strGrid->Cells[0][1] = "";
    strGrid->Cells[1][1] = "";
    strGrid->Cells[2][1] = "";

    // update private var
    filesCount = 0;
}
//---------------------------------------------------------------------------

void StrGrid::SetDefaultExtention (String ext)
{
// Change file extention for OpenDialog
// The string must be "bln" or "dat". Else, it uses "bln".

    String extSmall = ext.LowerCase();
    if (extSmall == "dat")
        openDialog->Filter = "Неклиброваные файлы измерений (*.dat)|*.dat|Все файлы|*.*";
    else if (extSmall == "bln")
        openDialog->Filter = "Калиброваные файлы OBR_DN (*.bln)|*.bln|Все файлы|*.*";
    else
        assert(false);
}

//---------------------------------------------------------------------------

//----------------------- PUBLIC WIDGETS ROUTINES ---------------------------

void __fastcall StrGrid::OnRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{

    UpdateIndices();              // update indices of the rows.
    program->SetRPInputModified();      // project modified
}
//---------------------------------------------------------------------------


void StrGrid::AddFileWithDialogAndSort ()         // functions for buttons
{
// Open a fileOpenDialog with current file extention.
// Add its files, if dialog is not canceled.
// Performs sort too!

    if (!openDialog->Execute())
        return;                    // cancel

    int count = openDialog->Files->Count;          // add files
    // reading
    for (int i=0; i<count; i++)
    {
        String nextFile = openDialog->Files->Strings[i];
        AddFileName (nextFile);
    }

    SortFiles ();   //UpdateIndices() is here
    program->SetRPInputModified();
}
//---------------------------------------------------------------------------


void StrGrid::RemoveFile ()
{
// Remove the file on which str Grid is pointing.

    int index = strGrid->Row - 1;   // row = index+1
    DeleteFileName(index);
    program->SetRPInputModified();
}
//---------------------------------------------------------------------------

void StrGrid::SortFiles ()
{
// Sort files in string grid using A___M15.BLN-sort of parsing.

    const int defaultNumber = 1000; // a number for 'bad' file names

    // parse file names for numbers
    bool parsingOK = true;
    vector<int> Numbers;
    for (int i=0; i<filesCount; i++)
    {
        String fileName = ReadFileName (i);
        bool ok=false;
        int number = FindNumber (fileName, &ok);
        if (ok)
            Numbers.push_back (number);
        else
        {
            parsingOK = false;
            Numbers.push_back (defaultNumber);
        }
    }

    // find out the right order
    vector<SortingClass> sortVect;
    SortingClass element;
    for (int i=0; i<filesCount; i++)
    {
        element.number = i;
        element.value = Numbers[i];
        sortVect.push_back(element);
    }
    stable_sort (sortVect.begin(), sortVect.end(), MyCompare);

    // save all files
    StrList files = ReadFileNames ();

    int filesCountOld = filesCount;
    // clear the grid
    Clear();

    // add all files again
    for (int i=0; i<filesCountOld; i++)
    {
        int index = sortVect[i].number;
        AddFileName (files[index]);
    }
    UpdateIndices ();

    // report if any error
    if (!parsingOK)
        ShowMessage ("Не все имена файлов удалось распознать.\n"
            "Проверьте правильность сортировки самостоятельно.");

    program->SetRPInputModified();
}
//---------------------------------------------------------------------------



//---------------------------- PRIVATE ROUTINES -----------------------------

void StrGrid::UpdateIndices ()
{
// update first (0th) colomn - indices of files.

    if (filesCount == 0)
    {
        strGrid->Cells[0][1] = "";
        return;
    }

    int nMax = (filesCount-1)/2;         // from -nMax to nMax
    for (int i=1; i<=filesCount; i++)
        strGrid->Cells[0][i] = i-nMax-1;
}
//---------------------------------------------------------------------------


String StrGrid::ReadFileName (int index)
{
// Read file name #index. Index starts at 0.

    if ((index<0) || (index>=filesCount))
        return "";

    String path = strGrid->Cells[1][index+1];
    String name = strGrid->Cells[2][index+1];
    return path+name;
}
//---------------------------------------------------------------------------

void StrGrid::AddFileName (String newFileName)
{
// Add new fileName to the table (as a last entry).

    String path = ExtractFilePath (newFileName);
    String name = ExtractFileName (newFileName);

    if (filesCount>0)           // component's bug: cannot have <1 row.
        strGrid->RowCount++;    // add another row

    filesCount++;

    strGrid->Cells[1][filesCount] = path;
    strGrid->Cells[2][filesCount] = name;

    UpdateIndices ();
}
//---------------------------------------------------------------------------


void StrGrid::DeleteFileName (int index)
{
// Delete file name #index. Index starts at 0.

    // if no files, ignore
    if (filesCount == 0)
        return; // no need to UpdateIndices ();

    // if 1 file, just clear the 1st row
    else if (filesCount == 1)
    {
        strGrid->Cells[0][1] = "";
        strGrid->Cells[1][1] = "";
        strGrid->Cells[2][1] = "";
        filesCount = 0;
    }

    // if >1 files
    else
    {
        // copy rows from below
        for (int i = index; i < filesCount; i++)
            strGrid->Rows[i+1] = strGrid->Rows[i+2];

        // delete last row
        strGrid->RowCount--;
        // update filesCount
        filesCount--;
    }

    UpdateIndices ();
}
//---------------------------------------------------------------------------

int StrGrid::FindNumber(String fileName, bool* ok)
{
// Parses a file name and returnes its number (like *m15, *p30, ...)
// On error ok = false
// fileName can be in either format (abs or relative)

    int length = fileName.Length();

    // find out the position of the last digit
    int lastDigit = -1;
    for (int j = length; j>0; j--)
    {
        String c = fileName.SubString(j, 1);   // next char
        bool isDigit = (c=="0")||(c=="1")||(c=="2")||(c=="3")||
            (c=="4")||(c=="5")||(c=="6")||(c=="7")||(c=="8")||(c=="9");

        if (isDigit)
        {
            lastDigit = j;
            break;
        }
    }
    if  (lastDigit == -1)       // no digits found - bad filename.
    {
        *ok = false;
        return 0;
    }

    // find out the position of the first digit
    int firstDigit = lastDigit;
    for (int j = lastDigit; j>0; j--)
    {
        String c = fileName.SubString(j, 1);          // next char
        bool isDigit = (c=="0")||(c=="1")||(c=="2")||(c=="3")||
            (c=="4")||(c=="5")||(c=="6")||(c=="7")||(c=="8")||(c=="9");

        if (!isDigit)
            break;
        firstDigit = j;
    }

    // find out the absolute number
    int digitsCount = lastDigit-firstDigit+1;
    String strNumber = fileName.SubString(firstDigit, digitsCount);
    int absNumber = strNumber.ToInt();

    // check the previous symbol: must be 'p', 'm' or anything for n==0.
    if (firstDigit == 1) // no previous symbol - bad name
    {
        *ok = false;
        return 0;
    }
    int number = 0;
    String prevSymbol = fileName.SubString(firstDigit-1, 1);
    if ((prevSymbol=='m') || (prevSymbol=='M'))
        number = -absNumber;
    else if ((prevSymbol=='p') || (prevSymbol=='P'))
        number = absNumber;
    else if (absNumber == 0)
        number = 0;
    else                     // bad previous symbol
    {
        *ok = false;
        return 0;
    }

    *ok = true;
    return number;
}

