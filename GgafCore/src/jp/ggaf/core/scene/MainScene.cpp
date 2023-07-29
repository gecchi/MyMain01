#include "jp/ggaf/core/scene/MainScene.h"

using namespace GgafCore;

MainScene::MainScene(const char* prm_name, SceneChief* prm_pSceneChief) : Scene(prm_name, prm_pSceneChief) {
    _obj_class |= Obj_ggaf_MainScene;
    _class_name = "MainScene";
}

void MainScene::updateActiveInTheTree() {
    if (_pParent) {
        if (_pParent->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        if (instanceOf(Obj_ggaf_Spacetime)) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            //���g�� Spacetime�ȊO�ł��� _pParent=nullptr �ŁA
            //updateActiveInTheTree() ���R�[������邱�Ƃ͂��肦�Ȃ��͂��B
            throwCriticalException("_is_active_in_the_tree_flg �X�V�ł��܂���B this="<<NODE_INFO);
        }
    }
}

MainScene::~MainScene() {
}
