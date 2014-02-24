#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAlphaFader::GgafDxAlphaFader(GgafDxDrawableActor* prm_pActor) : GgafValueTransitioner<float, 1 > (),
_pActor(prm_pActor) {
    forceRange(0.0f, 1.0f);
}
void GgafDxAlphaFader::reset() {
    GgafValueTransitioner<float, 1 >::reset();
    forceRange(0.0f, 1.0f);
}

float GgafDxAlphaFader::getValue(int idx) {
    return _pActor->getAlpha();
}
void GgafDxAlphaFader::setValue(int idx, float value) {
    _pActor->setAlpha(value);
}

GgafDxAlphaFader::~GgafDxAlphaFader() {
}
