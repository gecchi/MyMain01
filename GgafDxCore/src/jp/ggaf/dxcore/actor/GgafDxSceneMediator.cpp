#include "jp/ggaf/dxcore/actor/GgafDxSceneMediator.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSceneMediator::GgafDxSceneMediator(GgafDxScene* prm_pScene_platform) : GgafSceneMediator((GgafScene*)prm_pScene_platform) {
    _obj_class |= Obj_GgafDxSceneMediator;
    _class_name = "GgafDxSceneMediator";
}

GgafDxSceneMediator::~GgafDxSceneMediator() {
}
