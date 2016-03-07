#include "jp/ggaf/core/scene/GgafMainScene.h"

using namespace GgafCore;

GgafMainScene::GgafMainScene(const char* prm_name) : GgafScene(prm_name) {
    _obj_class |= Obj_GgafMainScene;
    _class_name = "GgafMainScene";
}

void GgafMainScene::updateActiveInTheTree() {
    if (_pParent) {
        if (_pParent->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        if (instanceOf(Obj_GgafSpacetime)) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            //���g�� GgafSpacetime�ȊO�ł��� _pParent=nullptr �ŁA
            //updateActiveInTheTree() ���R�[������邱�Ƃ͂��肦�Ȃ��͂��B
            throwGgafCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
        }
    }
}

GgafMainScene::~GgafMainScene() {
}
