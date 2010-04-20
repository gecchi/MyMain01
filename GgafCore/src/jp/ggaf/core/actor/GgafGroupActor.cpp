#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGroupActor::GgafGroupActor(actorkind prm_kind) : GgafActor("HEAD") {
    char aChar_strbit[33];
    GgafUtil::strbin(prm_kind, aChar_strbit);
    stringstream ss;
    ss <<  "kind=" << aChar_strbit << "";
    string name = ss.str();
    strcpy(_name, name.c_str());
    _class_name = "GgafGroupActor";
    _kind = prm_kind;
    setHitAble(false);
    _pLordActor = NULL;
    _actor_class = GROUPACTOR;
}

GgafLordActor* GgafGroupActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("【警告】GgafGroupActor::getLordActor 所属していないため、LordActorがとれません！("<<getName()<<")。そこで勝手にこの世(GgafUniverse)所属のLordActorを返しました");
        } else {
            if (_pParent->_actor_class == MAINACTOR) {
                _pLordActor = ((GgafMainActor*)(_pParent))->getLordActor();
            } else if (_pParent->_actor_class == GROUPACTOR) {
                _pLordActor = ((GgafGroupActor*)(_pParent))->getLordActor();
            } else if (_pParent->_actor_class == LORDACTOR) {
                return (GgafLordActor*)_pParent;
            }
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("【警告】GgafMainActor::getLordActor このツリーにはLordActorがいません！("<<getName()<<")。そこで勝手にこの世(GgafUniverse)所属のLordActorを返しました");
        }
    }
    return _pLordActor;
}

void GgafGroupActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_actor_class == MAINACTOR) {
                ((GgafMainActor*)(pActor))->setLordActor(prm_pLordActor);
            } else if (pActor->_actor_class == GROUPACTOR) {
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

GgafGod* GgafGroupActor::askGod() {
    if (_pGod == NULL) {
#ifdef MY_DEBUG
        if (getParent() == NULL) {
            throwGgafCriticalException("GgafGroupActor::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupActor::~GgafGroupActor() {
}
