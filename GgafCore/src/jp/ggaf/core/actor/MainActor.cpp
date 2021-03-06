#include "jp/ggaf/core/actor/MainActor.h"

#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/core/scene/Spacetime.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

MainActor::MainActor(const char* prm_name) :
    Actor(prm_name),
    _pGroupHead(nullptr),
    _pSceneMediator(nullptr)
{
    _obj_class |= Obj_ggaf_MainActor;
    _class_name = "MainActor";
    setHitAble(false);
}

MainActor* MainActor::extract() {
    MainActor* pActor = (MainActor*)Actor::extract();
    pActor->setSceneMediator(nullptr);
    pActor->setGroupHead(nullptr);
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

void MainActor::setSceneMediator(SceneMediator* prm_pSceneMediator) {
    _pSceneMediator = prm_pSceneMediator;
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_ggaf_MainActor)) {
            ((MainActor*)(pActor))->setSceneMediator(prm_pSceneMediator);
        } else if (pActor->instanceOf(Obj_ggaf_GroupHead)) {
            ((GroupHead*)(pActor))->setSceneMediator(prm_pSceneMediator);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}

void MainActor::setGroupHead(GroupHead* prm_pGroupHead) {
    _pGroupHead = prm_pGroupHead;
    Actor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_ggaf_MainActor)) {
            ((MainActor*)(pActor))->setGroupHead(prm_pGroupHead);
        } else if (pActor->instanceOf(Obj_ggaf_GroupHead)) {
            //スルーする
            //下位ツリーにGroupHeadがあれば、そのツリーには影響させないこととする
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}


GroupHead* MainActor::getGroupHead() {
    if (_pGroupHead) {
        return _pGroupHead;
    } else {
        if (_pParent == nullptr) {
            return nullptr;
        } else if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
            _pGroupHead = ((MainActor*)(_pParent))->getGroupHead();
            return _pGroupHead;
        } else if (_pParent->instanceOf(Obj_ggaf_GroupHead)) {
            return (GroupHead*)_pParent;
        } else {
            return nullptr;
        }
    }
}


SceneMediator* MainActor::getSceneMediator() {
    if (_pSceneMediator) {
        return _pSceneMediator;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_ggaf_MainActor)) {
                _pSceneMediator = ((MainActor*)(_pParent))->getSceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_ggaf_GroupHead)) {
                _pSceneMediator = ((GroupHead*)(_pParent))->getSceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_ggaf_SceneMediator)) { //ありえんかな
                _pSceneMediator = (SceneMediator*)_pParent;
                return _pSceneMediator;
            } else {
                _pSceneMediator = nullptr;
                return _pSceneMediator;
            }
        } else {
            _pSceneMediator = nullptr;
            return _pSceneMediator;
        }
    }
}


GroupHead* MainActor::appendGroupChild(kind_t prm_kind, MainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        //_TRACE_("【警告】SceneMediator::appendGroupChild("<<getName()<<") すでに"<<prm_pMainActor->_pSceneMediator->_pScene_platform->getName()<<"シーンの仲介者に所属しています。が、"<<_pScene_platform->getName()<<"シーンの仲介者に乗り換えます");
        prm_pMainActor->extract();
    }
    GroupHead* pMyGroupHead = getGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //自身の所属済み団長種別と引数のアクターの種別が同じ場合
        appendChild(prm_pMainActor); //単純に自分の子に追加でOK
        prm_pMainActor->setGroupHead(pMyGroupHead);             //団長を反映
        prm_pMainActor->setSceneMediator(getSceneMediator()); //仲介者を反映
        return pMyGroupHead;
    } else {
        //自身の所属済み団長種別と引数のアクターの種別が異なる場合
        GroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //では、自分の子に引数のアクターと同じ種別の団長が居るか探す
        if (pChildGroupActor) {
            //子に同じ種別団長がいた場合、その団長の子へ
            pChildGroupActor->appendChild(prm_pMainActor);                //子に居る既存団長の配下に追加
            prm_pMainActor->setGroupHead(pChildGroupActor);            //団長を反映
            prm_pMainActor->setSceneMediator(getSceneMediator());  //仲介者を反映
            return pChildGroupActor;
        } else {
            //子に同じ種別団長がいない場合、団長を新たに作成し自身の子へ、
            //引数のアクターは団長のその子へ
            GroupHead* pNewChildGroupActor = NEW GroupHead(prm_kind);
            appendChild(pNewChildGroupActor);                          //自身の配下に新団長を追加し
            pNewChildGroupActor->appendChild(prm_pMainActor);          //新団長の配下に引数のアクター
            prm_pMainActor->setGroupHead(pNewChildGroupActor);            //団長を反映
            pNewChildGroupActor->setSceneMediator(getSceneMediator());  //新団長配下に仲介者を反映
            return pNewChildGroupActor;
        }
    }
}

GroupHead* MainActor::appendGroupChild(MainActor* prm_pMainActor) {
    //getStatus()->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GroupHead* MainActor::searchChildGroupHead(kind_t prm_kind) {
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
                return nullptr;
            } else {
                pChildActor = pChildActor->_pNext;
            }
        } while (true);
    }
}

God* MainActor::askGod() {
    if (_pGod == nullptr) {
        if (_pParent == nullptr) {
            throwCriticalException("神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

kind_t MainActor::lookUpKind() {
    GroupHead* pMyGroupHead = getGroupHead();
#ifdef MY_DEBUG
    if (pMyGroupHead == nullptr) {
        throwCriticalException("MainActor::lookUpKind() GroupHeadに所属していないので 種別がわかりません。this="<<NODE_INFO);
    }
#endif
    return pMyGroupHead->_kind;
}

MainActor::~MainActor() {
}
