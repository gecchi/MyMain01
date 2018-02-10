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
    GgafActor* pActor = getSubFirst();
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
    GgafActor* pActor = getSubFirst();
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


GgafGroupHead* GgafMainActor::addSubGroup(kind_t prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneMediator) {
        //_TRACE_("【警告】GgafSceneMediator::addSubGroup("<<getName()<<") すでに"<<prm_pMainActor->_pSceneMediator->_pScene_platform->getName()<<"シーンの仲介者に所属しています。が、"<<_pScene_platform->getName()<<"シーンの仲介者に乗り換えます");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //自身の所属済み団長種別と引数のアクターの種別が同じ場合
        addSubLast(prm_pMainActor); //単純に自分のサブに追加でOK
        prm_pMainActor->setMyGroupHead(pMyGroupHead);             //団長を反映
        prm_pMainActor->setMySceneMediator(getMySceneMediator()); //仲介者を反映
        return pMyGroupHead;
    } else {
        //自身の所属済み団長種別と引数のアクターの種別が異なる場合
        GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //では、自分のサブに引数のアクターと同じ種別の団長が居るか探す
        if (pSubGroupActor) {
            //サブに同じ種別団長がいた場合、その団長のサブへ
            pSubGroupActor->addSubLast(prm_pMainActor);                //サブに居る既存団長の配下に追加
            prm_pMainActor->setMyGroupHead(pSubGroupActor);            //団長を反映
            prm_pMainActor->setMySceneMediator(getMySceneMediator());  //仲介者を反映
            return pSubGroupActor;
        } else {
            //サブに同じ種別団長がいない場合、団長を新たに作成し自身のサブへ、
            //引数のアクターは団長のそのサブへ
            GgafGroupHead* pNewSubGroupActor = NEW GgafGroupHead(prm_kind);
            addSubLast(pNewSubGroupActor);                          //自身の配下に新団長を追加し
            pNewSubGroupActor->addSubLast(prm_pMainActor);          //新団長の配下に引数のアクター
            prm_pMainActor->setMyGroupHead(pNewSubGroupActor);            //団長を反映
            pNewSubGroupActor->setMySceneMediator(getMySceneMediator());  //新団長配下に仲介者を反映
            return pNewSubGroupActor;
        }
    }
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //getStatus()->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    return addSubGroup(prm_pMainActor->getDefaultKind(), prm_pMainActor);
}

GgafGroupHead* GgafMainActor::searchSubGroupHead(kind_t prm_kind) {
    if (_pSubFirst == nullptr) {
        return nullptr;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = nullptr;
        do {
            if (pSubActor->instanceOf(Obj_GgafGroupHead)) {
                pSubGroupHead_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupHead_ret->_kind == prm_kind && pSubGroupHead_ret->_frame_of_life_when_end == 0) {
                    return pSubGroupHead_ret;
                }
            }
            if (pSubActor->_is_last_flg) {
                return nullptr;
            } else {
                pSubActor = pSubActor->_pNext;
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
