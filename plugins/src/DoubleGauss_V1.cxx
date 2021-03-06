#include "Riostream.h"
#include "DoubleGauss_V1.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"
#include "TMatrix.h"

ClassImp(DoubleGauss_V1)

DoubleGauss_V1::DoubleGauss_V1(
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
):
    RooAbsPdf(name, title),
    xVar("xVar", "xVar", this, _xVar),
    yVar("yVar", "yVar", this, _yVar),
    x0("x0", "x0", this, _x0),
    y0("y0", "y0", this, _y0),
    w1("w1", "w1", this, _w1),
    rho_N1("rho_N1", "rho_N1", this, _rho_N1),
    xWidthN1("xWidthN1", "xWidthN1", this, _xWidthN1),
    yWidthN1("yWidthN1", "yWidthN1", this, _yWidthN1),
    rho_W1("rho_W1", "rho_W1", this, _rho_W1),
    xWidthW1("xWidthW1", "xWidthW1", this, _xWidthW1),
    yWidthW1("yWidthW1", "yWidthW1", this, _yWidthW1),
    w2("w2", "w2", this, _w2),
    yWidthN2("yWidthN2", "yWidthN2", this, _yWidthN2),
    yWidthW2("yWidthW2", "yWidthW2", this, _yWidthW2),
    vtxResX("vtxResX", "vtxResX", this, _vtxResX),
    vtxResY("vtxResY", "vtxResY", this, _vtxResY)
{}

DoubleGauss_V1::DoubleGauss_V1(
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
):
    DoubleGauss_V1(
        name, title, _xVar, _yVar, _x0, _y0,
        _w1, _rho_N1, _xWidthN1, _yWidthN1, _rho_W1, _xWidthW1, _yWidthW1,
        _w2, _yWidthN2, _yWidthW2, _vtxRes, _vtxRes
    )
{}

DoubleGauss_V1::DoubleGauss_V1(const DoubleGauss_V1& other, const char* name):
    RooAbsPdf(other, name),
    xVar("xVar", this, other.xVar),
    yVar("yVar", this, other.yVar),
    x0("x0", this, other.x0),
    y0("y0", this, other.y0),
    w1("w1", this, other.w1),
    rho_N1("rho_N1", this, other.rho_N1),
    xWidthN1("xWidthN1", this, other.xWidthN1),
    yWidthN1("yWidthN1", this, other.yWidthN1),
    rho_W1("rho_W1", this, other.rho_W1),
    xWidthW1("xWidthW1", this, other.xWidthW1),
    yWidthW1("yWidthW1", this, other.yWidthW1),
    w2("w2", this, other.w2),
    yWidthN2("yWidthN2", this, other.yWidthN2),
    yWidthW2("yWidthW2", this, other.yWidthW2),
    vtxResX("vtxResX", this, other.vtxResX),
    vtxResY("vtxResY", this, other.vtxResY)
{}

Double_t DoubleGauss_V1::evaluate() const
{
    TMatrix beamN1(2,2);
    beamN1(0,0) = TMath::Power(xWidthN1, 2.0);
    beamN1(1,1) = TMath::Power(yWidthN1, 2.0);
    beamN1(1,0) = rho_N1*xWidthN1*yWidthN1;
    beamN1(0,1) = rho_N1*xWidthN1*yWidthN1;
    TMatrix beamW1(2,2);
    beamW1(0,0) = TMath::Power(xWidthW1, 2.0);
    beamW1(1,1) = TMath::Power(yWidthW1, 2.0);
    beamW1(1,0) = rho_W1*xWidthW1*yWidthW1;
    beamW1(0,1) = rho_W1*xWidthW1*yWidthW1;
    TMatrix beamW1_Inv(TMatrix::kInverted, beamW1);
    TMatrix beamN1_Inv(TMatrix::kInverted, beamN1);
    TMatrix beamN2MargInv(2,2);
    beamN2MargInv(0,0) = 0.0;
    beamN2MargInv(1,1) = 1./TMath::Power(yWidthN2, 2.0);
    beamN2MargInv(0,1) = 0.0;
    beamN2MargInv(1,0) = 0.0;
    TMatrix beamW2MargInv(2,2);
    beamW2MargInv(0,0) = 0.0;
    beamW2MargInv(1,1) = 1./TMath::Power(yWidthW2, 2.0);
    beamW2MargInv(0,1) = 0.0;
    beamW2MargInv(1,0) = 0.0;
    TMatrix vtxResSq(2,2);
    vtxResSq(0,0) = TMath::Power(vtxResX, 2.0);
    vtxResSq(1,1) = TMath::Power(vtxResY, 2.0);
    vtxResSq(0,1) = 0.0;
    vtxResSq(1,0) = 0.0;
    TMatrix sigmaN1N2FinalInv(2,2);
    TMatrix sigmaN1W2FinalInv(2,2);
    TMatrix sigmaW1N2FinalInv(2,2);
    TMatrix sigmaW1W2FinalInv(2,2);
    sigmaN1N2FinalInv = ((beamN1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
    sigmaN1W2FinalInv = ((beamN1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();
    sigmaW1N2FinalInv = ((beamW1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
    sigmaW1W2FinalInv = ((beamW1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();

    fitFuncN1N2->SetParameter(0, sigmaN1N2FinalInv(0,0));
    fitFuncN1N2->SetParameter(1, sigmaN1N2FinalInv(1,1));
    fitFuncN1N2->SetParameter(2, sigmaN1N2FinalInv(1,0));
    fitFuncN1N2->SetParameter(3, (sigmaN1N2FinalInv.Invert()).Determinant());
    fitFuncN1N2->SetParameter(4, w1*w2);

    fitFuncN1W2->SetParameter(0, sigmaN1W2FinalInv(0,0));
    fitFuncN1W2->SetParameter(1, sigmaN1W2FinalInv(1,1));
    fitFuncN1W2->SetParameter(2, sigmaN1W2FinalInv(1,0));
    fitFuncN1W2->SetParameter(3, (sigmaN1W2FinalInv.Invert()).Determinant());
    fitFuncN1W2->SetParameter(4, w1*(1.-w2));

    fitFuncW1N2->SetParameter(0, sigmaW1N2FinalInv(0,0));
    fitFuncW1N2->SetParameter(1, sigmaW1N2FinalInv(1,1));
    fitFuncW1N2->SetParameter(2, sigmaW1N2FinalInv(1,0));
    fitFuncW1N2->SetParameter(3, (sigmaW1N2FinalInv.Invert()).Determinant());
    fitFuncW1N2->SetParameter(4, w2*(1.-w1));

    fitFuncW1W2->SetParameter(0, sigmaW1W2FinalInv(0,0));
    fitFuncW1W2->SetParameter(1, sigmaW1W2FinalInv(1,1));
    fitFuncW1W2->SetParameter(2, sigmaW1W2FinalInv(1,0));
    fitFuncW1W2->SetParameter(3, (sigmaW1W2FinalInv.Invert()).Determinant());
    fitFuncW1W2->SetParameter(4, (1.-w2)*(1.-w1));

    double combVal = fitFuncN1N2->Eval(xVar-x0, yVar-y0)
                   + fitFuncN1W2->Eval(xVar-x0, yVar-y0)
                   + fitFuncW1N2->Eval(xVar-x0, yVar-y0)
                   + fitFuncW1W2->Eval(xVar-x0, yVar-y0);
    return combVal;
}
