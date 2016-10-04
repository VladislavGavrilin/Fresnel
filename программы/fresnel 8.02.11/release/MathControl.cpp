#include "MathControl.h"
#include "GuiControl.h"  // for inputData-struct from GUI

#include <fstream>       // file r/w
#include <string>        // reading file line-by-line
#include <sstream>       // reading numbers from each line

#include <math>
#include <assert>


double round (double number)
{
// simple round operation

    return floor(number+0.5);    
}
//---------------------------------------------------------------------------

Math::Math()
{
// Set data to 0.

    // plot data settings
    phaseStraighten = false;
    normalizeRP = false;
    minAmp = 0;
}
//---------------------------------------------------------------------------

Math::~Math()
{
// The class seems to have no data in the heap. Nothing to clean up.
}
//---------------------------------------------------------------------------
bool Math::ReadAndReplaceInputData(StrList ampFiles, StrList phaseFiles,
                             String ampCalFile, String phaseCalFile, CalibrType calType)
{
// Reads input files (amp and phase) and stores the data in private variable.
// If one of the files is corrupt (cannot be read) it shows the message
// and quits. All the private input data becomes undefined!!! (clear it or delete the object)
// The amount of amp/phase files must be equal, else quits.


    // count data files (must have equal sizes)
    int count = ampFiles.size();
    int countPhase = phaseFiles.size();
    if (count != countPhase)
    {
        ShowMessage ("Количество файлов с амплитудой и с фазой не совпадает!");
        return false;
    }
    if (count == 0)
    {
        ShowMessage ("Не заданы файлы с амилтудно-фазовым распределением!");
        return false;
    }

    // clear class variables containing input data
    // (inputAmpRaw; inputPhaseRaw; inputAmpPlot; inputPhasePlot;)
    inputAmpRaw.clear();
    inputPhaseRaw.clear();
    inputAmpPlot.clear();
    inputPhasePlot.clear();

    // cycle through all the files (amp - phase, raw - plot simultaneously)
    // on error clear the class data, show message and quit.
    for (int i=0; i<count; i++)
    {
        // read the data (BLN/ DAT) - amp+phase
        Vect nextAmp, nextPhase;
        bool readAmpOK=false, readPhaseOK=false;
        if (calType == BLN)
        {
            nextAmp = ReadBLNOrExt (ampFiles[i], &readAmpOK);
            nextPhase = ReadBLNOrExt (phaseFiles[i], &readPhaseOK);
        }
        else if (calType == DAT)
        {
            nextAmp = ReadDAT (ampFiles[i], &readAmpOK);
            nextPhase = ReadDAT (phaseFiles[i], &readPhaseOK);
        }
        if (!(readAmpOK && readPhaseOK))
        {
            String badFile;
            if (!readAmpOK)
                badFile = ampFiles[i];
            else
                badFile = phaseFiles[i];
            String MessageStart = "Не удаётся прочитать файл: ";
            ShowMessage (MessageStart + badFile);

            inputAmpRaw.clear();
            inputPhaseRaw.clear();
            inputAmpPlot.clear();
            inputPhasePlot.clear();
            return false;
        }

        // sort arrays              - amp+phase
        SortArray(nextAmp);
        SortArray(nextPhase);

        // calibrate arrays        - amp+phase
        if (calType == BLN)
        {
            CalibrateBLNFormat (nextAmp, amp);
            CalibrateBLNFormat (nextPhase, phase);
        }
        else if (calType == DAT)
        {
            bool ampCalOK = CalibrateDATFormat (nextAmp, ampCalFile, amp);
            bool phaseCalOK = CalibrateDATFormat (nextPhase, phaseCalFile, phase);
            if (!(ampCalOK && phaseCalOK))
            {
                ShowMessage ("Невозможно провести калибровку.\n"
                    "Проверьте файлы калибровки.");

                inputAmpRaw.clear();
                inputPhaseRaw.clear();
                inputAmpPlot.clear();
                inputPhasePlot.clear();
                return false;
            }
        }

        // store arrays to class varables     - amp+phase
        inputAmpRaw.push_back(nextAmp);
        inputPhaseRaw.push_back(nextPhase);

        // fill in inputDataPlot using plot state variables and store it to class.
        Vect nextAmpPlot = CalcAmpPlotFromRaw (nextAmp, false);
        Vect nextPhasePlot = CalcPhasePlotFromRaw (nextPhase);

        inputAmpPlot.push_back(nextAmpPlot);
        inputPhasePlot.push_back(nextPhasePlot);

    }     // main cycle

    // no errors
    return true;
}
//---------------------------------------------------------------------------

bool Math::ReadAndRelpaceRPData(String ampFile, String phaseFile)
{
// Read two input files and save to class vars. No sorting, no calibration...
// On error return false.

    // read ampFile - raw and plot. on error, quit
    bool ampOK = false;
    Vect ampRaw = ReadBLNOrExt(ampFile, &ampOK);
    if (!ampOK)
    {
        ShowMessage ("Невозможно прочитать файл результатов");
        return false;
    }
    Vect ampPlot = CalcAmpPlotFromRaw(ampRaw, true);
    // save them
    rpAmpRaw = ampRaw;
    rpAmpPlot = ampPlot;

    // read and save phaseFile - raw and plot. on error, quit
    bool phaseOK = false;
    Vect phaseRaw = ReadBLNOrExt(phaseFile, &phaseOK);
    if (!phaseOK)
    {
        ShowMessage ("Невозможно прочитать файл результатов");
        return false;
    }
    Vect phasePlot = CalcPhasePlotFromRaw(phaseRaw);
    // save them
    rpPhaseRaw = phaseRaw;
    rpPhasePlot = phasePlot;

    // no errors
    return true;
}
//---------------------------------------------------------------------------


bool Math::CalculateAndReplaceInputAndRPData(RPInput rpInput,
                            double* shiftX, double* shiftY, double* maxRP)
{
// Read input data and calculate the RP data, phaseCenterShift, maxRP.
// It uses the guiModule for input information (struct RPInput).
//
// If the return value is false, the state of the math-objects becoms indefined!!!
// (clear the object or delete it).
//
// If an error occures the class itself reports about it.


    // Read data from GuiControl and test its values for validity (m=n, a>0, ...)
    bool dataOK = TestInputData(rpInput);
    if (!dataOK)        // error message was in TestInputData
        return false;
    
    // Read input files (StrGrid files)
    CalibrType calibr;                     // I should have used the same type...
    if (rpInput.calibr == dat)
        calibr = DAT;
    else
        calibr = BLN;

    bool readOK = ReadAndReplaceInputData (rpInput.ampFiles, rpInput.phaseFiles,
        rpInput.ampCalFile, rpInput.phaseCalFile, calibr);
    if (!readOK)    // error message was in the function
        return false;

    // Find out nMin, nMax, nAll, betaFirst
    int nMin=0, nAll=0;
    FindNMinAndNAll(rpInput.stepBeta, &nMin, &nAll);
    if (nAll < 2)
    {
        ShowMessage ("Невозможно провести восстановление.\n"
                "Провертье правильность входных файлов.");
        return false;
    }
    double betaFirst = nMin*rpInput.stepBeta;

    // Calculate coefficients
    double deltaAlpha = rpInput.stepAlpha;
    double lambda = 30./ rpInput.f;
    double r = rpInput.r;
    int nAlphaHalf = (rpInput.ampFiles.size()-1)/2;
    Vect_c alphaCoeffs = Make1DCoefficients (deltaAlpha, lambda, r, nAlphaHalf);

    double deltaBeta = rpInput.stepBeta;
    int nBetaHalf = rpInput.kHalfAmount;
    Vect_c betaCoeffs = Make1DCoefficients (deltaBeta, lambda, r, nBetaHalf);


    // Find out the location of the phase center
    // (calculate all RPs here - with some speed and memory optimization).
    int smallCount = ceil (rpInput.stepBeta/rpInput.stepBetaSmall);
    double stepBetaSmall = rpInput.stepBeta/ smallCount;

    int nX = floor (rpInput.dXHalfLength/ rpInput.dXdYStep + 0.5);    // ~round
    int nY = floor (rpInput.dYHalfLength/ rpInput.dXdYStep + 0.5);
    double stepXY = rpInput.dXdYStep;

    VectMN maxRPArray (2*nX+1, std::vector<double>(2*nY+1, 0));      // max values of RP with different shifts

    for (int iSmall=0; iSmall<smallCount; iSmall++)
    {
        // make a sampling-array without shifts
        double betaFirstNext = betaFirst + stepBetaSmall*iSmall;
        VectMN_c arrayNoShift = MakeInputSampling (betaFirstNext, deltaBeta, nAll);

        for (int iX=-nX; iX<=nX; iX++)
        {
            for (int iY=-nY; iY<=nY; iY++)
            {
                // make a sampling array with shifts
                double deltaX = rpInput.dXCenter + stepXY*iX;
                double deltaY = rpInput.dYCenter + stepXY*iY;
                VectMN_c arrayShifted = ShiftRotationCenter (arrayNoShift, deltaX, deltaY,
                          r, lambda, rpInput.stepAlpha, betaFirstNext, deltaBeta);

                // make a RP-array from array with shifts
                Vect_c RPShifted = ConvolutionSparse(alphaCoeffs, betaCoeffs, arrayShifted);
                // find out its MAX and save it to array of max'es
                double nextMax = MaxComplexValue(RPShifted);
                maxRPArray[iX+nX][iY+nY] = max (maxRPArray[iX+nX][iY+nY], nextMax);
            }
        }       // next shift
    }           // next beta0

    // now we can find out optimum shift and maxRP
    int iOpt=0, jOpt=0;
    FindMaxIJ(maxRPArray, &iOpt, &jOpt);
    double deltaXOpt = rpInput.dXCenter + stepXY*(iOpt-nX);
    double deltaYOpt = rpInput.dYCenter + stepXY*(jOpt-nY);

    double maxValue = maxRPArray[iOpt][jOpt];

    // new code for not normalized input (maxValue = maxRP - maxInput);
    double maxInput = FindMaxInputValue();
    double maxValue_dB = 20*log10(maxValue) - maxInput;


    // Based on phase center location, calculate the RP.
    Vect_c finalRP (smallCount*nAll);
    for (int iSmall=0; iSmall<smallCount; iSmall++)
    {
        // make a sampling-array without shifts
        double betaFirstNext = betaFirst + stepBetaSmall*iSmall;
        VectMN_c arrayNoShift = MakeInputSampling (betaFirstNext, deltaBeta, nAll);

        // array with proper shift
        VectMN_c arrayShifted = ShiftRotationCenter (arrayNoShift, deltaXOpt, deltaYOpt,
                          r, lambda, rpInput.stepAlpha, betaFirstNext, deltaBeta);
        // calculate RP
        Vect_c rpSparse = ConvolutionSparse(alphaCoeffs, betaCoeffs, arrayShifted);

        // fill in the final RP array
        for (int i=0; i<nAll; i++)
            finalRP [iSmall + i*smallCount] = rpSparse[i];
    }

    // fill in the private variables containing RP
    int countAll = smallCount*nAll;
    rpAmpRaw = Vect(countAll);
    rpPhaseRaw = Vect(countAll);
    for (int i=0; i<countAll; i++)
    {
        double nextBeta = betaFirst + i*stepBetaSmall;
        rpAmpRaw[i].x = nextBeta;       // it's still in degrees
        rpPhaseRaw[i].x = nextBeta;

        rpAmpRaw[i].y = 20*log10(abs(finalRP[i]));
        rpPhaseRaw[i].y = arg(finalRP[i]) *180/M_PI;
    }

    // return data
    *shiftX = deltaXOpt*10; // in millimeters
    *shiftY = deltaYOpt*10;
    *maxRP = maxValue_dB;

    return true; // all went well

}
//---------------------------------------------------------------------------

void Math::RemoveInputAndRPData()
{
// Clears input and RP data.
// Really, one can safely do without this function. - all data is in stack.

    inputAmpRaw.clear();               // input
    inputPhaseRaw.clear();
    inputAmpPlot.clear();
    inputPhasePlot.clear();

    rpAmpRaw = Vect(0);                // RP
    rpAmpPlot = Vect(0);
    rpPhaseRaw = Vect(0);
    rpPhasePlot = Vect(0);
}
//---------------------------------------------------------------------------

int Math::AddExternalData(String fileName, bool* ok)
{
// Reads external file and returns its handle (index).
// No sorting or calibration here. On error ok=false

    // read the file
    bool fileReadOK = false;
    Vect newData = ReadBLNOrExt(fileName, &fileReadOK);
    if (!fileReadOK)
    {
        ShowMessage ("Невозможно прочитать файл. Проверьте его формат.");
        *ok = false;
        return -1;
    }

    // find out the index (handle):
    //   search for a free one or add a new element to vector extDataRaw
    int length = extDataRaw.size();
    int index = -1;
    for (int i=0; i<length; i++)
    {
        if (extDataRaw[i].size() == 0) // we can use this element
        {
            index = i;
            break;
        }
    }
    if (index == -1) // no free elements => create one more element
    {
        index = length;
        extDataRaw.push_back ();
    }

    // write data to extDataRaw[index]
    extDataRaw[index] = newData;

    // results
    *ok = true;
    return index;
}
//---------------------------------------------------------------------------

void Math::RemoveExternalData(int dataID)
{
// Clear one item from extDataRaw.
// If the id<0 or >length-1 - ignore

    int maxID = extDataRaw.size()-1;
    if ((dataID<0) || (dataID>maxID))   // bad ID
        return;

    extDataRaw[dataID] = Vect(0);       // good ID => clear
}
//---------------------------------------------------------------------------

void Math::RemoveAllExternalData()
{
// Clear all ext. data.

    extDataRaw.clear();
}
//---------------------------------------------------------------------------

bool Math::SaveRPDataAsInPlot(AmpOrPhase ampOrPhase, String fileName)
{
// save RP plot data (for user) to file specified.
//on error (no data or cannot write) return false. No messages.

    // open the file for write              don't forget to close it later!
    std::ofstream file(fileName.c_str());
    if (file.fail())
        return false;

    // check the array
    Vect array;
    if (ampOrPhase == amp)
        array = rpAmpPlot;
    else if (ampOrPhase == phase)
        array = rpPhasePlot;

    int length = array.size();
    if (length == 0)
    {
        file.close();
        return false;
    }

    // write the array to file
    for (int i=0; i<length; i++)
    {
        file << array[i].x << "\t" << array[i].y << "\n";
    }

    // clean up
    file.close();
    return true;
}
//---------------------------------------------------------------------------

bool Math::SaveRPDataRaw(AmpOrPhase ampOrPhase, String fileName)
{
// save RP raw data (for Project class) to file specified.
//on error (no data or cannot write) return false. No messages.

    // open the file for write              don't forget to close it later!
    std::ofstream file(fileName.c_str());
    if (file.fail())
        return false;

    // check the array
    Vect array;
    if (ampOrPhase == amp)
        array = rpAmpRaw;
    else if (ampOrPhase == phase)
        array = rpPhaseRaw;

    int length = array.size();
    if (length == 0)
    {
        file.close();
        return false;
    }

    // write the array to file
    for (int i=0; i<length; i++)
    {
        file << array[i].x << "\t" << array[i].y << "\n";
    }

    // clean up
    file.close();
    return true;
}
//---------------------------------------------------------------------------

bool Math::ResultExists()
{
// Access function: any RP data?

    int size = rpAmpRaw.size();
    bool exist = (size>0);
    return exist;
}


//--------------------------- ACCESS FUNCTIONS ------------------------------

//------------------------------   SET     ----------------------------------
void Math::SetPlotPhaseStraighten(bool straighten)
{
// Use it each time you redraw the plot to update plot settings

    if (straighten != phaseStraighten)
    {
        phaseStraighten = straighten;
        UpdateAllPlotData ();
    }
}
//---------------------------------------------------------------------------

void Math::SetPlotNormalizeRP(bool normalize)
{
// Use it each time you redraw the plot to update plot settings

    if (normalize != normalizeRP)
    {
        normalizeRP = normalize;
        UpdateAllPlotData ();
    }
}
//---------------------------------------------------------------------------

void Math::SetPlotMinAmp(double newMinAmp)
{
// Use it each time you redraw the plot to update plot settings

    if (newMinAmp != minAmp)
    {
        minAmp = newMinAmp;
        UpdateAllPlotData ();
    }
}
//---------------------------------------------------------------------------

//-------------------------------   GET     ---------------------------------
// Access functions to PLOT data (for plot only!)

int Math::GetPlotInputCount()
{
// Access function

    return inputAmpPlot.size();
}

int Math::GetPlotInputLength(AmpOrPhase ampOrPhase, int index)
{
// Access function

    if (ampOrPhase == amp)
    {
        int arrCount = inputAmpPlot.size();
        if ((index < 0) || (index >= arrCount))  // bad index
            return 0;
        else
            return inputAmpPlot[index].size();
    }
    else // phase
    {
        int arrCount = inputPhasePlot.size();
        if ((index < 0) || (index >= arrCount))  // bad index
            return 0;
        else
            return inputPhasePlot[index].size();
    }
}

double Math::GetPlotInputData(AmpOrPhase ampOrPhase, ValueOrPhi valueOrPhi,
                                            int arrayIndex, int elementIndex)
{
// Access function

    // assuming all input is correct
    if (ampOrPhase == amp)
    {
        if (valueOrPhi == value)
           return inputAmpPlot[arrayIndex][elementIndex].y;
        else
           return inputAmpPlot[arrayIndex][elementIndex].x;
    }
    else // if (ampOrPhase == phase)
    {
        if (valueOrPhi == value)
           return inputPhasePlot[arrayIndex][elementIndex].y;
        else
           return inputPhasePlot[arrayIndex][elementIndex].x;
    }
}
//---------------------------------------------------------------------------

int Math::GetPlotRPLength(AmpOrPhase ampOrPhase)
{
// Access function

    if (ampOrPhase == amp)
        return rpAmpPlot.size();
    else
        return rpPhasePlot.size();
}

double Math::GetPlotRPData(AmpOrPhase ampOrPhase, ValueOrPhi valueOrPhi, int index)
{
// Access function

    int size;
    if (ampOrPhase == amp)
        size = rpAmpPlot.size();
    else
        size = rpPhasePlot.size();

    if ((index < 0) || (index >= size))     // bad index
        return 0;

    if (ampOrPhase == amp)
    {
        if (valueOrPhi == value)
            return rpAmpPlot[index].y;
        else
            return rpAmpPlot[index].x;
    }
    else
    {
        if (valueOrPhi == value)
            return rpPhasePlot[index].y;
        else
            return rpPhasePlot[index].x;
    }
}
//---------------------------------------------------------------------------

int Math::GetPlotExternalLength(int dataID)
{
// Access function

    int dataCount = extDataRaw.size();
    if ((dataID < 0) || (dataID >= dataCount))     // bad dataID
        return 0;

    return extDataRaw[dataID].size();
}

double Math::GetPlotExternalData(ValueOrPhi valueOrPhi, int dataID, int index)
{
// Access function

    int dataCount = extDataRaw.size();
    if ((dataID < 0) || (dataID >= dataCount))     // bad dataID
        return 0;

    int elCount = extDataRaw[dataID].size();
    if ((index < 0) || (index >= elCount))         // bad index
        return 0;

    if (valueOrPhi == value)
        return extDataRaw[dataID][index].y;
    else
        return extDataRaw[dataID][index].x;
}


//------------------------ PRIVATE ROUTINES ------------------------------

//---------------------------- FILE READ ---------------------------------

// new function to help read comma-separated data

void DeleteCommas (std::istringstream& stream)
{
    char ch;
    for (;;)
    {
        stream.get(ch);

        if (ch==',')
            return;

        if (stream.fail())
            return;
            
        if (!(ch==' ' || ch=='\t'))
        {
            if (!stream.fail())
                stream.putback(ch);
            return;
        }
    }
}

VectMN Math::ReadFileCustom (int colCount,
                                String fileName, bool* ok)
{
// Reading double-format data from a specified file.
// colCount shows the anticipated amount of colomns is the file.
// The amount of rows is determined here.

    // open file. (dont' forget to close it later)
    std::ifstream file(fileName.c_str());
    if (file.fail())
    {
        *ok = false;
        return VectMN (0, std::vector<double>(0));
    }

    // find out the amount of valid rows assuming colCount colomns.
    int rowCount = 0;
    while (!file.eof())
    {
        std::string buffer;               // reading next string
        std::getline(file, buffer);
        std::istringstream stream (buffer);

        double dummy;                     // trying to read colCount doubles
        for (int i=0; i<colCount; i++)    //   from the string
        {
            DeleteCommas (stream);
            stream >> dummy;
        }

        bool readOk = !stream.fail();
        if (readOk)                // read successful
            rowCount++;
        else                              // read failed
            break;
    }

    // if the amount of rows is 0, exit with an ok=false
    if (rowCount == 0)
    {
        file.close();
        *ok = false;
        return VectMN (0, std::vector<double>(0));
    }

    // create array (a vector)
    VectMN result (rowCount, std::vector<double>(colCount));

    // reading - no errors expected
//    file.seekg(0);  // - some problems with flags       // rewind the file
    file.close();
    file.clear();
    file.open(fileName.c_str());
    for (int row=0; row<rowCount; row++)
    {
        std::string buffer;               // reading next string
        std::getline(file, buffer);
        std::istringstream stream (buffer);

        for (int col=0; col<colCount; col++)    //   from the string
        {
            DeleteCommas (stream);
            double nextNumber;
            stream >> nextNumber;
            result[row][col] = nextNumber;                 
        }
    }

    // clean up
    file.close();
    *ok = true;
    return result;
}
//---------------------------------------------------------------------------

Vect Math::ReadBLNOrExt(String fileName, bool* ok)
{
// Read BLN-formatted files: 2 colomns

    // reading the file
    const int cols=2;
    bool readOK;
    VectMN array;
    array = ReadFileCustom (cols, fileName, &readOK);

    if (!readOK)
    {
        *ok = false;
        return Vect(0);
    }
    // allocating a dynamic array and filling it in
    int rows = array.size();
    Vect outArray(rows);
    for (int i=0; i<rows; i++)
    {
        outArray[i].x = array[i][0];
        outArray[i].y = array[i][1];
    }

    *ok = true;
    return outArray;
}
//---------------------------------------------------------------------------

Vect Math::ReadDAT(String fileName, bool* ok)
{
// Read DAT-formatted files: 6 colomns. 1st is phi, 4th is data.

    // reading the file
    const int cols=6;
    bool readOK;
    VectMN array;
    array = ReadFileCustom (cols, fileName, &readOK);

    if (!readOK)
    {
        *ok = false;
        return Vect(0);
    }
    // allocating a dynamic array and filling it in
    int rows = array.size();
    Vect outArray(rows);
    for (int i=0; i<rows; i++)
    {
        outArray[i].x = array[i][0];
        outArray[i].y = array[i][3];
    }

    *ok = true;
    return outArray;
}
//---------------------------------------------------------------------------

Vect Math::ReadCAL(String fileName, bool* ok)
{
// Read DAT-formatted files: 3 colomns. 1st is x, 3th is y (data).

    // reading the file
    const int cols=3;
    bool readOK;
    VectMN array;
    array = ReadFileCustom (cols, fileName, &readOK);

    if (!readOK)
    {
        *ok = false;
        return Vect(0);
    }
    // allocating a dynamic array and filling it in
    int rows = array.size();
    Vect outArray(rows);
    for (int i=0; i<rows; i++)
    {
        outArray[i].x = array[i][2];
        outArray[i].y = array[i][0];
    }

    *ok = true;
    return outArray;
}

//-------------------------- PROCESSING DATA -------------------------------

void Math::SortArray(Vect& oldArr)
{
// The function returns the array of sorted data. Array must be non-zero.
//
// The algorithm is very simple: reverse if need,
// and drop values appearing in descending order.

    int rowsIn = oldArr.size();

    // find out the direction
    bool reverseDirection;
    if (oldArr[0].x > oldArr[rowsIn-1].x)
        reverseDirection = true;
    else
        reverseDirection = false;

    // find out the new length
    int newLength = 1;
    if (!reverseDirection)
    {
        double lastValue = oldArr[0].x;
        for (int i=1; i<rowsIn; i++)
        {
            if (oldArr[i].x>lastValue) // in normal order
            {
                lastValue = oldArr[i].x;
                newLength++;
            }
            // else we have a value less then lastValue, skip it.
        }
    }
    else  // a reverse for-cycle
    {
        double lastValue = oldArr[rowsIn-1].x;
        for (int i=rowsIn-2; i>=0; i--)         // rowsIn-1 is lastValue. start with rowsIn-2.
        {
            if (oldArr[i].x>lastValue) // in normal order
            {
                lastValue = oldArr[i].x;
                newLength++;
            }
            // else we have a value less then lastValue, skip it.
        }
    }


    // create new array and fill it in.
    Vect newArr(newLength);
    if (!reverseDirection)
    {
        double lastValue = oldArr[0].x;
        int index=0;
        newArr[index].x = oldArr[0].x;
        newArr[index].y = oldArr[0].y;
        index++;

        for (int i=1; i<rowsIn; i++)
        {
            if (oldArr[i].x>lastValue) // in normal order
            {
                lastValue = oldArr[i].x;
                newArr[index].x = oldArr[i].x;
                newArr[index].y = oldArr[i].y;
                index++;
            }
            // else we have a value less then lastValue, skip it.
        }

        assert(index==newLength);
    }
    else  // a reverse for-cycle
    {
        double lastValue = oldArr[rowsIn-1].x;
        int index=0;
        newArr[index].x = oldArr[rowsIn-1].x;
        newArr[index].y = oldArr[rowsIn-1].y;
        index++;

        for (int i=rowsIn-2; i>=0; i--)         // rowsIn-1 is lastValue. start with rowsIn-2.
        {
            if (oldArr[i].x>lastValue) // in normal order
            {
                lastValue = oldArr[i].x;
                newArr[index].x = oldArr[i].x;
                newArr[index].y = oldArr[i].y;
                index++;
            }
            // else we have a value less than lastValue, skip it.
        }

        assert(index==newLength);
    }

    oldArr = newArr;
}
//---------------------------------------------------------------------------

void Math::CalibrateBLNFormat(Vect& array, AmpOrPhase fileType)
{
// Calibrating BLN-formatted data: 2 colomns which represent
//        Amp:    phi(degrees) and amp(in dB)
//        Phase:  phi(degrees) and phase(degrees/10)

    // amp data - just skip
    if (fileType == amp)
        return;

    // phase data - phase=phase*10;
    if (fileType == phase)
    {
        int rows = array.size();
        for (int i=0; i<rows; i++)
            array[i].y = array[i].y*10;
    }
}
//---------------------------------------------------------------------------

bool Math::CalibrateDATFormat(Vect& array, String calFile, AmpOrPhase fileType)
{
// Trying to calibrate the file based on calFile-calibration scale.
// If calFile is bad, returns false.

    // reading calFile
    bool calOK;
    Vect calData = ReadCAL(calFile, &calOK);
    if (!calOK)
        return false;
    int calRows = calData.size();

/*    // inverting the sign of the dB - strange feature of the file format
    bool x1_gt_xn = (calData[0].x > calData[calRows-1].x);
    bool y1_gt_yn = (calData[0].y > calData[calRows-1].y);

    bool needInvert = (x1_gt_xn && (!y1_gt_yn)) ||      // y- ascend, x- descend
                ((!x1_gt_xn) && y1_gt_yn);              // x- ascend, y- descend



    if (needInvert)
    {                        */
        for (int i=0; i<calRows; i++)
            calData[i].y = -calData[i].y;     // dB -> -dB
/*    }                      */
// well, let's invert phase always, too.
// it seems that it's always necessary

    // sorting calData
    SortArray(calData);

    // interpolation
    int rows = array.size();
    for (int i=0; i<rows; i++)
        array[i].y = InterpolateDAT (array[i].y, calData);

    // phase *=10
    if (fileType == phase)
    {
        for (int i=0; i<rows; i++)
            array[i].y *= 10;
    }

    return true;
}
//---------------------------------------------------------------------------

Vect Math::CalcAmpPlotFromRaw(const Vect&  rawArray, bool isRP)
{
// Copies data and cuts it to minAmp value
// If isRP it also uses normalization (if normalizeRP=true)

    int rows = rawArray.size();
    Vect plotArray (rows);

    if (rows == 0)             // no data - no calculations
        return plotArray;

    if (isRP && normalizeRP)   // normalize
    {
        // find out max
        double max = rawArray[0].y;
        for (int i=0; i<rows; i++)
        {
            if (rawArray[i].y>max)
                max = rawArray[i].y;
        }

        // copy (data-max) to plotArray
        for (int i=0; i<rows; i++)
        {
            plotArray[i].x = rawArray[i].x;
            plotArray[i].y = rawArray[i].y - max;
        }
    }
    else                        // don't normalize
    {
        // just copy the data
        plotArray = rawArray;
    }

    // cut the data below minAmp level
    for (int i=0; i<rows; i++)
    {
        if(plotArray[i].y<minAmp)
            plotArray[i].y = minAmp;
    }

    return plotArray;
}
//---------------------------------------------------------------------------

Vect Math::CalcPhasePlotFromRaw(const Vect& rawArray)
{
// Copies data and straightens phase if phaseStraighten=true
//
// (algorithm is very simple - just see that abs(a-b)<180 degrees)
// Data is in degrees! Array must be sorted.

    // copy arrays
    Vect plotArray = rawArray;

    // if phaseStraighten==false, don't do other calculations
    if (!phaseStraighten)
        return plotArray;

    // a zero-size check
    int rows = plotArray.size();
    if (rows==0)
        return plotArray;

    // straighten the phase
    double lastPhase = plotArray[0].y;
    for (int i=1; i<rows; i++)         // start from second element
    {
        // find out how many 360-degrees to add/ subtract
        double diff = lastPhase - plotArray[i].y;
        double times = round(diff/360);
        // calculate next plotArray, update lastPhase
        plotArray[i].y = plotArray[i].y + times*360;
        lastPhase = plotArray[i].y;
    }

    return plotArray;
}
//---------------------------------------------------------------------------

double Math::InterpolateDAT (double x, const Vect& calData)
{
// Simple linear interpolation.
// the calData-array must be sorted by x-coordinate.

    double result=0;
    int calRows = calData.size();

    // handle x<=x0
    if (x<=calData[0].x)
    {
        // find out defivative
        double d_y = calData[1].y - calData[0].y;
        double d_x = calData[1].x - calData[0].x;
        double deriv = d_y/d_x;

        // approximate
        double delta_x = calData[0].x - x;
        result = calData[0].y - delta_x*deriv;
    }

    // handle x0<=x <= xn
    else if (x<=calData[calRows-1].x)
    {
        // find out k: x_k<= x0 <=x_k+1
        int k=0;
        for (int i=1; i<calRows; i++)
        {
            if(x<=calData[i].x)
            {
                k = i-1;
                break;
            }
        }
        // find out defivative
        double d_y = calData[k+1].y - calData[k].y;
        double d_x = calData[k+1].x - calData[k].x;
        double deriv = d_y/d_x;

        // approximate
        double delta_x = x - calData[k].x;
        result = calData[k].y + delta_x*deriv;
    }

    // handle x>xn
    else
    {
        // find out defivative
        double d_y = calData[calRows-1].y - calData[calRows-2].y;
        double d_x = calData[calRows-1].x - calData[calRows-2].x;
        double deriv = d_y/d_x;

        // approximate
        double delta_x = x - calData[calRows-1].x;
        result = calData[calRows-1].y + delta_x*deriv;
    }
               
    return result;
}
//---------------------------------------------------------------------------

void Math::UpdateAllPlotData()
{
// Update all plot data. Use it in access functions "set plot settings".

    // update input data - amp+phase
    int length = inputAmpPlot.size();
    for (int i=0; i<length; i++)
    {
        Vect nextAmp = inputAmpRaw[i];
        Vect nextPhase = inputPhaseRaw[i];

        inputAmpPlot[i] = CalcAmpPlotFromRaw (nextAmp, false);
        inputPhasePlot[i] = CalcPhasePlotFromRaw (nextPhase);
    }

    // update RP data    - amp+phase
    rpAmpPlot = CalcAmpPlotFromRaw(rpAmpRaw, true);
    rpPhasePlot = CalcPhasePlotFromRaw(rpPhaseRaw);
}
//---------------------------------------------------------------------------




//----------------------- RP CALCULATION ROUTINES --------------------------

VectMN_c Math::MakeInputSampling(double beta0, double deltaBeta, int pointsCount)
{
// Calculate a sampling with step deltaBeta starting from beta0 with pointsCount points
// deltaPsi is usually a BIG step (not deltaBetaSmall).

    int pointsAlpha = inputAmpRaw.size();

    // pointsAlpha-by-pointsCount array
    VectMN_c array(pointsAlpha, std::vector<std::complex <double> >(pointsCount,0));

    // Fill in the amplitude to the array.
    for (int iAlpha=0; iAlpha<pointsAlpha; iAlpha++)
    {
        int rawArrayIndex = 0;  // index of an element in 'inputAmpRaw[iAlpha]'
        for (int iBeta=0; iBeta<pointsCount; iBeta++)
        {
            double betaCurr = beta0 + deltaBeta*iBeta;
            // find out the point p in inputAmpRaw:    p_prev < betaCurr <= p
            // it cann't be infinite:     betaCurr_last<=input_last-deltaSmall
            while (betaCurr > inputAmpRaw[iAlpha][rawArrayIndex].x)
                rawArrayIndex++;

            // use linear interpolation of amplitude
            double x1 = inputAmpRaw[iAlpha][rawArrayIndex-1].x;
            double x2 = inputAmpRaw[iAlpha][rawArrayIndex].x;
            double y1 = inputAmpRaw[iAlpha][rawArrayIndex-1].y;
            double y2 = inputAmpRaw[iAlpha][rawArrayIndex].y;

            double deriv = (y2-y1)/(x2-x1);
            double dx = betaCurr - x1;
            double value_dB = y1 + dx*deriv;
            double value = pow(10, value_dB/20);

            array[iAlpha][iBeta] = value;
         }
    }


    // Calculate the phase and    *=exp(1j*phase)
    for (int iAlpha=0; iAlpha<pointsAlpha; iAlpha++)
    {
        int rawArrayIndex = 0;  // index of an element in 'inputPhaseRaw[iAlpha]'
        for (int iBeta=0; iBeta<pointsCount; iBeta++)
        {
            double betaCurr = beta0 + deltaBeta*iBeta;
            // find out the point p in inputPhaseRaw:    p_prev < betaCurr <= p
            // it cann't be infinite:     betaCurr_last<=input_last-deltaSmall
            while (betaCurr > inputPhaseRaw[iAlpha][rawArrayIndex].x)
                rawArrayIndex++;

            // use linear interpolation of amplitude
            double x1 = inputPhaseRaw[iAlpha][rawArrayIndex-1].x;
            double x2 = inputPhaseRaw[iAlpha][rawArrayIndex].x;
            double y1 = inputPhaseRaw[iAlpha][rawArrayIndex-1].y;
            double y2 = inputPhaseRaw[iAlpha][rawArrayIndex].y;

            if (abs(y1-y2)>180)     // 360-deg. period stuff
            {
                int k = floor((y2-y1)/360 + 0.5); // ~round(dy/360).
                y2 = y2-k*360;
            }

            double deriv = (y2-y1)/(x2-x1);
            double dx = betaCurr - x1;
            double value_deg = y1 + dx*deriv;
            std::complex<double> value = polar(1, value_deg*M_PI/180);

            array[iAlpha][iBeta] *= value;
         }
    }

    return array;
}
//---------------------------------------------------------------------------

VectMN_c Math::ShiftRotationCenter(const VectMN_c& baseInput, double deltaX, double deltaY,
    double r, double lambda, double deltaAlpha, double beta0, double deltaBeta)
{
// a.k.a. Phase center shift.
// Calculate input data as if the rotations center was shifted  (change only phase)
//
// I should have used a separate class for calculations core.
// It wouldn't have that many parameters then.

    int alphaCount = baseInput.size();
    assert (alphaCount>0);  // it shouldn't be empty!
    int betaCount = baseInput[0].size();

    double alpha0 = -( (betaCount-1)/2 ) * deltaAlpha;    // we count from -alphaMax to +alphaMax
                                                          // (as in StringGrid)
    VectMN_c array = baseInput; // copy the whole array

    for (int iAlpha=0; iAlpha<alphaCount; iAlpha++)
    {
        for (int iBeta=0; iBeta<betaCount; iBeta++)
        {
            // calculate r_new
            double alpha = (alpha0 + iAlpha*deltaAlpha) *M_PI/180;    // in radians
            double beta = (beta0 + iBeta*deltaBeta) *M_PI/180;        // in radians

            double rNew = sqrt ( pow (r*sin(alpha) - deltaX, 2) +
                       pow (r*cos(alpha)*sin(beta) - deltaY, 2) +
                                         pow (r*cos(alpha)*cos(beta),2) );

            double deltaPhase = (rNew-r)/lambda * 2*M_PI;
            std::complex<double> factor = polar(1, deltaPhase);
            array[iAlpha][iBeta] *= factor;
        }
    }

    return array;
}
//---------------------------------------------------------------------------

Vect_c Math::Make1DCoefficients(double deltaAngle, double lambda, double r, int n)
{
// Making array k_mn using Fortran's f2c'ed fucntion SF45R from MSU.
// deltaAngle goes into the function in degrees,
// and here it is translated to radians.
// n = (nAll-1)/2, i.e. nAll = 2n+1.     - amount of coefficients

    double deltaRadians = deltaAngle*M_PI/180.;
    double txy = lambda/deltaRadians;

    double a = -txy/2;
    double b = txy/2;
    double c = M_PI/lambda/r;
    double d1 = 2*M_PI/txy;

    Vect_c k(2*n+1);

    for (int i=0; i<=n; i++)    //  -n, -n+1,... , +n
    {
        k[n+i] = CalculateOneCoefficient(a,b,c,d1*i);
        k[n-i] = k[n+i];  // for i==0 it's OK, too
    }
    return k;
}
//---------------------------------------------------------------------------

Vect_c Math::ConvolutionSparse(const Vect_c& coeffsAlpha,
                const Vect_c& coeffsBeta, const VectMN_c& samples)
{
// Caluclate RP using coefficients and samples of input data (with step deltaBetaBIG)

    int alphaCount = coeffsAlpha.size();
    int betaCount = coeffsBeta.size();
    int length = samples[0].size();

    // convolution with respect to alpha
    Vect_c convByAlpha (length,0);   // a temporary array
    for (int i=0; i<length; i++)
    {
        for (int iAlpha=0; iAlpha<alphaCount; iAlpha++)
            convByAlpha[i] += coeffsAlpha[iAlpha]*samples[iAlpha][i];
    }

    // final convolution with respect to beta
    Vect_c array (length,0);            // result
    int betaHalf = (betaCount-1)/2;
    for (int i=0; i<length; i++)
    {
        int iBetaFirst = max(-i, -betaHalf);        // edge effects
        int iBetaLast = min(length-1-i, betaHalf);
        for (int iBeta=iBetaFirst; iBeta<=iBetaLast; iBeta++)  // -betaHalf,...,betaHalf - most of the time
        {
            int iBetaForCoeffs = iBeta + betaHalf;      // array indices
            int iBetaForConv = i + iBeta;
            array[i] += coeffsBeta[iBetaForCoeffs]*convByAlpha[iBetaForConv];
        }
    }

    return array;
}
//---------------------------------------------------------------------------

double Math::MaxComplexValue(const Vect_c& vect)
{
// Find out the biggest value of a complex vector.
// (I should have used some math template library instead of STL vectors)

    int size = vect.size();
    if (size==0)
        return 0;

    double value = abs(vect[0]);
    for (int i=0; i<size; i++)
    {
        double nextValue = abs(vect[i]);
        if (nextValue>value)
            value = nextValue;
    }
    return value;
}
//---------------------------------------------------------------------------

void Math::FindMaxIJ(VectMN array, int* iOut, int* jOut)
{
// Find max element in the martix of maxRP - for Phase center shift.
// array must of course be rectangula (equal elements in rows).

    int iMax = array.size();
    if (iMax==0)                 // empty array
    {
        *iOut=0;
        *jOut=0;
        return;
    }

    int jMax = array[0].size();
    if (jMax==0)                 // empty array
    {
        *iOut=0;
        *jOut=0;
        return;
    }

    double maxValue=array[0][0];
    int iOpt=0, jOpt=0;
    for (int i=0; i<iMax; i++)
    {
        for (int j=0; j<jMax; j++)
        {
            if (array[i][j] > maxValue)
            {
                maxValue = array[i][j];
                iOpt = i;
                jOpt = j;
            }
        }
    }

    *iOut = iOpt;
    *jOut = jOpt;
}
//---------------------------------------------------------------------------

complex<double> Math::CalculateOneCoefficient(double a, double b, double c, double d)
{
// Calculating one coefficient given some parameters.
// This code is a reused version of Fortran code...

    double aNew = (a-d/(2*c)) * sqrt(c);
    double bNew = (b-d/(2*c)) * sqrt(c);
    
    double phase = d*d / (4*c);

    complex<double> intA = fresnel(aNew);
    complex<double> intB = fresnel(bNew);

    complex<double> k1 = 1/(b-a) * conj(intB-intA) * (1/sqrt(c)) * polar(1,phase);

    return k1;
}
//---------------------------------------------------------------------------


bool Math::TestInputData(RPInput rpInput)
{
// Check if the data is OK (m=n, a>0,..)
// On error report it and return false.

    if (rpInput.r <= 0)
    {
        ShowMessage ("Расстояние должно быть положительно!");
        return false;
    }

    if (rpInput.f <= 0)
    {
        ShowMessage ("Частота должна быть положительна!");
        return false;
    }

    if (rpInput.dXHalfLength < 0)
    {
        ShowMessage ("Диапазоны сдвигов должны быть неотрицательными!");
        return false;
    }

    if (rpInput.dYHalfLength < 0)
    {
        ShowMessage ("Диапазоны сдвигов должны быть неотрицательными!");
        return false;
    }

    if (rpInput.dXdYStep <= 0)
    {                             // only counts if there is any shift
        if ((rpInput.dXHalfLength>0) || (rpInput.dYHalfLength>0))
        {
            ShowMessage ("Шаг сдвигов должен быть положительным!");
            return false;
        }
    }

    if (rpInput.kHalfAmount <= 0)
    {
        ShowMessage ("Количество коэффициентов должно быть положительно!");
        return false;
    }

    if (rpInput.stepAlpha <= 0)
    {
        ShowMessage ("Угловой шаг должен быть положителен!");
        return false;
    }

    if (rpInput.stepBeta <= 0)
    {
        ShowMessage ("Угловой шаг должен быть положителен!");
        return false;
    }

    if (rpInput.stepBetaSmall <= 0)
    {
        ShowMessage ("Угловой шаг должен быть положителен!");
        return false;
    }

    int ampCount = rpInput.ampFiles.size();
    int phaseCount = rpInput.phaseFiles.size();

    if (ampCount == 0)
    {
        ShowMessage ("Не заданы файлы амплитудного распределения!");
        return false;
    }

    if (phaseCount == 0)
    {
        ShowMessage ("Не заданы файлы фазового распределения!");
        return false;
    }

    if (ampCount != phaseCount)
    {
        ShowMessage ("Количество файлов амплитудного и фазового распределения\n"
                "должно совпадать!");
        return false;
    }

    if ((ampCount%2) != 1)
    {
        ShowMessage ("Количество входных файлов амплитудного распределения"
                "должно быть нечётным!");
        return false;
    }

    if (rpInput.calibr == dat)
    {
        if (rpInput.ampCalFile == "")
        {
            ShowMessage ("Не задан файл калибровки амплитуды!");
            return false;
        }
        if (rpInput.phaseCalFile == "")
        {
            ShowMessage ("Не задан файл калибровки фазы!");
            return false;
        }
    }

    return true;
}
//---------------------------------------------------------------------------

void Math::FindNMinAndNAll(double stepBeta, int* nMin, int* nAll)
{
// Find out the parameters mentioned

    int alphaCount = inputAmpRaw.size();

    // find out the common minimum
    double comMin = inputAmpRaw[0][0].x;               // amplitude
    for (int i=0; i<alphaCount; i++)
    {
        double nextMin = inputAmpRaw[i][0].x;
        if (nextMin > comMin)
            comMin = nextMin;
    }
    for (int i=0; i<alphaCount; i++)                   // phase
    {
        double nextMin = inputPhaseRaw[i][0].x;
        if (nextMin > comMin)
            comMin = nextMin;
    }

    // find out the common maximum
    int end0 = inputAmpRaw[0].size();                 // amplitude
    double comMax = inputAmpRaw[0][end0-1].x;
    for (int i=0; i<alphaCount; i++)
    {
        int nextEnd = inputAmpRaw[i].size();
        double nextMax = inputAmpRaw[i][nextEnd-1].x;
        if (nextMax < comMax)
            comMax = nextMax;
    }
    for (int i=0; i<alphaCount; i++)                  // phase
    {
        int nextEnd = inputPhaseRaw[i].size();
        double nextMax = inputPhaseRaw[i][nextEnd-1].x;
        if (nextMax < comMax)
            comMax = nextMax;
    }


    // find out integers
    int minInt = ceil (comMin/stepBeta);
    int maxInt = floor (comMax/stepBeta);
    int count = maxInt - minInt; // amount of points: (it was '...-2' "just for not bothering")

    *nMin = minInt;
    *nAll = count;
}
//---------------------------------------------------------------------------

void Math::CopyExtDataFrom(Math* oldMath)
{
// Copy ext data from old Math object to new one.
// It's due to bad program design.

    extDataRaw = oldMath->extDataRaw;
}
//---------------------------------------------------------------------------

double Math::FindMaxInputValue()
{
// Find max value of input data.
// For use in Calc-function.

    int alphaCount = inputAmpRaw.size();

    if (alphaCount == 0)
        return 0;           // no data

    int firstCount = inputAmpRaw[0].size();
    if (firstCount == 0)
        return 0;           // no data (it seems to be invalid)

    double comMax = inputAmpRaw[0][0].y;
    for (int i=0; i<alphaCount; i++)
    {
        int length_i =inputAmpRaw[i].size();
        for (int pos=0; pos<length_i; pos++)
        {
            double nextPoint = inputAmpRaw[i][pos].y;
            if (nextPoint > comMax)
                comMax = nextPoint;
        }
    }
    return comMax;
}
