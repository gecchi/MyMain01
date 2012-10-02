#include "stdafx.h"

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name, GgafStatus* prm_pStat) :
        GgafActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    _pGroupHead = NULL;
    _pDirector = NULL;
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setSceneDirector(NULL); //監督アクターリセット
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

void GgafMainActor::setSceneDirector(GgafDirector* prm_pDirector) {
    _pDirector = prm_pDirector;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setSceneDirector(prm_pDirector);
            } else if (pActor->_obj_class & Obj_GgafGroupHead) {
                ((GgafGroupHead*)(pActor))->setSceneDirector(prm_pDirector);
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
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setGroupHead(prm_pGroupHead);
            } else if (pActor->_obj_class & Obj_GgafGroupHead) {
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
//＜setGroupHead最適化案メモ＞
//以下のような構造の場合、GgafGroupHeadは統合できるはず。
//TODO:うまくして、GgafGroupHead(088C6D48)の排除はできないか
//
//   ｜GgafGroupHead(088C6EA0)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   ｜｜EnemyCirce(088C5E50)[EnemyCirce](-66856,-154236,26350)@13883,1,101,101,0(0)
//   ｜｜｜GgafGroupHead(088C6D48)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   ｜｜｜｜EnemyVesta(08826070)[EnemyVesta1](-197896,-154236,296217)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C2610)[EnemyVesta2](203010,-154759,157390)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C3150)[EnemyVesta3](64184,-154236,-243517)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C3C90)[EnemyVesta4](-336722,-153712,-104690)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C47D0)[EnemyVesta5](-66384,145763,26578)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C5310)[EnemyVesta6](-67327,-454235,26121)@13883,1,101,101,0(0)
//   ｜｜｜└─
//   ｜｜└─
//   ｜└─


GgafGroupHead* GgafMainActor::getMyGroupHead() {
    if (_pGroupHead == NULL) {
#ifdef MY_DEBUG
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getGroupActor 所属していないため、GroupActorがとれません！("<<getName()<<")");
        }
#endif
        if (_pParent->_obj_class & Obj_GgafMainActor) {
            _pGroupHead = ((GgafMainActor*)(_pParent))->getMyGroupHead();
        } else if (_pParent->_obj_class & Obj_GgafGroupHead) {
            return (GgafGroupHead*)_pParent;
        }
    }
    return _pGroupHead;
}


GgafDirector* GgafMainActor::getSceneDirector() {
    if (_pDirector == NULL) {
        if (_pParent == NULL) {
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //この世の監督アクターに仮所属
            _TRACE_("【警告】GgafMainActor::getDirector 所属していないため、Directorがとれません！("<<getName()<<")。そこで勝手にこの世(Universe)のDirectorを返しました");
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pDirector = ((GgafMainActor*)(_pParent))->getSceneDirector();
            } else if (_pParent->_obj_class & Obj_GgafGroupHead) {
                _pDirector = ((GgafGroupHead*)(_pParent))->getSceneDirector();
            } else if (_pParent->_obj_class & Obj_GgafDirector) { //ありえんかな
                return (GgafDirector*)_pParent;
            } else {
                _pDirector = NULL;
            }
           _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //この世の監督アクターに仮所属
            _TRACE_("【警告】GgafMainActor::getDirector このツリーにはDirectorがいません！("<<getName()<<")。そこで勝手にこの世(Universe)のDirectorを返しました");
        }
    }
    return _pDirector;
}



GgafGroupHead* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pDirector) {
        //_TRACE_("【警告】GgafDirector::addSubGroup("<<getName()<<") すでに"<<prm_pMainActor->_pDirector->_pScene_Platform->getName()<<"シーンの監督に所属しています。が、"<<_pScene_Platform->getName()<<"シーンの監督に乗り換えます");
        prm_pMainActor->extract();
    }
    GgafGroupHead* pSubGroupActor = searchSubGroupHead(prm_kind);
    if (pSubGroupActor == NULL) {
        pSubGroupActor = NEW GgafGroupHead(prm_kind);
        addSubLast(pSubGroupActor);
    } else {
       //OK
    }
    pSubGroupActor->addSubLast(prm_pMainActor);
    prm_pMainActor->setGroupHead(pSubGroupActor);
    prm_pMainActor->setSceneDirector(getSceneDirector()); //監督アクターリセット
    prm_pMainActor->setPlatformScene(getPlatformScene()); //所属シーンリセット
    return pSubGroupActor;
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    //_pStatus->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    //したがって actorkind へキャストしても問題ない。
    return addSubGroup((actorkind)(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)), prm_pMainActor);
}


GgafGroupHead* GgafMainActor::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = NULL;
        do {
            if (pSubActor->_obj_class & Obj_GgafGroupHead) {
                pSubGroupHead_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupHead_ret->_kind == prm_kind && pSubGroupHead_ret->_will_end_after_flg == false) {
                    return pSubGroupHead_ret;
                }
            }
            if (pSubActor->_is_last_flg) {
                return NULL;
            } else {
                pSubActor = pSubActor->_pNext;
            }
        } while (true);
    }
}


GgafGod* GgafMainActor::askGod() {
    if (_pGod == NULL) {
        if (_pParent == NULL) {
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
