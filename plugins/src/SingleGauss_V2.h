#ifndef SINGLEGAUSS_V2
#define SINGLEGAUSS_V2

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TF2.h"

class SingleGauss_V2 : public RooAbsPdf {
public:
    SingleGauss_V2() {};
    SingleGauss_V2(
        const char *name, const char *title,
	    RooAbsReal& _xVar,
	    RooAbsReal& _yVar,
	    RooAbsReal& _x0,
	    RooAbsReal& _y0,
	    RooAbsReal& _rho_N1,
	    RooAbsReal& _xWidthN1,
	    RooAbsReal& _yWidthN1,
	    RooAbsReal& _xWidthN2,
    	RooAbsReal& _vtxRes
    );
    SingleGauss_V2(
        const char *name, const char *title,
        RooAbsReal& _xVar,
	    RooAbsReal& _yVar,
	    RooAbsReal& _x0,
	    RooAbsReal& _y0,
	    RooAbsReal& _rho_N1,
	    RooAbsReal& _xWidthN1,
	    RooAbsReal& _yWidthN1,
	    RooAbsReal& _xWidthN2,
	    RooAbsReal& _vtxResX,
	    RooAbsReal& _vtxResY
    );
    SingleGauss_V2(const SingleGauss_V2& other, const char* name=0);
    virtual TObject* clone(const char* newname) const {
        return new SingleGauss_V2(*this, newname);
    };
    inline virtual ~SingleGauss_V2() {};
protected:
    RooRealProxy xVar;
    RooRealProxy yVar;
    RooRealProxy x0;
    RooRealProxy y0;
    RooRealProxy rho_N1;
    RooRealProxy xWidthN1;
    RooRealProxy yWidthN1;
    RooRealProxy xWidthN2;
    RooRealProxy vtxResX;
    RooRealProxy vtxResY;

    TF2 *fitFuncN1N2 = new TF2("fitFuncN1N2", "1./(2*3.14159*TMath::Sqrt([3]))*TMath::Exp(-0.5*(TMath::Power(x[0],2.0)*[0]+TMath::Power(x[1],2.0)*[1]+2*[2]*x[0]*x[1]))", -30, 30, -30, 30);

    Double_t evaluate() const;
private:
    ClassDef(SingleGauss_V2, 1)
};

#endif
