#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ScrolledScene::ScrolledScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "ScrolledScene";
    _scroll_speed = 1000;
    _pFuncScrolling = ScrolledScene::scroll_X; //�f�t�H���g��X�����X�N���[��
}


void ScrolledScene::scroll_X(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
            pActor->_X -= (*((coord*)p1));
        }
    }
}

void ScrolledScene::processBehavior() {
    DefaultScene::processBehavior();
    if (_pFuncScrolling && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        executeFuncLowerTree(_pFuncScrolling, &_scroll_speed, nullptr);
        //������ executeFuncLowerTree �̑�Q��R�����́A
        //������ɋL�q����ScrolledScene::scroll_X �̎������ p1 ,p2 �ƑΉ�����
        //  this           �� GgafObject* pThat
        //  &_scroll_speed �� void* p1
        //  nullptr        �� void* p2

    }
}

ScrolledScene::~ScrolledScene() {
}
