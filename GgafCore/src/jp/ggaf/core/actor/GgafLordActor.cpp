#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafLordActor::GgafLordActor(GgafScene* prm_pScene_Platform) : GgafActor(prm_pScene_Platform->getName()) {
    _pScene_Platform = prm_pScene_Platform;
    _class_name = "GgafLordActor";
    setBumpable(false);
}

void GgafLordActor::remove() {
    throwGgafCriticalException("[GgafLordActor::remove] Error! GgafLordActorはremove()によって削除は行えません！");
}

void GgafLordActor::accept(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pLordActor != NULL) {
        //_TRACE_("【警告】GgafLordActor::accept("<<getName()<<") すでに"<<prm_pMainActor->_pLordActor->_pScene_Platform->getName()<<"シーンの管理者に所属しています。が、"<<_pScene_Platform->getName()<<"シーンの管理者に乗り換えます");
        prm_pMainActor->breakAwayFromTree();
    }
    GgafHeadActor* pHeadActor = NULL;
    if (hasSubHeadActor(prm_kind)) {
        pHeadActor = getSubHeadActor(prm_kind);
    } else {
        pHeadActor = NEW GgafHeadActor(prm_kind);
        addSubLast(pHeadActor);
    }
    prm_pMainActor->setLordActor(this);
    prm_pMainActor->setHeadActor(pHeadActor);
    prm_pMainActor->setScenePlatform(_pScene_Platform);
    pHeadActor->addSubLast(prm_pMainActor);
}

void GgafLordActor::accept(GgafMainActor* prm_pMainActor) {
    accept(0, prm_pMainActor);
}

bool GgafLordActor::hasSubHeadActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return false;
    } else {
        GgafHeadActor* pHeadActor = (GgafHeadActor*)_pSubFirst;
        do {
            if (pHeadActor->_kind == prm_kind) {
                return true;
            }
            if (pHeadActor->_is_last_flg) {
                return false;
            } else {
                pHeadActor = (GgafHeadActor*)(pHeadActor->_pNext);
            }
        } while (true);
    }

}

GgafHeadActor* GgafLordActor::getSubHeadActor(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        throwGgafCriticalException("[GgafLordActor::getSubHeadActor] Error! _pSubFirstがNULLです。");
    }
    GgafHeadActor* pHeadActor = (GgafHeadActor*)_pSubFirst;
    do {
        if (pHeadActor->_kind == prm_kind) {
            break;
        }
        if (pHeadActor->_is_last_flg) {
            throwGgafCriticalException("[GgafLordActor::getSubHeadActor] Error! 子ノードは存在しません。(actorkind="<<prm_kind<<")");
        } else {
            pHeadActor = (GgafHeadActor*)(pHeadActor->_pNext);
        }
    } while (true);
    return pHeadActor;
}

/*
 GgafHeadActor* GgafLordActor::getHeadActor(string prm_kind) {

 }
 */

GgafGod* GgafLordActor::askGod() {
    if (_pGod == NULL) {
        if (getPlatformScene() == NULL) {
            throwGgafCriticalException("GgafLordActor::askGod 神は世界からのみ謁見できます。まずは世界に属しなさい！！("<<getName()<<")");
        } else {
            _pGod = getPlatformScene()->askGod();
        }
    }
    return _pGod;
}

GgafLordActor::~GgafLordActor() {
}
