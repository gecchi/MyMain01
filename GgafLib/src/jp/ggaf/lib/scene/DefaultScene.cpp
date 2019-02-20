#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"



using namespace GgafLib;

DefaultScene::DefaultScene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator) :
        GgafDx::Scene(prm_name, prm_pSceneMediator ? prm_pSceneMediator : NEW DefaultSceneMediator(this)) {
    _obj_class |= Obj_DefaultScene;
    _class_name = "DefaultScene";
    _paFrame_NextEvent = nullptr;
    _cnt_event = 0;
    _event_num = 0;
    _scroll_speed = 0;
    _pFuncScrolling = nullptr;
    _pProg = DefaultScene::createProgress();
}

//void DefaultScene:://useProgress(int prm_num) {
//    if (GgafCore::Scene::_pProg == nullptr) {
//        GgafCore::Scene::_pProg = createProgress(prm_num);
//    } else {
//        _TRACE_("���x����["<<getName()<<"] �͊��� useProgress ���Ă��܂��Bprm_num="<<prm_num);
//    }
//}

SceneProgress* DefaultScene::createProgress() {
    return NEW SceneProgress(this);
}

SceneProgress* DefaultScene::getProgress() const {
    return (SceneProgress*)(GgafCore::Scene::getProgress());
}

void DefaultScene::processSettlementBehavior() {
    GgafDx::Scene::processSettlementBehavior();
    if (_pFuncScrolling && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        executeFuncLowerTree(_pFuncScrolling, &_scroll_speed, nullptr, nullptr); //�z���A�N�^�[�ɃX�N���[�����s�I�I
        //������ executeFuncLowerTree �̑�2,3,4�����́A
        //���̃��\�b�h�̃G�f�B�^��̒�����ɋL�q���Ă��� DefaultScene::scroll_x �̎������ p1 ,p2, p3 �ƑΉ�����
        //  this           �� GgafCore::Object* pThat
        //  &_scroll_speed �� void* p1
        //  nullptr        �� void* p2
        //  nullptr        �� void* p3
    }
}

DefaultScene* DefaultScene::getNearestScrollingScene() {
    if (_pFuncScrolling) {
        return this;
    } else {
        GgafCore::Scene* pScene = this;
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

WallScene* DefaultScene::getNearestWallScene() {
    if (instanceOf(Obj_WallScene)) {
        return (WallScene*)this;
    } else {
        GgafCore::Scene* pScene = this;
        while (true) {
            pScene = pScene->getParent();
            if (pScene) {
                if (pScene->instanceOf(Obj_WallScene)) {
                    return (WallScene*)pScene;
                }
            } else {
                return nullptr;
            }
        }
    }
}

frame DefaultScene::getLastEventFrame() {
    if (_paFrame_NextEvent) {
        return _paFrame_NextEvent[_event_num-1];
    } else {
        return 0;
    }
}

DefaultScene::~DefaultScene() {
    //�V�[���ɃC�x���g��������������Ȃ�
    GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
}
