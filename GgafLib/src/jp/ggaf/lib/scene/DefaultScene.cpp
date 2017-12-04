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
    _scroll_speed = 0;
    _pFuncScrolling = nullptr;
}

void DefaultScene::useProgress(int prm_num) {
    if (GgafScene::_pProg == nullptr) {
        GgafScene::_pProg = createProgress(prm_num);
    } else {
        _TRACE_("＜警告＞["<<getName()<<"] は既に useProgress しています。prm_num="<<prm_num);
    }
}

SceneProgress* DefaultScene::createProgress(int prm_num) {
    return NEW SceneProgress(this, prm_num);
}

SceneProgress* DefaultScene::getProgress() const {
    return (SceneProgress*)(GgafScene::getProgress());
}

void DefaultScene::processSettlementBehavior() {
    GgafDxScene::processSettlementBehavior();
    if (_pFuncScrolling && _is_active_flg && !_was_paused_flg && _can_live_flg) {
        executeFuncLowerTree(_pFuncScrolling, &_scroll_speed, nullptr); //配下アクターにスクロール実行！！
        //ここの executeFuncLowerTree の第２第３引数は、
        //このメソッドのエディタ上の直ぐ上に記述してある DefaultScene::scroll_x の受取り引数 p1 ,p2 と対応する
        //  this           → GgafObject* pThat
        //  &_scroll_speed → void* p1
        //  nullptr        → void* p2

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

WallScene* DefaultScene::getNearestWallScene() {
    if (instanceOf(Obj_WallScene)) {
        return (WallScene*)this;
    } else {
        GgafScene* pScene = this;
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
    //シーンにイベントが無いかもしれない
    GGAF_DELETEARR_NULLABLE(_paFrame_NextEvent);
}
