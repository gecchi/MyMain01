#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"

#include "jp/ggaf/dx/actor/FigureActor.h"


using namespace GgafDx;

AlphaFader::AlphaFader(FigureActor* prm_pActor) : GgafCore::ValueTransitioner<float, 1 > (),
_pActor(prm_pActor) {
    setRange(0.0f, 1.0f);
}
void AlphaFader::reset() {
    GgafCore::ValueTransitioner<float, 1 >::reset();
    setRange(0.0f, 1.0f);
}

float AlphaFader::getValue(int idx) {
    return _pActor->getAlpha();
}
void AlphaFader::setValue(int idx, float value) {
    _pActor->setAlpha(value);
}

AlphaFader::~AlphaFader() {
}
