#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"

using namespace GgafLib;

DefaultScene::DefaultScene(const char* prm_name, GgafCore::SceneMediator* prm_pSceneMediator) :
        GgafDx::Scene(prm_name, prm_pSceneMediator ? prm_pSceneMediator : NEW DefaultSceneMediator(this)) {
    _obj_class |= Obj_DefaultScene;
    _class_name = "DefaultScene";
//    _paFrame_NextEvent = nullptr;
//    _cnt_event = 0;
//    _event_num = 0;
    _feature_p1 = 0;
    _pFuncFeature = nullptr;
    GGAF_DELETE_NULLABLE(_pPhase);
    _pPhase = NEW ScenePhase(this);
}

ScenePhase* DefaultScene::createAnotherPhase() {
    return NEW ScenePhase(this);
}

ScenePhase* DefaultScene::getPhase() const {
    return (ScenePhase*)(GgafCore::Scene::getPhase());
}

void DefaultScene::processSettlementBehavior() {
    GgafDx::Scene::processSettlementBehavior();
    if (_pFuncFeature && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        executeFuncLowerTree(_pFuncFeature, &_feature_p1, nullptr, nullptr); //配下アクターにスクロール実行！！
        //ここの executeFuncLowerTree の第2,3,4引数は、
        //このメソッドのエディタ上の直ぐ上に記述してある DefaultScene::scroll_x の受取り引数 p1 ,p2, p3 と対応する
        //  this           → GgafCore::Object* pThat
        //  &_feature_p1 → void* p1
        //  nullptr        → void* p2
        //  nullptr        → void* p3
    }
}

DefaultScene* DefaultScene::getNearestFeatureScene() {
    if (_pFuncFeature) {
        return this;
    } else {
        GgafCore::Scene* pScene = this;
        while (true) {
            pScene = pScene->getParent();
            if (pScene) {
                if (pScene->instanceOf(Obj_DefaultScene)) {
                    DefaultScene* pDefaultScene = (DefaultScene*)pScene;
                    if (pDefaultScene->_pFuncFeature) {
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

DefaultScene::~DefaultScene() {
}
