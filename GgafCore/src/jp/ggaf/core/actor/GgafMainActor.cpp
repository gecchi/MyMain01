#include "stdafx.h"
#include "jp/ggaf/core/actor/GgafMainActor.h"

#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"
#include "jp/ggaf/core/util/GgafStatus.h"

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
        GgafActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    _pGroupHead = nullptr;
    _pSceneDirector = nullptr;
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setSceneDirector(nullptr); //監督アクターリセット
    pActor->setGroupHead(nullptr); //団長アクターリセット
    return pActor;
}

void GgafMainActor::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (getParent()) {
    } else {
        throwGgafCriticalException("GgafMainActor::updateActiveInTheTree() _is_active_in_the_tree_flg 更新できません。 name="<<getName()<<" this="<<this);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }

}

void GgafMainActor::setSceneDirector(GgafSceneDirector* prm_pSceneDirector) {
    _pSceneDirector = prm_pSceneDirector;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->instanceOf(Obj_GgafMainActor)) {
                ((GgafMainActor*)(pActor))->setSceneDirector(prm_pSceneDirector);
            } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
                ((GgafGroupHead*)(pActor))->setSceneDirector(prm_pSceneDirector);
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}

void GgafMainActor::setGroupHead(GgafGroupHead* prm_pGroupHead) {
    _pGroupHead = prm_pGroupHead;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->instanceOf(Obj_GgafMainActor)) {
                ((GgafMainActor*)(pActor))->setGroupHead(prm_pGroupHead);
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


GgafSceneDirector* GgafMainActor::getSceneDirector() {
    if (_pSceneDirector) {
        return _pSceneDirector;
    } else {
        if (_pParent) {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneDirector = ((GgafMainActor*)(_pParent))->getSceneDirector();
                return _pSceneDirector;
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneDirector = ((GgafGroupHead*)(_pParent))->getSceneDirector();
                return _pSceneDirector;
            } else if (_pParent->instanceOf(Obj_GgafSceneDirector)) { //ありえんかな
                _pSceneDirector = (GgafSceneDirector*)_pParent;
                return _pSceneDirector;
            } else {
                _pSceneDirector = nullptr;
                return _pSceneDirector;
            }
        } else {
            _pSceneDirector = GgafGod::_pGod->_pUniverse->getSceneDirector(); //この世の監督アクターに仮所属
            _TRACE_("【警告】GgafMainActor::getSceneDirector 所属していないため、Directorがとれません！("<<getName()<<")。"<<
                "そこで仮所属でこの世(Universe)のDirectorを返しました。最終的に、親アクターがシーンに所属すれば、その時に更新されてご破算です。確認して下さい。");
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
        //自身の団長種別と引数種別が同じ場合、
        addSubLast(prm_pMainActor); //単純にサブに追加でOK
        prm_pMainActor->setGroupHead(pMyGroupHead);
        prm_pMainActor->setSceneDirector(getSceneDirector()); //監督アクターリセット
        prm_pMainActor->setPlatformScene(getPlatformScene()); //所属シーンリセット
        return pMyGroupHead;
    } else {
        //自身の種別と違う場合
        GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind); //サブに同じ種別団長が居るか探す
        if (pSubGroupActor == nullptr) {
            //サブに同じ種別団長がいない場合、団長を新たに作成
            pSubGroupActor = NEW GgafGroupHead(prm_kind);
            addSubLast(pSubGroupActor);
        } else {
            //サブに同じ種別団長がいた場合、その団長のサブへ
        }
        pSubGroupActor->addSubLast(prm_pMainActor); //団長のサブに追加
        prm_pMainActor->setGroupHead(pSubGroupActor);
        prm_pMainActor->setSceneDirector(getSceneDirector()); //監督アクターリセット
        prm_pMainActor->setPlatformScene(getPlatformScene()); //所属シーンリセット
        return pSubGroupActor;
    }
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //_pStatus->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    //したがって actorkind へキャストしても問題ない。
    return addSubGroup((actorkind)(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)), prm_pMainActor);
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
                if (pSubGroupHead_ret->_kind == prm_kind && pSubGroupHead_ret->_will_end_after_flg == false) {
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
