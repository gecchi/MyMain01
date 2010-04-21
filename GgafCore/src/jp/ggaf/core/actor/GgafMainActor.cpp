#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name) : GgafActor(prm_name) {
    _actor_class |= Obj_GgafMainActor;
    _class_name = "GgafMainActor";
    _pGroupActor = NULL;
    _pLordActor = NULL;
    setHitAble(false);
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_actor_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setLordActor(prm_pLordActor);
            } else if (pActor->_actor_class & Obj_GgafGroupActor) {
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
    if (_pSubFirst != NULL) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_actor_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setGroupActor(prm_pGroupActor);
            } else if (pActor->_actor_class & Obj_GgafGroupActor) {
                //ƒXƒ‹[‚·‚é
                //‰ºˆÊƒcƒŠ[‚ÉGgafGroupActor‚ª‚ ‚ê‚ÎA‚»‚ÌƒcƒŠ[‚É‚Í‰e‹¿‚³‚¹‚È‚¢‚±‚Æ‚Æ‚·‚é
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}
//ƒsetGroupActorÅ“K‰»ˆÄƒƒ‚„
//ˆÈ‰º‚Ì‚æ‚¤‚È\‘¢‚Ìê‡AGgafGroupActor‚Í“‡‚Å‚«‚éB
//TODO:‚¤‚Ü‚­‚µ‚ÄAGgafGroupActor(088C6D48)‚Ì”rœ‚Í‚Å‚«‚È‚¢‚©
//
//   bGgafGroupActor(088C6EA0)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   bbEnemyCirce(088C5E50)[EnemyCirce](-66856,-154236,26350)@13883,1,101,101,0(0)
//   bbbGgafGroupActor(088C6D48)[kind=00000000000000000100000000000000]@13883,0,101,101,0(0)
//   bbbbEnemyVesta(08826070)[EnemyVesta1](-197896,-154236,296217)@13883,1,101,101,0(0)
//   bbbbEnemyVesta(088C2610)[EnemyVesta2](203010,-154759,157390)@13883,1,101,101,0(0)
//   bbbbEnemyVesta(088C3150)[EnemyVesta3](64184,-154236,-243517)@13883,1,101,101,0(0)
//   bbbbEnemyVesta(088C3C90)[EnemyVesta4](-336722,-153712,-104690)@13883,1,101,101,0(0)
//   bbbbEnemyVesta(088C47D0)[EnemyVesta5](-66384,145763,26578)@13883,1,101,101,0(0)
//   bbbbEnemyVesta(088C5310)[EnemyVesta6](-67327,-454235,26121)@13883,1,101,101,0(0)
//   bbb„¤„Ÿ
//   bb„¤„Ÿ
//   b„¤„Ÿ


GgafGroupActor* GgafMainActor::getGroupActor() {
    if (_pGroupActor == NULL) {
#ifdef MY_DEBUG
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getGroupActor Š‘®‚µ‚Ä‚¢‚È‚¢‚½‚ßAGroupActor‚ª‚Æ‚ê‚Ü‚¹‚ñI("<<getName()<<")");
        }
#endif
        if (_pParent->_actor_class & Obj_GgafMainActor) {
            _pGroupActor = ((GgafMainActor*)(_pParent))->getGroupActor();
        } else if (_pParent->_actor_class & Obj_GgafGroupActor) {
            return (GgafGroupActor*)_pParent;
        }
    }
    return _pGroupActor;
}


GgafLordActor* GgafMainActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("yŒxzGgafMainActor::getLordActor Š‘®‚µ‚Ä‚¢‚È‚¢‚½‚ßALordActor‚ª‚Æ‚ê‚Ü‚¹‚ñI("<<getName()<<")B‚»‚±‚ÅŸè‚É‚±‚Ì¢(Universe)‚ÌLordActor‚ğ•Ô‚µ‚Ü‚µ‚½");
        } else {
            if (_pParent->_actor_class & Obj_GgafMainActor) {
                _pLordActor = ((GgafMainActor*)(_pParent))->getLordActor();
            } else if (_pParent->_actor_class & Obj_GgafGroupActor) {
                _pLordActor = ((GgafGroupActor*)(_pParent))->getLordActor();
            } else if (_pParent->_actor_class & Obj_GgafLordActor) {
                return (GgafLordActor*)_pParent;
            }
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("yŒxzGgafMainActor::getLordActor ‚±‚ÌƒcƒŠ[‚É‚ÍLordActor‚ª‚¢‚Ü‚¹‚ñI("<<getName()<<")B‚»‚±‚ÅŸè‚É‚±‚Ì¢(Universe)‚ÌLordActor‚ğ•Ô‚µ‚Ü‚µ‚½");
            return _pLordActor;
        }
    }
    return _pLordActor;
}



GgafGroupActor* GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor != NULL) {
        //_TRACE_("yŒxzGgafLordActor::addSubGroup("<<getName()<<") ‚·‚Å‚É"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"ƒV[ƒ“‚ÌŠÇ—Ò‚ÉŠ‘®‚µ‚Ä‚¢‚Ü‚·B‚ªA"<<_pScene_Platform->getName()<<"ƒV[ƒ“‚ÌŠÇ—Ò‚Éæ‚èŠ·‚¦‚Ü‚·");
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
            if (pSubActor->_actor_class & Obj_GgafGroupActor) {
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
#ifdef MY_DEBUG
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::askGod _‚Í‚±‚Ì¢‚É‘¶İ‚·‚é•¨‚©‚ç‚Ì‚İ‰yŒ©‚Å‚«‚Ü‚·B‚Ü‚¸‚Í‚±‚Ì¢‚É‘®‚µ‚È‚³‚¢II("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

actorkind GgafMainActor::getKind() {
    return getGroupActor()->_kind;
}


GgafMainActor::~GgafMainActor() {
}
