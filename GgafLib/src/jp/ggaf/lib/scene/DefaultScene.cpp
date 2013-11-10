#include "stdafx.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultScene::DefaultScene(const char* prm_name) : GgafDxScene(prm_name) {
    _obj_class |= Obj_DefaultScene;
    _class_name = "DefaultScene";
    _paFrame_NextEvent = nullptr;
    _cnt_event = 0;
    _event_num = 0;
    DefaultScene::_pProg = nullptr;
    _scroll_speed = 0;
    _pFuncScrolling = nullptr;
}

void DefaultScene::useProgress(int prm_num) {
    if (GgafScene::_pProg == nullptr) {
        GgafScene::_pProg = NEW SceneProgress(this, prm_num);
        DefaultScene::_pProg = (SceneProgress*)(GgafScene::_pProg);
    } else {
        _TRACE_("���x����["<<getName()<<"] �͊��� useProgress ���Ă��܂��Bprm_num="<<prm_num);
    }
}

void DefaultScene::processSettlementBehavior() {
    GgafDxScene::processSettlementBehavior();
    if (_pFuncScrolling && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        executeFuncLowerTree(_pFuncScrolling, &_scroll_speed, nullptr);
        //������ executeFuncLowerTree �̑�Q��R�����́A
        //���̃��\�b�h�̃G�f�B�^��̒�����ɋL�q���Ă��� DefaultScene::scroll_x �̎������ p1 ,p2 �ƑΉ�����
        //  this           �� GgafObject* pThat
        //  &_scroll_speed �� void* p1
        //  nullptr        �� void* p2

    }
}

DefaultScene* DefaultScene::getNearestScrollingScene() {
    if (_pFuncScrolling) {
        return this;
    } else {
        GgafScene* pScene = this;
        while (true) {
            pScene = pScene->getParent();
            if (pScene) {
                if (pScene->instanceOf(Obj_DefaultScene)) {
                    DefaultScene* pDefaultScene = (DefaultScene*)pScene;
                    if (pDefaultScene->_pFuncScrolling) {
                         return pDefaultScene;
                    }
                }
            } else {
                return nullptr;
            }
        }
    }
}

WalledScene* DefaultScene::getNearestWalledScene() {
    if (instanceOf(Obj_WalledScene)) {
        return (WalledScene*)this;
    } else {
        GgafScene* pScene = this;
        while (true) {
            pScene = pScene->getParent();
            if (pScene) {
                if (pScene->instanceOf(Obj_WalledScene)) {
                    return (WalledScene*)pScene;
                }
            } else {
                return nullptr;
            }
        }
    }
}

DefaultScene::~DefaultScene() {
    //�V�[���ɃC�x���g��������������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
}
