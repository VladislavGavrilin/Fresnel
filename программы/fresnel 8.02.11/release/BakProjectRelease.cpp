//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Program.h"
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", Form1);
USEFORM("PlotFrame.cpp", plot); /* TFrame: File Type */


//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TForm1), &Form1);


         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
