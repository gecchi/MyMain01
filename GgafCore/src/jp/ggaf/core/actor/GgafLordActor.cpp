#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafLordActor::GgafLordActor(GgafScene* prm_pScene_Platform) : GgafActor(prm_pScene_Platform->getName()) {
    _pScene_Platform = prm_pScene_Platform;
    _class_name = "GgafLordActor";
    setHitAble(false);
    _actor_class = LORDACTOR;
}

void GgafLordActor::remove() {
    throwGgafCriticalException("[GgafLordActor::remove] Error! GgafLordActorはremove()によって削除は行えません！");
}

GgafGroupActor* GgafLordActor::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor != NULL) {
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
    prm_pMainActor->setLordActor(this);
    prm_pMainActor->setScenePlatform(_pScene_Platform);
    return pSubGroupActor;
}

GgafGroupActor* GgafLordActor::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}



GgafGroupActor* GgafLordActor::getSubGroupActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupActor* pSubGroupActor_ret = NULL;
        do {
            if (pSubActor->_actor_class == GROUPACTOR) {
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

/*
 GgafGroupActor* GgafLordActor::getGroupActor(string prm_kind) {

 }
 */

GgafGod* GgafLordActor::askGod() {
    if (_pGod == NULL) {
#ifdef MY_DEBUG
        if (getPlatformScene() == NULL) {
            throwGgafCriticalException("GgafLordActor::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}

GgafLordActor::~GgafLordActor() {
}
