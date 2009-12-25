#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name) : GgafActor(prm_name) {
    _class_name = "GgafMainActor";
    _pHeadActor = NULL;
    _pLordActor = NULL;
    setBumpable(false);
    _actor_class = MAINACTOR;
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_actor_class == MAINACTOR) {
                ((GgafMainActor*)(pActor))->setLordActor(prm_pLordActor);
            } else if (pActor->_actor_class == HEADACTOR) {
                ((GgafHeadActor*)(pActor))->setLordActor(prm_pLordActor);
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}

void GgafMainActor::setHeadActor(GgafHeadActor* prm_pHeadActor) {
    _pHeadActor = prm_pHeadActor;
    if (_pSubFirst != NULL) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_actor_class == MAINACTOR) {
                ((GgafMainActor*)(pActor))->setHeadActor(prm_pHeadActor);
            } else if (pActor->_actor_class == HEADACTOR) {
                //スルーする
                //下位ツリーにGgafHeadActorがあれば、そのツリーには影響させないこととする
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }

}

GgafHeadActor* GgafMainActor::getHeadActor() {
    if (_pHeadActor == NULL) {
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getHeadActor 所属していないため、HeadActorがとれません！("<<getName()<<")");
        } else {
            if (_pParent->_actor_class == MAINACTOR) {
                _pHeadActor = ((GgafMainActor*)(_pParent))->getHeadActor();
            } else if (_pParent->_actor_class == HEADACTOR) {
                return (GgafHeadActor*)_pParent;
            }
        }
    }
    return _pHeadActor;
}

GgafLordActor* GgafMainActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("【警告】GgafMainActor::getLordActor 所属していないため、LordActorがとれません！("<<getName()<<")。そこで勝手にこの世(Universe)のLordActorを返しました");
        } else {
            if (_pParent->_actor_class == MAINACTOR) {
                _pLordActor = ((GgafMainActor*)(_pParent))->getLordActor();
            } else if (_pParent->_actor_class == HEADACTOR) {
                _pLordActor = ((GgafHeadActor*)(_pParent))->getLordActor();
            } else if (_pParent->_actor_class == LORDACTOR) {
                return (GgafLordActor*)_pParent;
            }
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("【警告】GgafMainActor::getLordActor このツリーにはLordActorがいません！("<<getName()<<")。そこで勝手にこの世(Universe)のLordActorを返しました");
            return _pLordActor;
        }
    }
    return _pLordActor;
}



void GgafMainActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor != NULL) {
        //_TRACE_("【警告】GgafLordActor::addSubGroup("<<getName()<<") すでに"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"シーンの管理者に所属しています。が、"<<_pScene_Platform->getName()<<"シーンの管理者に乗り換えます");
        prm_pMainActor->extract();
    }
    GgafHeadActor* pSubHeadActor = getSubHeadActor(prm_kind);
    if (pSubHeadActor == NULL) {
        pSubHeadActor = NEW GgafHeadActor(prm_kind);
        addSubLast(pSubHeadActor);
    } else {
       //OK
    }
    pSubHeadActor->addSubLast(prm_pMainActor);
    prm_pMainActor->setHeadActor(pSubHeadActor);
}


GgafHeadActor* GgafMainActor::getSubHeadActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafHeadActor* pSubHeadActor_ret = NULL;
        do {
            if (pSubActor->_actor_class == HEADACTOR) {
                pSubHeadActor_ret = (GgafHeadActor*)pSubActor;
                if (pSubHeadActor_ret->_kind == prm_kind) {
                    return pSubHeadActor_ret;
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
        } else {
            _pGod = getParent()->askGod();
        }
    }
    return _pGod;
}

GgafMainActor::~GgafMainActor() {
}
