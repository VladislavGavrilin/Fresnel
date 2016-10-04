#ifndef MathControlH
#define MathControlH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <complex>
#include "StrGrid.h"  // typedef vector<String> StrList;
#include "GuiControl.h"  // for inputData-struct from GUI


complex<double> fresnel (double x);     // fortran function for Fresnel integral

enum ValueOrPhi
{
// It's used as an argument to functions
// to find out if we want the 'X' or the 'Y'

    value, phi
};
//---------------------------------------------------------------------------

enum AmpOrPhase
{
// It's used as an argument to function
// to find out if we want Amplitude of Phase

    amp, phase
};
//---------------------------------------------------------------------------

enum CalibrType
{
// It's used as an argument to function
// to find out if we want DAT or BLN calibration

    DAT, BLN
};

//---------------------------------------------------------------------------

struct point
{
// use this structure as basic element for vectors to store data
    double x;
    double y;
};

typedef std::vector<point> Vect;  // a type for all 2-by-N arrays. Try not to use dynamic arrays (in heap).
                                  // var.size() is the N (length)
                                  // You can also use:  b = a;              - copy vectors
                                  //        point p={10,20}; Vect v(100,p); - initialization.
                                  
typedef std::vector<std::vector <double> > VectMN;        // a type for real M-by-N arrays.

typedef std::vector<std::vector <std::complex <double> > > VectMN_c; // a type for complex M-by-N arrays.
typedef std::vector<std::complex <double> > Vect_c;                  // a type for complex 1D arrays.
//---------------------------------------------------------------------------

class Math
{
// The class stores math data and performs calculations.

// IMPORTANT convention: all data is stored in _dB_,  _degress_ and cantimeters!!!

public:
    Math();
    ~Math();
    bool ReadAndReplaceInputData(StrList ampFiles, StrList phaseFiles,
                    String ampCalFile, String phaseCalFile, CalibrType calType);
    bool ReadAndRelpaceRPData(String ampFile, String phaseFile);
    bool CalculateAndReplaceInputAndRPData(RPInput rpInput, double* shiftX, double* shiftY, double* maxRP);
    void RemoveInputAndRPData();
    int AddExternalData(String fileName, bool* ok);
    void RemoveExternalData(int dataID);
    void RemoveAllExternalData();
    bool SaveRPDataAsInPlot(AmpOrPhase ampOrPhase, String fileName);
    bool SaveRPDataRaw(AmpOrPhase ampOrPhase, String fileName);
    bool ResultExists();

    void SetPlotPhaseStraighten(bool straighten);   // set plot settings
    void SetPlotNormalizeRP(bool normalize);
    void SetPlotMinAmp(double newMinAmp);

    int GetPlotInputCount();                        // plot input
    int GetPlotInputLength(AmpOrPhase ampOrPhase, int index);
    double GetPlotInputData(AmpOrPhase ampOrPhase, ValueOrPhi valueOrPhi, int arrayIndex, int elementIndex);

    int GetPlotRPLength(AmpOrPhase ampOrPhase);     // plot RP
    double GetPlotRPData(AmpOrPhase ampOrPhase, ValueOrPhi valueOrPhi, int index);

    int GetPlotExternalLength(int dataID);          // plot external
    double GetPlotExternalData(ValueOrPhi valueOrPhi, int dataID, int index);

    void CopyExtDataFrom(Math* oldMath);         // bad design...


private:      
    // private copy constructor - to forbid 'a=b' operations.
    Math(const Math& math) {};

    // private data
    bool phaseStraighten;   // plot's data settings
    bool normalizeRP;
    double minAmp;

                          // input data
    std::vector<Vect> inputAmpRaw;           // 'Raw' is stored between calculations of RP
    std::vector<Vect> inputPhaseRaw;         // 'Plot' is generated for plot
    std::vector<Vect> inputAmpPlot;          // each time it changes its view mode
    std::vector<Vect> inputPhasePlot;        // (i.e. plot's data settings)
                                      // all arrays normally have equal amount of Vects
                           // RP data
    Vect rpAmpRaw;
    Vect rpPhaseRaw;
    Vect rpAmpPlot;
    Vect rpPhasePlot;

                            // external data. Note, that this data is not sorted (for some reason...)
    std::vector<Vect> extDataRaw;     // there can be free elements here (if some elements get deleted)
                                      // they can be used later

    // private routines
    VectMN ReadFileCustom (int colCount, String fileName, bool* ok);   // reading files
    Vect ReadBLNOrExt(String fileName, bool* ok);
    Vect ReadDAT(String fileName, bool* ok);
    Vect ReadCAL(String fileName, bool* ok);

    void SortArray(Vect& oldArr);                               // process arrays
    void CalibrateBLNFormat(Vect& array, AmpOrPhase fileType);
    bool CalibrateDATFormat(Vect&  array, String calFile, AmpOrPhase fileType);
    Vect CalcAmpPlotFromRaw(const Vect& rawArray, bool isRP);
    Vect CalcPhasePlotFromRaw(const Vect& rawArray);
    double InterpolateDAT (double rawData, const Vect& calData);
    void UpdateAllPlotData();

    // RP calculation routines   -  I should have used a separate class for it
    VectMN_c MakeInputSampling(double phi0, double deltaPsi, int pointsCount);
    VectMN_c ShiftRotationCenter(const VectMN_c& baseInput, double deltaX, double deltaY,
         double r, double lambda, double deltaAlpha, double beta0, double deltaBeta);
    Vect_c Make1DCoefficients(double deltaAngle, double lambda, double r, int n);
    Vect_c ConvolutionSparse(const Vect_c& coeffsAlpha, const Vect_c& coeffsBeta, const VectMN_c& samples);
    double MaxComplexValue(const Vect_c& vect);
    void FindMaxIJ(VectMN array, int* i, int* j);
    complex<double> CalculateOneCoefficient(double a, double b, double c, double d);
    bool TestInputData(RPInput rpInput);
    void FindNMinAndNAll(double stepBeta, int* nMin, int* nAll);
    double FindMaxInputValue();

};

extern Math* math;


//---------------------------------------------------------------------------
#endif
 