#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafLordActor::GgafLordActor(GgafScene* prm_pScene_Platform) : GgafActor(prm_pScene_Platform->getName()) {
    _pScene_Platform = prm_pScene_Platform;
    _class_name = "GgafLordActor";
    setBumpable(false);
    _actor_class = LORDACTOR;
}

void GgafLordActor::remove() {
    throwGgafCriticalException("[GgafLordActor::remove] Error! GgafLordActorはremove()によって削除は行えません！");
}

void GgafLordActor::accept(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor != NULL) {
        //_TRACE_("【警告】GgafLordActor::accept("<<getName()<<") すでに"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"シーンの管理者に所属しています。が、"<<_pScene_Platform->getName()<<"シーンの管理者に乗り換えます");
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
    prm_pMainActor->setLordActor(this);
    prm_pMainActor->setScenePlatform(_pScene_Platform);
}

void GgafLordActor::accept(GgafMainActor* prm_pMainActor) {
    accept(0, prm_pMainActor);
}



GgafHeadActor* GgafLordActor::getSubHeadActor(actorkind prm_kind) {
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

/*
 GgafHeadActor* GgafLordActor::getHeadActor(string prm_kind) {

 }
 */

GgafGod* GgafLordActor::askGod() {
    if (_pGod == NULL) {
        if (getPlatformScene() == NULL) {
            throwGgafCriticalException("GgafLordActor::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        } else {
            _pGod = getPlatformScene()->askGod();
        }
    }
    return _pGod;
}

GgafLordActor::~GgafLordActor() {
}
