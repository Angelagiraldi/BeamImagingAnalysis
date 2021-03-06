#include "Riostream.h"
#include "TripleGauss_V2.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"
#include "TMatrix.h"

ClassImp(TripleGauss_V2)

TripleGauss_V2::TripleGauss_V2(
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
):
    RooAbsPdf(name, title),
    xVar("xVar", "xVar", this, _xVar),
    yVar("yVar", "yVar", this, _yVar),
    x0("x0", "x0", this, _x0),
    y0("y0", "y0", this, _y0),
    w1N("w1N", "w1N", this, _w1N),
    w1M("w1M", "w1M", this, _w1M),
    rho_N1("rho_N1", "rho_N1", this, _rho_N1),
    xWidthN1("xWidthN1", "xWidthN1", this, _xWidthN1),
    yWidthN1("yWidthN1", "yWidthN1", this, _yWidthN1),
    rho_M1("rho_M1", "rho_M1", this, _rho_M1),
    xWidthM1("xWidthM1", "xWidthM1", this, _xWidthM1),
    yWidthM1("yWidthM1", "yWidthM1", this, _yWidthM1),
    rho_W1("rho_W1", "rho_W1", this, _rho_W1),
    xWidthW1("xWidthW1", "xWidthW1", this, _xWidthW1),
    yWidthW1("yWidthW1", "yWidthW1", this, _yWidthW1),
    w2N("w2N", "w2N", this, _w2N),
    w2M("w2M", "w2M", this, _w2M),
    yWidthN2("yWidthN2", "yWidthN2", this, _yWidthN2),
    yWidthM2("yWidthM2", "yWidthM2", this, _yWidthM2),
    yWidthW2("yWidthW2", "yWidthW2", this, _yWidthW2),
    vtxResX("vtxResX", "vtxResX", this, _vtxResX),
    vtxResY("vtxResY", "vtxResY", this, _vtxResY)
{}

TripleGauss_V2::TripleGauss_V2(
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
):
    TripleGauss_V2(
        name, title, _xVar, _yVar, _x0, _y0, _w1N, _w1M,
        _rho_N1, _xWidthN1, _yWidthN1, _rho_M1, _xWidthM1, _yWidthM1,
        _rho_W1, _xWidthW1, _yWidthW1,
        _w2N, _w2M, _yWidthN2, _yWidthM2, _yWidthW2, _vtxRes, _vtxRes
    )
{}

TripleGauss_V2::TripleGauss_V2(const TripleGauss_V2& other, const char* name):
    RooAbsPdf(other, name),
    xVar("xVar", this, other.xVar),
    yVar("yVar", this, other.yVar),
    x0("x0", this, other.x0),
    y0("y0", this, other.y0),
    w1N("w1N", this, other.w1N),
    w1M("w1M", this, other.w1M),
    rho_N1("rho_N1", this, other.rho_N1),
    xWidthN1("xWidthN1", this, other.xWidthN1),
    yWidthN1("yWidthN1", this, other.yWidthN1),
    rho_M1("rho_M1", this, other.rho_M1),
    xWidthM1("xWidthM1", this, other.xWidthM1),
    yWidthM1("yWidthM1", this, other.yWidthM1),
    rho_W1("rho_W1", this, other.rho_W1),
    xWidthW1("xWidthW1", this, other.xWidthW1),
    yWidthW1("yWidthW1", this, other.yWidthW1),
    w2N("w2N", this, other.w2N),
    w2M("w2M", this, other.w2M),
    yWidthN2("yWidthN2", this, other.yWidthN2),
    yWidthM2("yWidthM2", this, other.yWidthM2),
    yWidthW2("yWidthW2", this, other.yWidthW2),
    vtxResX("vtxResX", this, other.vtxResX),
    vtxResY("vtxResY", this, other.vtxResY)
{}

Double_t TripleGauss_V2::evaluate() const
{
    TMatrix beamN1(2,2);
    beamN1(0,0) = TMath::Power(xWidthN1, 2.0);
    beamN1(1,1) = TMath::Power(yWidthN1, 2.0);
    beamN1(1,0) = rho_N1*xWidthN1*yWidthN1;
    beamN1(0,1) = rho_N1*xWidthN1*yWidthN1;
    TMatrix beamM1(2,2);
    beamM1(0,0) = TMath::Power(xWidthM1, 2.0);
    beamM1(1,1) = TMath::Power(yWidthM1, 2.0);
    beamM1(1,0) = rho_M1*xWidthM1*yWidthM1;
    beamM1(0,1) = rho_M1*xWidthM1*yWidthM1;
    TMatrix beamW1(2,2);
    beamW1(0,0) = TMath::Power(xWidthW1, 2.0);
    beamW1(1,1) = TMath::Power(yWidthW1, 2.0);
    beamW1(1,0) = rho_W1*xWidthW1*yWidthW1;
    beamW1(0,1) = rho_W1*xWidthW1*yWidthW1;
    TMatrix beamN1_Inv(TMatrix::kInverted, beamN1);
    TMatrix beamM1_Inv(TMatrix::kInverted, beamM1);
    TMatrix beamW1_Inv(TMatrix::kInverted, beamW1);
    TMatrix beamN2MargInv(2,2);
    beamN2MargInv(0,0) = 1.0/TMath::Power(yWidthN2, 2.0);
    beamN2MargInv(1,1) = 0.0;
    beamN2MargInv(0,1) = 0.0;
    beamN2MargInv(1,0) = 0.0;
    TMatrix beamM2MargInv(2,2);
    beamM2MargInv(0,0) = 1.0/TMath::Power(yWidthM2, 2.0);
    beamM2MargInv(1,1) = 0.0;
    beamM2MargInv(0,1) = 0.0;
    beamM2MargInv(1,0) = 0.0;
    TMatrix beamW2MargInv(2,2);
    beamW2MargInv(0,0) = 1.0/TMath::Power(yWidthW2, 2.0);
    beamW2MargInv(1,1) = 0.0;
    beamW2MargInv(0,1) = 0.0;
    beamW2MargInv(1,0) = 0.0;
    TMatrix vtxResSq(2,2);
    vtxResSq(0,0) = TMath::Power(vtxResX, 2.0);
    vtxResSq(1,1) = TMath::Power(vtxResY, 2.0);
    vtxResSq(0,1) = 0.0;
    vtxResSq(1,0) = 0.0;
    TMatrix sigmaN1N2FinalInv(2,2);
    TMatrix sigmaN1M2FinalInv(2,2);
    TMatrix sigmaN1W2FinalInv(2,2);
    TMatrix sigmaM1N2FinalInv(2,2);
    TMatrix sigmaM1M2FinalInv(2,2);
    TMatrix sigmaM1W2FinalInv(2,2);
    TMatrix sigmaW1N2FinalInv(2,2);
    TMatrix sigmaW1M2FinalInv(2,2);
    TMatrix sigmaW1W2FinalInv(2,2);
    sigmaN1N2FinalInv = ((beamN1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
    sigmaN1M2FinalInv = ((beamN1_Inv+beamM2MargInv).Invert()+vtxResSq).Invert();
    sigmaN1W2FinalInv = ((beamN1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();
    sigmaM1N2FinalInv = ((beamM1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
    sigmaM1M2FinalInv = ((beamM1_Inv+beamM2MargInv).Invert()+vtxResSq).Invert();
    sigmaM1W2FinalInv = ((beamM1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();
    sigmaW1N2FinalInv = ((beamW1_Inv+beamN2MargInv).Invert()+vtxResSq).Invert();
    sigmaW1M2FinalInv = ((beamW1_Inv+beamM2MargInv).Invert()+vtxResSq).Invert();
    sigmaW1W2FinalInv = ((beamW1_Inv+beamW2MargInv).Invert()+vtxResSq).Invert();

    fitFuncN1N2->SetParameter(0, sigmaN1N2FinalInv(0,0));
    fitFuncN1N2->SetParameter(1, sigmaN1N2FinalInv(1,1));
    fitFuncN1N2->SetParameter(2, sigmaN1N2FinalInv(1,0));
    fitFuncN1N2->SetParameter(3, (sigmaN1N2FinalInv.Invert()).Determinant());
    fitFuncN1N2->SetParameter(4, w1N*w2N);

    fitFuncN1M2->SetParameter(0, sigmaN1M2FinalInv(0,0));
    fitFuncN1M2->SetParameter(1, sigmaN1M2FinalInv(1,1));
    fitFuncN1M2->SetParameter(2, sigmaN1M2FinalInv(1,0));
    fitFuncN1M2->SetParameter(3, (sigmaN1M2FinalInv.Invert()).Determinant());
    fitFuncN1M2->SetParameter(4, w1N*w2M);

    fitFuncN1W2->SetParameter(0, sigmaN1W2FinalInv(0,0));
    fitFuncN1W2->SetParameter(1, sigmaN1W2FinalInv(1,1));
    fitFuncN1W2->SetParameter(2, sigmaN1W2FinalInv(1,0));
    fitFuncN1W2->SetParameter(3, (sigmaN1W2FinalInv.Invert()).Determinant());
    fitFuncN1W2->SetParameter(4, w1N*(1.0-w2N-w2M));

    fitFuncM1N2->SetParameter(0, sigmaM1N2FinalInv(0,0));
    fitFuncM1N2->SetParameter(1, sigmaM1N2FinalInv(1,1));
    fitFuncM1N2->SetParameter(2, sigmaM1N2FinalInv(1,0));
    fitFuncM1N2->SetParameter(3, (sigmaM1N2FinalInv.Invert()).Determinant());
    fitFuncM1N2->SetParameter(4, w1M*w2N);

    fitFuncM1M2->SetParameter(0, sigmaM1M2FinalInv(0,0));
    fitFuncM1M2->SetParameter(1, sigmaM1M2FinalInv(1,1));
    fitFuncM1M2->SetParameter(2, sigmaM1M2FinalInv(1,0));
    fitFuncM1M2->SetParameter(3, (sigmaM1M2FinalInv.Invert()).Determinant());
    fitFuncM1M2->SetParameter(4, w1M*w2M);

    fitFuncM1W2->SetParameter(0, sigmaM1W2FinalInv(0,0));
    fitFuncM1W2->SetParameter(1, sigmaM1W2FinalInv(1,1));
    fitFuncM1W2->SetParameter(2, sigmaM1W2FinalInv(1,0));
    fitFuncM1W2->SetParameter(3, (sigmaM1W2FinalInv.Invert()).Determinant());
    fitFuncM1W2->SetParameter(4, w1M*(1.0-w2N-w2M));

    fitFuncW1N2->SetParameter(0, sigmaW1N2FinalInv(0,0));
    fitFuncW1N2->SetParameter(1, sigmaW1N2FinalInv(1,1));
    fitFuncW1N2->SetParameter(2, sigmaW1N2FinalInv(1,0));
    fitFuncW1N2->SetParameter(3, (sigmaW1N2FinalInv.Invert()).Determinant());
    fitFuncW1N2->SetParameter(4, (1.0-w1N-w1M)*w2N);

    fitFuncW1M2->SetParameter(0, sigmaW1M2FinalInv(0,0));
    fitFuncW1M2->SetParameter(1, sigmaW1M2FinalInv(1,1));
    fitFuncW1M2->SetParameter(2, sigmaW1M2FinalInv(1,0));
    fitFuncW1M2->SetParameter(3, (sigmaW1M2FinalInv.Invert()).Determinant());
    fitFuncW1M2->SetParameter(4, (1.0-w1N-w1M)*w2M);

    fitFuncW1W2->SetParameter(0, sigmaW1W2FinalInv(0,0));
    fitFuncW1W2->SetParameter(1, sigmaW1W2FinalInv(1,1));
    fitFuncW1W2->SetParameter(2, sigmaW1W2FinalInv(1,0));
    fitFuncW1W2->SetParameter(3, (sigmaW1W2FinalInv.Invert()).Determinant());
    fitFuncW1W2->SetParameter(4, (1.0-w1N-w1M)*(1.0-w2N-w2M));

    double combVal = fitFuncN1N2->Eval(xVar-x0, yVar-y0)
                   + fitFuncN1M2->Eval(xVar-x0, yVar-y0)
                   + fitFuncN1W2->Eval(xVar-x0, yVar-y0)
                   + fitFuncM1N2->Eval(xVar-x0, yVar-y0)
                   + fitFuncM1M2->Eval(xVar-x0, yVar-y0)
                   + fitFuncM1W2->Eval(xVar-x0, yVar-y0)
                   + fitFuncW1N2->Eval(xVar-x0, yVar-y0)
                   + fitFuncW1M2->Eval(xVar-x0, yVar-y0)
                   + fitFuncW1W2->Eval(xVar-x0, yVar-y0);
    return combVal;
}
