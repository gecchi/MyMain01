#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"

#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpherAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMorpher::GgafDxMorpher(GgafDxMorphMeshActor* prm_pActor) : GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >(),
_pActor(prm_pActor) {
    _pAsstMv = nullptr;
    setRange(0.0f, 1.0f);
}
GgafDxMorpherAssistantA* GgafDxMorpher::asst() {
    return _pAsstMv ? _pAsstMv : _pAsstMv = NEW GgafDxMorpherAssistantA(this);
}

void GgafDxMorpher::reset() {
    GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >::reset();
    setRange(0.0f, 1.0f);
}
float GgafDxMorpher::getValue(int idx) {
    return _pActor->_weight[idx];
}
void GgafDxMorpher::setValue(int idx, float value) {
    _pActor->_weight[idx] = value;
}
void GgafDxMorpher::behave(int s, int n) {
    if (_pAsstMv) {
        _pAsstMv->behave();
    }
    GgafValueEnveloper<float, (MAX_MORPH_TARGET+1) >::behave(1, _pActor->_morph_target_num);
}


GgafDxMorpher::~GgafDxMorpher() {
    GGAF_DELETE_NULLABLE(_pAsstMv);
}
