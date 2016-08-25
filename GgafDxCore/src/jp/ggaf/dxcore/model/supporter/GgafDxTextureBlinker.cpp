#include <jp/ggaf/dxcore/util/GgafDxUtil.h>
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxTextureBlinker::GgafDxTextureBlinker(GgafDxModel* prm_pModel)  : GgafValueEnveloper<float, 1 > (),
_pModel(prm_pModel) {
    setRange(0.0f, 1000.0f);
}
void GgafDxTextureBlinker::reset() {
    GgafValueEnveloper<float, 1 >::reset();
    setRange(0.0f, 1000.0f);
}

float GgafDxTextureBlinker::getValue(int idx) {
    return _pModel->_power_blink;
}
void GgafDxTextureBlinker::setValue(int idx, float value) {
    _pModel->_power_blink = value;
}

GgafDxTextureBlinker::~GgafDxTextureBlinker() {
}
