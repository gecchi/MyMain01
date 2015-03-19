#include "jp/ggaf/core/actor/GgafMainActor.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
    GgafActor(prm_name, prm_pStat),
    _pGroupHead(nullptr),
    _pSceneDirector(nullptr)
{
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setPlatformScene(nullptr);
    pActor->setMySceneDirector(nullptr);
    pActor->setMyGroupHead(nullptr);
    return pActor;
}

void GgafMainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent) {
    } else {
        throwGgafCriticalException("GgafMainActor::updateActiveInTheTree() _is_active_in_the_tree_flg 更新できません。this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void GgafMainActor::setMySceneDirector(GgafSceneDirector* prm_pSceneDirector) {
    _pSceneDirector = prm_pSceneDirector;
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMySceneDirector(prm_pSceneDirector);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            ((GgafGroupHead*)(pActor))->setMySceneDirector(prm_pSceneDirector);
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


GgafSceneDirector* GgafMainActor::getMySceneDirector() {
    if (_pSceneDirector) {
        return _pSceneDirector;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneDirector = ((GgafMainActor*)(_pParent))->getMySceneDirector();
                return _pSceneDirector;
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneDirector = ((GgafGroupHead*)(_pParent))->getMySceneDirector();
                return _pSceneDirector;
            } else if (_pParent->instanceOf(Obj_GgafSceneDirector)) { //ありえんかな
                _pSceneDirector = (GgafSceneDirector*)_pParent;
                return _pSceneDirector;
            } else {
                _pSceneDirector = nullptr;
                return _pSceneDirector;
            }
        } else {
            _pSceneDirector = nullptr;
            return _pSceneDirector;
        }
    }
}


GgafGroupHead* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pSceneDirector) {
        //_TRACE_("【警告】GgafSceneDirector::addSubGroup("<<getName()<<") すでに"<<prm_pMainActor->_pSceneDirector->_pScene_platform->getName()<<"シーンの監督に所属しています。が、"<<_pScene_platform->getName()<<"シーンの監督に乗り換えます");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pMyGroupHead = getMyGroupHead();
    if (pMyGroupHead != nullptr && pMyGroupHead->_kind == prm_kind) {
        //自身の所属済み団長種別と引数のアクターの種別が同じ場合
        addSubLast(prm_pMainActor); //単純に自分のサブに追加でOK
        prm_pMainActor->setMyGroupHead(pMyGroupHead);             //団長を反映
        prm_pMainActor->setMySceneDirector(getMySceneDirector()); //監督を反映
        prm_pMainActor->setPlatformScene(getPlatformScene());     //所属シーンを反映
        return pMyGroupHead;
    } else {
        //自身の所属済み団長種別と引数のアクターの種別が異なる場合
        GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //では、自分のサブに引数のアクターと同じ種別の団長が居るか探す
        if (pSubGroupActor) {
            //サブに同じ種別団長がいた場合、その団長のサブへ
            pSubGroupActor->addSubLast(prm_pMainActor);                //サブに居る既存団長の配下に追加
            prm_pMainActor->setMyGroupHead(pSubGroupActor);            //団長を反映
            prm_pMainActor->setMySceneDirector(getMySceneDirector());  //監督を反映
            prm_pMainActor->setPlatformScene(getPlatformScene());      //所属シーンを反映
            return pSubGroupActor;
        } else {
            //サブに同じ種別団長がいない場合、団長を新たに作成し自身のサブへ、
            //引数のアクターは団長のそのサブへ
            GgafGroupHead* pNewSubGroupActor = NEW GgafGroupHead(prm_kind);
            addSubLast(pNewSubGroupActor);                          //自身の配下に新団長を追加し
            pNewSubGroupActor->addSubLast(prm_pMainActor);          //新団長の配下に引数のアクター
            prm_pMainActor->setMyGroupHead(pNewSubGroupActor);            //団長を反映
            pNewSubGroupActor->setMySceneDirector(getMySceneDirector());  //新団長配下に監督を反映
            pNewSubGroupActor->setPlatformScene(getPlatformScene());      //新団長配下に所属シーンセット
            return pNewSubGroupActor;
        }
    }
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //getStatus()->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    return addSubGroup(prm_pMainActor->getStatus()->getUint(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}

GgafGroupHead* GgafMainActor::searchSubGroupHead(actorkind prm_kind) {
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
            throwGgafCriticalException("GgafMainActor::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

actorkind GgafMainActor::getKind() {
    return getMyGroupHead()->_kind;
}



GgafMainActor::~GgafMainActor() {
}
