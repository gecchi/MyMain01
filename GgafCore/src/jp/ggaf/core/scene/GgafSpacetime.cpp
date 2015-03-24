#include "jp/ggaf/core/scene/GgafSpacetime.h"

using namespace GgafCore;

GgafSpacetime::GgafSpacetime(const char* prm_name) : GgafMainScene(prm_name) {
    _obj_class |= Obj_GgafSpacetime;
    _class_name = "GgafSpacetime";
}

void GgafSpacetime::updateActiveInTheTree() {
    _is_active_in_the_tree_flg = _is_active_flg;
}

GgafSpacetime::~GgafSpacetime() {
}
