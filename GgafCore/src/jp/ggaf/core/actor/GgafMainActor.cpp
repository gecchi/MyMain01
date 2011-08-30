#include "stdafx.h"
using namespace std;

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
    pActor->setMyDirector(NULL); //監督アクターリセット
    pActor->setScenePlatform(NULL); //所属シーンリセット
    return pActor;
}

//bool GgafMainActor::isActive() {
//    if (GgafActor::isActive() && getPlatformScene() && getPlatformScene()->isActive()) {
//        return true;
//    } else {
//        return false;
//    }
//}

void GgafMainActor::setMyDirector(GgafDirector* prm_pDirector) {
    _pDirector = prm_pDirector;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setMyDirector(prm_pDirector);
            } else if (pActor->_obj_class & Obj_GgafGroupHead) {
                ((GgafGroupHead*)(pActor))->setMyDirector(prm_pDirector);
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


GgafDirector* GgafMainActor::getDirector() {
    if (_pDirector == NULL) {
        if (_pParent == NULL) {
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector(); //この世の監督アクターに仮所属
            _TRACE_("【警告】GgafMainActor::getDirector 所属していないため、Directorがとれません！("<<getName()<<")。そこで勝手にこの世(Universe)のDirectorを返しました");
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pDirector = ((GgafMainActor*)(_pParent))->getDirector();
            } else if (_pParent->_obj_class & Obj_GgafGroupHead) {
                _pDirector = ((GgafGroupHead*)(_pParent))->getDirector();
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
    prm_pMainActor->setMyDirector(getDirector()); //監督アクターリセット
    prm_pMainActor->setScenePlatform(getPlatformScene()); //所属シーンリセット
    return pSubGroupActor;
}

GgafGroupHead* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}


GgafGroupHead* GgafMainActor::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupActor_ret = NULL;
        do {
            if (pSubActor->_obj_class & Obj_GgafGroupHead) {
                pSubGroupActor_ret = (GgafGroupHead*)pSubActor;
                if (pSubGroupActor_ret->_kind == prm_kind) {
                    return pSubGroupActor_ret;
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
