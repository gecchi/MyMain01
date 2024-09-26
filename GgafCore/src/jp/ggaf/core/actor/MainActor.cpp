#include "jp/ggaf/core/actor/MainActor.h"

#include "jp/ggaf/core/scene/Spacetime.h"
#include "jp/ggaf/core/util/Status.h"
#include "jp/ggaf/core/actor/SceneChief.h"

using namespace GgafCore;

MainActor::MainActor(const char* prm_name) :
    Actor(prm_name),
    _pSceneChief(nullptr)
{
    _obj_class |= Obj_ggaf_MainActor;
    _class_name = "MainActor";
    setHitAble(false);
}

MainActor* MainActor::extract() {
    MainActor* pActor = (MainActor*)Actor::extract();
    pActor->setSceneChief(nullptr);
    return pActor;
}

void MainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent == nullptr) {
        throwCriticalException("_is_active_in_the_tree_flg 更新できません。this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void MainActor::setSceneChief(SceneChief* prm_pSceneChief) {
    _pSceneChief = prm_pSceneChief;
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_ggaf_MainActor)) {
            ((MainActor*)(pActor))->setSceneChief(prm_pSceneChief);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}


SceneChief* MainActor::getSceneChief() {
    if (_pSceneChief) {
        return _pSceneChief;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
                _pSceneChief = ((MainActor*)(_pParent))->getSceneChief();
                return _pSceneChief;
            } else if (_pParent->instanceOf(Obj_ggaf_SceneChief)) { //ありえんかな
                _pSceneChief = (SceneChief*)_pParent;
                return _pSceneChief;
            } else {
                _pSceneChief = nullptr;
                return _pSceneChief;
            }
        } else {
            _pSceneChief = nullptr;
            return _pSceneChief;
        }
    }
}

Caretaker* MainActor::askCaretaker() {
    if (_pCaretaker == nullptr) {
        if (_pParent == nullptr) {
            throwCriticalException("管理者はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
        _pCaretaker = getParent()->askCaretaker();
    }
    return _pCaretaker;
}

void MainActor::notifyDestroyed() {
    Actor::notifyDestroyed();
    GgafCore::Scene* pPlatformScene = getSceneChief()->getPlatformScene();
    pPlatformScene->onDestroyedActor(this);
}

MainActor::~MainActor() {
}
