#include "Riostream.h"
#include "SingleGauss_V2.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"
#include "TMatrix.h"

ClassImp(SingleGauss_V2)

SingleGauss_V2::SingleGauss_V2(
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
):
    RooAbsPdf(name,title),
    xVar("xVar", "xVar", this, _xVar),
    yVar("yVar", "yVar", this, _yVar),
    x0("x0", "x0", this, _x0),
    y0("y0", "y0", this, _y0),
    rho_N1("rho_N1", "rho_N1", this, _rho_N1),
    xWidthN1("xWidthN1", "xWidthN1", this, _xWidthN1),
    yWidthN1("yWidthN1", "yWidthN1", this, _yWidthN1),
    xWidthN2("xWidthN2", "xWidthN2", this, _xWidthN2),
    vtxResX("vtxResX", "vtxResX", this, _vtxResX),
    vtxResY("vtxResY", "vtxResY", this, _vtxResY)
{}

SingleGauss_V2::SingleGauss_V2(
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
):
    SingleGauss_V2(
        name, title, _xVar, _yVar, _x0, _y0, _rho_N1,
        _xWidthN1, _yWidthN1, _xWidthN2, _vtxRes, _vtxRes
    )
{}

SingleGauss_V2::SingleGauss_V2(const SingleGauss_V2& other, const char* name):
    RooAbsPdf(other,name),
    xVar("xVar", this, other.xVar),
    yVar("yVar", this, other.yVar),
    x0("x0", this, other.x0),
    y0("y0", this, other.y0),
    rho_N1("rho_N1", this, other.rho_N1),
    xWidthN1("xWidthN1", this, other.xWidthN1),
    yWidthN1("yWidthN1", this, other.yWidthN1),
    xWidthN2("xWidthN2", this, other.xWidthN2),
    vtxResX("vtxResX", this, other.vtxResX),
    vtxResY("vtxResY", this, other.vtxResY)
{}

Double_t SingleGauss_V2::evaluate() const
{
    TMatrix beamN1(2,2);
    beamN1(0,0) = TMath::Power(xWidthN1, 2.0);
    beamN1(1,1) = TMath::Power(yWidthN1, 2.0);
    beamN1(1,0) = rho_N1*xWidthN1*yWidthN1;
    beamN1(0,1) = rho_N1*xWidthN1*yWidthN1;
    TMatrix beamN1_Inv(TMatrix::kInverted, beamN1);
    TMatrix beamN2MargInv(2,2);
    beamN2MargInv(0,0) = 1./TMath::Power(xWidthN2, 2.0);
    beamN2MargInv(1,1) = 0.0;
    beamN2MargInv(0,1) = 0.0;
    beamN2MargInv(1,0) = 0.0;
    TMatrix vtxResSq(2,2);
    vtxResSq(0,0) = TMath::Power(vtxResX, 2.0);
    vtxResSq(1,1) = TMath::Power(vtxResY, 2.0);
    vtxResSq(0,1) = 0.0;
    vtxResSq(1,0) = 0.0;
    TMatrix sigmaN1N2FinalInv(2,2);
    sigmaN1N2FinalInv = ((beamN1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();

    fitFuncN1N2->SetParameter(0, sigmaN1N2FinalInv(0,0));
    fitFuncN1N2->SetParameter(1, sigmaN1N2FinalInv(1,1));
    fitFuncN1N2->SetParameter(2, sigmaN1N2FinalInv(1,0));
    fitFuncN1N2->SetParameter(3, (sigmaN1N2FinalInv.Invert()).Determinant());

    double combVal = fitFuncN1N2->Eval(xVar-x0, yVar-y0);
    return combVal;
 }
