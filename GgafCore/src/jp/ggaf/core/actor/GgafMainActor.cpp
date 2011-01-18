#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name) : GgafActor(prm_name) {
    _obj_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    _pGroupActor = NULL;
    _pLordActor = NULL;
    setHitAble(false);
}

GgafMainActor* GgafMainActor::extract() {
    GgafMainActor* pActor = (GgafMainActor*)GgafActor::extract();
    pActor->setLordActor(NULL); //管理者アクターリセット
    pActor->setScenePlatform(NULL); //所属シーンリセット
    return pActor;
}

bool GgafMainActor::isActive() {
    if (GgafActor::isActive() && getPlatformScene() && getPlatformScene()->isActive()) {
        return true;
    } else {
        return false;
    }
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setLordActor(prm_pLordActor);
            } else if (pActor->_obj_class & Obj_GgafGroupActor) {
                ((GgafGroupActor*)(pActor))->setLordActor(prm_pLordActor);
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}

void GgafMainActor::setGroupActor(GgafGroupActor* prm_pGroupActor) {
    _pGroupActor = prm_pGroupActor;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setGroupActor(prm_pGroupActor);
            } else if (pActor->_obj_class & Obj_GgafGroupActor) {
                //スルーする
                //下位ツリーにGgafGroupActorがあれば、そのツリーには影響させないこととする
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}
//＜setGroupActor最適化案メモ＞
//以下のような構造の場合、GgafGroupActorは統合できるはず。
//TODO:うまくして、GgafGroupActor(088C6D48)の排除はできないか
//
//   ｜GgafGroupActor(088C6EA0)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   ｜｜EnemyCirce(088C5E50)[EnemyCirce](-66856,-154236,26350)@13883,1,101,101,0(0)
//   ｜｜｜GgafGroupActor(088C6D48)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   ｜｜｜｜EnemyVesta(08826070)[EnemyVesta1](-197896,-154236,296217)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C2610)[EnemyVesta2](203010,-154759,157390)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C3150)[EnemyVesta3](64184,-154236,-243517)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C3C90)[EnemyVesta4](-336722,-153712,-104690)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C47D0)[EnemyVesta5](-66384,145763,26578)@13883,1,101,101,0(0)
//   ｜｜｜｜EnemyVesta(088C5310)[EnemyVesta6](-67327,-454235,26121)@13883,1,101,101,0(0)
//   ｜｜｜└─
//   ｜｜└─
//   ｜└─


GgafGroupActor* GgafMainActor::getGroupActor() {
    if (_pGroupActor == NULL) {
#ifdef MY_DEBUG
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getGroupActor 所属していないため、GroupActorがとれません！("<<getName()<<")");
        }
#endif
        if (_pParent->_obj_class & Obj_GgafMainActor) {
            _pGroupActor = ((GgafMainActor*)(_pParent))->getGroupActor();
        } else if (_pParent->_obj_class & Obj_GgafGroupActor) {
            return (GgafGroupActor*)_pParent;
        }
    }
    return _pGroupActor;
}


GgafLordActor* GgafMainActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor(); //この世の管理者アクターに仮所属
            _TRACE_("【警告】GgafMainActor::getLordActor 所属していないため、LordActorがとれません！("<<getName()<<")。そこで勝手にこの世(Universe)のLordActorを返しました");
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pLordActor = ((GgafMainActor*)(_pParent))->getLordActor();
            } else if (_pParent->_obj_class & Obj_GgafGroupActor) {
                _pLordActor = ((GgafGroupActor*)(_pParent))->getLordActor();
            } else if (_pParent->_obj_class & Obj_GgafLordActor) { //ありえんかな
                return (GgafLordActor*)_pParent;
            } else {
                _pLordActor = NULL;
            }
           _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor(); //この世の管理者アクターに仮所属
            _TRACE_("【警告】GgafMainActor::getLordActor このツリーにはLordActorがいません！("<<getName()<<")。そこで勝手にこの世(Universe)のLordActorを返しました");
        }
    }
    return _pLordActor;
}



GgafGroupActor* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor) {
        //_TRACE_("【警告】GgafLordActor::addSubGroup("<<getName()<<") すでに"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"シーンの管理者に所属しています。が、"<<_pScene_Platform->getName()<<"シーンの管理者に乗り換えます");
        prm_pMainActor->extract();
    }
    GgafGroupActor* pSubGroupActor = getSubGroupActor(prm_kind);
    if (pSubGroupActor == NULL) {
        pSubGroupActor = NEW GgafGroupActor(prm_kind);
        addSubLast(pSubGroupActor);
    } else {
       //OK
    }
    pSubGroupActor->addSubLast(prm_pMainActor);
    prm_pMainActor->setGroupActor(pSubGroupActor);
    prm_pMainActor->setLordActor(getLordActor()); //管理者アクターリセット
    prm_pMainActor->setScenePlatform(getPlatformScene()); //所属シーンリセット
    return pSubGroupActor;
}

GgafGroupActor* GgafMainActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}


GgafGroupActor* GgafMainActor::getSubGroupActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupActor* pSubGroupActor_ret = NULL;
        do {
            if (pSubActor->_obj_class & Obj_GgafGroupActor) {
                pSubGroupActor_ret = (GgafGroupActor*)pSubActor;
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
    return getGroupActor()->_kind;
}



GgafMainActor::~GgafMainActor() {
}
