#ifndef TRIPLEGAUSS_V1
#define TRIPLEGAUSS_V1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TF2.h"

class TripleGauss_V1 : public RooAbsPdf {
public:
    TripleGauss_V1() {};
    TripleGauss_V1(
        const char *name, const char *title,
	    RooAbsReal& _xVar,
	    RooAbsReal& _yVar,
	    RooAbsReal& _x0,
	    RooAbsReal& _y0,
	    RooAbsReal& _w1N,
        RooAbsReal& _w1M,
	    RooAbsReal& _rho_N1,
	    RooAbsReal& _xWidthN1,
	    RooAbsReal& _yWidthN1,
	    RooAbsReal& _rho_M1,
	    RooAbsReal& _xWidthM1,
	    RooAbsReal& _yWidthM1,
	    RooAbsReal& _rho_W1,
	    RooAbsReal& _xWidthW1,
	    RooAbsReal& _yWidthW1,
	    RooAbsReal& _w2N,
	    RooAbsReal& _w2M,
	    RooAbsReal& _yWidthN2,
	    RooAbsReal& _yWidthM2,
	    RooAbsReal& _yWidthW2,
        RooAbsReal& _vtxRes
    );
    TripleGauss_V1(
        const char *name, const char *title,
	    RooAbsReal& _xVar,
	    RooAbsReal& _yVar,
	    RooAbsReal& _x0,
	    RooAbsReal& _y0,
	    RooAbsReal& _w1N,
        RooAbsReal& _w1M,
	    RooAbsReal& _rho_N1,
	    RooAbsReal& _xWidthN1,
	    RooAbsReal& _yWidthN1,
	    RooAbsReal& _rho_M1,
	    RooAbsReal& _xWidthM1,
	    RooAbsReal& _yWidthM1,
	    RooAbsReal& _rho_W1,
	    RooAbsReal& _xWidthW1,
	    RooAbsReal& _yWidthW1,
	    RooAbsReal& _w2N,
	    RooAbsReal& _w2M,
	    RooAbsReal& _yWidthN2,
	    RooAbsReal& _yWidthM2,
	    RooAbsReal& _yWidthW2,
        RooAbsReal& _vtxResX,
        RooAbsReal& _vtxResY
    );
    TripleGauss_V1(const TripleGauss_V1& other, const char* name=0);
    virtual TObject* clone(const char* newname) const {
        return new TripleGauss_V1(*this, newname);
    };
    inline virtual ~TripleGauss_V1() {};
protected:
    RooRealProxy xVar;
    RooRealProxy yVar;
    RooRealProxy x0;
    RooRealProxy y0;
    RooRealProxy w1N;
    RooRealProxy w1M;
    RooRealProxy rho_N1;
    RooRealProxy xWidthN1;
    RooRealProxy yWidthN1;
    RooRealProxy rho_M1;
    RooRealProxy xWidthM1;
    RooRealProxy yWidthM1;
    RooRealProxy rho_W1;
    RooRealProxy xWidthW1;
    RooRealProxy yWidthW1;
    RooRealProxy w2N;
    RooRealProxy w2M;
    RooRealProxy yWidthN2;
    RooRealProxy yWidthM2;
    RooRealProxy yWidthW2;
    RooRealProxy vtxResX;
    RooRealProxy vtxResY;

    TF2 *fitFuncN1N2 = new TF2("fitFuncN1N2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncN1M2 = new TF2("fitFuncN1M2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncN1W2 = new TF2("fitFuncN1W2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncM1N2 = new TF2("fitFuncM1N2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncM1M2 = new TF2("fitFuncM1M2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncM1W2 = new TF2("fitFuncM1W2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncW1N2 = new TF2("fitFuncW1N2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncW1M2 = new TF2("fitFuncW1M2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncW1W2 = new TF2("fitFuncW1W2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);

    Double_t evaluate() const;
private:
    ClassDef(TripleGauss_V1, 1)
};

#endif
