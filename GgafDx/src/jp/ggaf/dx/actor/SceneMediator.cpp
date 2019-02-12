#include "jp/ggaf/dx/actor/SceneMediator.h"


using namespace GgafDx;

SceneMediator::SceneMediator(Scene* prm_pScene_platform) : GgafCore::SceneMediator((GgafCore::Scene*)prm_pScene_platform) {
    _obj_class |= Obj_GgafDx_SceneMediator;
    _class_name = "SceneMediator";
}

SceneMediator::~SceneMediator() {
}
