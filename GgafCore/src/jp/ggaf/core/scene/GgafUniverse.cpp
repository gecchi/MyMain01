#include "jp/ggaf/core/scene/GgafUniverse.h"

using namespace GgafCore;

GgafUniverse::GgafUniverse(const char* prm_name) : GgafMainScene(prm_name) {
    _obj_class |= Obj_GgafUniverse;
    _class_name = "GgafUniverse";
}

void GgafUniverse::updateActiveInTheTree() {
    _is_active_in_the_tree_flg = _is_active_flg;
}

GgafUniverse::~GgafUniverse() {
}
