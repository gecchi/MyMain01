#include "jp/ggaf/dx/actor/SceneChief.h"


using namespace GgafDx;

SceneChief::SceneChief(Scene* prm_pScene_platform) : GgafCore::SceneChief((GgafCore::Scene*)prm_pScene_platform) {
    _obj_class |= Obj_GgafDx_SceneChief;
    _class_name = "SceneChief";
}

SceneChief::~SceneChief() {
}
