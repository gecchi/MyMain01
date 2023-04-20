#include "jp/ggaf/core/scene/Spacetime.h"

using namespace GgafCore;

Spacetime::Spacetime(const char* prm_name) : MainScene(prm_name) {
    _obj_class |= Obj_ggaf_Spacetime;
    _class_name = "Spacetime";
#ifdef MY_DEBUG
    _is_running_processHitCheck = false;
#endif
}

void Spacetime::updateActiveInTheTree() {
    _is_active_in_the_tree_flg = _is_active_flg;
}

Spacetime::~Spacetime() {
}
