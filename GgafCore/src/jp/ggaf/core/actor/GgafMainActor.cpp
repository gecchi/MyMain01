#include "jp/ggaf/core/actor/GgafMainActor.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
    GgafActor(prm_name, prm_pStat),
    _pGroupHead(nullptr),
    _pSceneMediator(nullptr)
{
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setMySceneMediator(nullptr);
    pActor->setMyGroupHead(nullptr);
    return pActor;
}

void GgafMainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent == nullptr) {
        throwGgafCriticalException("_is_active_in_the_tree_flg 更新できません。this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void GgafMainActor::setMySceneMediator(GgafSceneMediator* prm_pSceneMediator) {
    _pSceneMediator = prm_pSceneMediator;
    GgafActor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMySceneMediator(prm_pSceneMediator);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            ((GgafGroupHead*)(pActor))->setMySceneMediator(prm_pSceneMediator);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}

void GgafMainActor::setMyGroupHead(GgafGroupHead* prm_pGroupHead) {
    _pGroupHead = prm_pGroupHead;
    GgafActor* pActor = getChildFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMyGroupHead(prm_pGroupHead);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            //スルーする
            //下位ツリーにGgafGroupHeadがあれば、そのツリーには影響させないこととする
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}


GgafGroupHead* GgafMainActor::getMyGroupHead() {
    if (_pGroupHead) {
        return _pGroupHead;
    } else {
        if (_pParent == nullptr) {
            return nullptr;
        } else if (_pParent->instanceOf(Obj_GgafMainActor)) {
            _pGroupHead = ((GgafMainActor*)(_pParent))->getMyGroupHead();
            return _pGroupHead;
        } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
            return (GgafGroupHead*)_pParent;
        } else {
            return nullptr;
        }
    }
}


GgafSceneMediator* GgafMainActor::getMySceneMediator() {
    if (_pSceneMediator) {
        return _pSceneMediator;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneMediator = ((GgafMainActor*)(_pParent))->getMySceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneMediator = ((GgafGroupHead*)(_pParent))->getMySceneMediator();
                return _pSceneMediator;
            } else if (_pParent->instanceOf(Obj_GgafSceneMediator)) { //ありえんかな
                _pSceneMediator = (GgafSceneMediator*)_pParent;
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


GgafGroupHead* GgafMainActor::appendGroupChild(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        //_TRACE_("【警告】GgafSceneMediator::appendGroupChild("<<getName()<<") すでに"<<prm_pMainActor->_pSceneMediator->_pScene_platform->getName()<<"シーンの仲介者に所属しています。が、"<<_pScene_platform->getName()<<"シーンの仲介者に乗り換えます");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //自身の所属済み団長種別と引数のアクターの種別が同じ場合
        appendChild(prm_pMainActor); //単純に自分の子に追加でOK
        prm_pMainActor->setMyGroupHead(pMyGroupHead);             //団長を反映
        prm_pMainActor->setMySceneMediator(getMySceneMediator()); //仲介者を反映
        return pMyGroupHead;
    } else {
        //自身の所属済み団長種別と引数のアクターの種別が異なる場合
        GgafGroupHead* pChildGroupActor = searchChildGroupHead(prm_kind); //では、自分の子に引数のアクターと同じ種別の団長が居るか探す
        if (pChildGroupActor) {
            //子に同じ種別団長がいた場合、その団長の子へ
            pChildGroupActor->appendChild(prm_pMainActor);                //子に居る既存団長の配下に追加
            prm_pMainActor->setMyGroupHead(pChildGroupActor);            //団長を反映
            prm_pMainActor->setMySceneMediator(getMySceneMediator());  //仲介者を反映
            return pChildGroupActor;
        } else {
            //子に同じ種別団長がいない場合、団長を新たに作成し自身の子へ、
            //引数のアクターは団長のその子へ
            GgafGroupHead* pNewChildGroupActor = NEW GgafGroupHead(prm_kind);
            appendChild(pNewChildGroupActor);                          //自身の配下に新団長を追加し
            pNewChildGroupActor->appendChild(prm_pMainActor);          //新団長の配下に引数のアクター
            prm_pMainActor->setMyGroupHead(pNewChildGroupActor);            //団長を反映
            pNewChildGroupActor->setMySceneMediator(getMySceneMediator());  //新団長配下に仲介者を反映
            return pNewChildGroupActor;
        }
    }
}

GgafGroupHead* GgafMainActor::appendGroupChild(GgafMainActor* prm_pMainActor) {
    //getStatus()->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    return appendGroupChild(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GgafGroupHead* GgafMainActor::searchChildGroupHead(kind_t prm_kind) {
    if (_pChildFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pChildActor = _pChildFirst;
        GgafGroupHead* pChildGroupHead_ret = nullptr;
        do {
            if (pChildActor->instanceOf(Obj_GgafGroupHead)) {
                pChildGroupHead_ret = (GgafGroupHead*)pChildActor;
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

GgafGod* GgafMainActor::askGod() {
    if (_pGod == nullptr) {
        if (_pParent == nullptr) {
            throwGgafCriticalException("神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

kind_t GgafMainActor::lookUpKind() {
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
#ifdef MY_DEBUG
    if (pMyGroupHead == nullptr) {
        throwGgafCriticalException("GgafMainActor::lookUpKind() GgafGroupHeadに所属していないので 種別がわかりません。this="<<NODE_INFO);
    }
#endif
    return pMyGroupHead->_kind;
}

GgafMainActor::~GgafMainActor() {
}
