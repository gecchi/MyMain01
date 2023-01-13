#include "jp/ggaf/core/actor/SceneMediator.h"

#include "jp/ggaf/core/scene/Scene.h"
#include "jp/ggaf/core/actor/MainActor.h"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

SceneMediator::SceneMediator(Scene* prm_pScene_platform) : Actor("SceneMediator"),
_pScene_platform(nullptr)
{
    _obj_class |= Obj_ggaf_SceneMediator;
    _class_name = "SceneMediator";
    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void SceneMediator::throwEventUpperTree(eventval prm_event_val, void* prm_pSource) {
    Scene* s = getPlatformScene();
    if (s) {
        s->throwEventUpperTree(prm_event_val, this); //自分より上位は居ない。そこで所属シーンへ投げる
    }
}

void SceneMediator::remove() {
    throwCriticalException("Error! SceneMediatorはremove()によって削除は行えません！");
}

GroupHead* SceneMediator::appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        throwCriticalException("Error! SceneMediator::appendGroupChild 所属済みを無理やり移動させようとしています。\n"
                " extract() を行ってから出来ないですか？ prm_pMainActor="<<NODE_INFO_P(prm_pMainActor)<<"/this="<<NODE_INFO);
    }
    GroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //子に同じ種別団長が居るか探す
    if (!pChildGroupActor) {
        //子に同じ種別団長がいない場合、団長を新たに作成
        pChildGroupActor = NEW GroupHead(prm_kind);
        appendChild(pChildGroupActor);
        pChildGroupActor->setSceneMediator(this);
    }
    pChildGroupActor->appendChild(prm_pMainActor);
    prm_pMainActor->setGroupHead(pChildGroupActor);
    prm_pMainActor->setSceneMediator(this);
    return pChildGroupActor;
}

GroupHead* SceneMediator::appendGroupChild(MainActor* prm_pMainActor) {
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GroupHead* SceneMediator::searchChildGroupHead(kind_t prm_kind) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        Actor* pChildActor = _pChildFirst;
        GroupHead* pChildGroupHead_ret = nullptr;
        do {
            if (pChildActor->instanceOf(Obj_ggaf_GroupHead)) {
                pChildGroupHead_ret = (GroupHead*)pChildActor;
                if (pChildGroupHead_ret->_kind == prm_kind && pChildGroupHead_ret->_frame_of_life_when_end == 0) {
                    return pChildGroupHead_ret;
                }
            }
            if (pChildActor->_is_last_flg) {
                break;
            } else {
                pChildActor = pChildActor->_pNext;
            }
        } while (true);

        return nullptr;
    }
}

void SceneMediator::updateActiveInTheTree() {
    Scene* pPlatform = getPlatformScene();
    if (pPlatform) {
        if (pPlatform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwCriticalException("_is_active_in_the_tree_flg 更新できません。 this="<<NODE_INFO);
    }
}

Caretaker* SceneMediator::askCaretaker() {
    if (_pCaretaker == nullptr) {
#ifdef MY_DEBUG
        if (getPlatformScene() == nullptr) {
            throwCriticalException("管理者はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pCaretaker = getPlatformScene()->askCaretaker();
    }
    return _pCaretaker;
}

Actor* SceneMediator::search(hashval prm_name_hash) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        Actor* pPrev = this;
        Actor* pCur = getChildFirst();

        while (pCur != this) {
            if (pCur->_name_hash == prm_name_hash) {
                return pCur; //おしまい
            } else {
                pPrev = pCur;
            }
            if (pPrev == pCur->getParent()) {
                //上から降りて来た場合
                goto susume;
            } else if (pPrev == pCur->getPrev()) {
                //左からに進んで来た場合
                goto susume;
            } else {
                //下から上がってきた場合
                //右へ行く事を試みる
                if (pCur->_is_last_flg) {
                    //と思ったら右端だったので、上に戻る
                    pCur = pCur->getParent();
                } else {
                    //右へ行けるので、行く！
                    pCur = pCur->getNext();
                }
                continue;
            }
susume:
            //降りれるならば降りる
            if (pCur->getChildFirst()) {
                pCur = pCur->getChildFirst();
            } else {
                //降りれない場合は右へ行く事を試みる
                if (pCur->_is_last_flg) {
                    //と思ったら右端だったので、上に戻る
                    pCur = pCur->getParent();
                } else {
                    //右へ行けるので、行く！
                    pCur = pCur->getNext();
                }
            }
        }
        return nullptr;
    }
}
SceneMediator::~SceneMediator() {
}
