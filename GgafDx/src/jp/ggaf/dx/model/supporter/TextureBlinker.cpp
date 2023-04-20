#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

TextureBlinker::TextureBlinker(Model* prm_pModel)  : GgafCore::ValueTransitioner<float, 1 > (),
_pModel(prm_pModel) {
    setRange(0.0f, 1000.0f);
}
void TextureBlinker::reset() {
    GgafCore::ValueTransitioner<float, 1 >::reset();
    setRange(0.0f, 1000.0f);
}

float TextureBlinker::getValue(int idx) {
    return _pModel->_power_blink;
}
void TextureBlinker::setValue(int idx, float value) {
    _pModel->_power_blink = value;
}

TextureBlinker::~TextureBlinker() {
}
