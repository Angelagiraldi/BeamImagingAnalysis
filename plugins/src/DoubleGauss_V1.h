#ifndef DOUBLEGAUSS_V1
#define DOUBLEGAUSS_V1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TF2.h"

class DoubleGauss_V1 : public RooAbsPdf {
public:
    DoubleGauss_V1() {};
    DoubleGauss_V1(
        const char *name, const char *title,
	    RooAbsReal& _xVar,
	    RooAbsReal& _yVar,
	    RooAbsReal& _x0,
	    RooAbsReal& _y0,
	    RooAbsReal& _w1,
	    RooAbsReal& _rho_N1,
	    RooAbsReal& _xWidthN1,
	    RooAbsReal& _yWidthN1,
	    RooAbsReal& _rho_W1,
	    RooAbsReal& _xWidthW1,
	    RooAbsReal& _yWidthW1,
	    RooAbsReal& _w2,
	    RooAbsReal& _yWidthN2,
	    RooAbsReal& _yWidthW2,
        RooAbsReal& _vtxRes
    );
    DoubleGauss_V1(
        const char *name, const char *title,
	    RooAbsReal& _xVar,
	    RooAbsReal& _yVar,
	    RooAbsReal& _x0,
	    RooAbsReal& _y0,
	    RooAbsReal& _w1,
	    RooAbsReal& _rho_N1,
	    RooAbsReal& _xWidthN1,
	    RooAbsReal& _yWidthN1,
	    RooAbsReal& _rho_W1,
	    RooAbsReal& _xWidthW1,
	    RooAbsReal& _yWidthW1,
	    RooAbsReal& _w2,
	    RooAbsReal& _yWidthN2,
	    RooAbsReal& _yWidthW2,
        RooAbsReal& _vtxResX,
        RooAbsReal& _vtxResY
    );
    DoubleGauss_V1(const DoubleGauss_V1& other, const char* name=0);
    virtual TObject* clone(const char* newname) const {
        return new DoubleGauss_V1(*this, newname);
    };
    inline virtual ~DoubleGauss_V1() {};
protected:
    RooRealProxy xVar;
    RooRealProxy yVar;
    RooRealProxy x0;
    RooRealProxy y0;
    RooRealProxy w1;
    RooRealProxy rho_N1;
    RooRealProxy xWidthN1;
    RooRealProxy yWidthN1;
    RooRealProxy rho_W1;
    RooRealProxy xWidthW1;
    RooRealProxy yWidthW1;
    RooRealProxy w2;
    RooRealProxy yWidthN2;
    RooRealProxy yWidthW2;
    RooRealProxy vtxResX;
    RooRealProxy vtxResY;

    TF2 *fitFuncN1N2 = new TF2("fitFuncN1N2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncN1W2 = new TF2("fitFuncN1W2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncW1N2 = new TF2("fitFuncW1N2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);
    TF2 *fitFuncW1W2 = new TF2("fitFuncW1W2", "[4]*1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);

    Double_t evaluate() const;
private:
    ClassDef(DoubleGauss_V1, 1)
};

#endif
