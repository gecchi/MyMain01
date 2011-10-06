#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafDirector::GgafDirector(GgafScene* prm_pScene_Platform) : GgafActor(prm_pScene_Platform->getName(), NULL) {
    _obj_class |= Obj_GgafDirector;
    _class_name = "GgafDirector";

    _pScene_Platform = prm_pScene_Platform;
    setHitAble(false);
}

void GgafDirector::remove() {
    throwGgafCriticalException("[GgafDirector::remove] Error! GgafDirectorはremove()によって削除は行えません！");
}

GgafGroupHead* GgafDirector::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
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
    prm_pMainActor->setSceneDirector(this);
    prm_pMainActor->setPlatformScene(_pScene_Platform);
    return pSubGroupActor;
}

GgafGroupHead* GgafDirector::addSubGroup(GgafMainActor* prm_pMainActor) {
    return addSubGroup(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND), prm_pMainActor);
}



GgafGroupHead* GgafDirector::searchSubGroupHead(actorkind prm_kind) {
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
                break;
            } else {
                pSubActor = pSubActor->_pNext;
            }
        } while (true);

        return NULL;
    }
}

/*
 GgafGroupHead* GgafDirector::getMyGroupHead(string prm_kind) {

 }
 */

GgafGod* GgafDirector::askGod() {
    if (_pGod == NULL) {
#ifdef MY_DEBUG
        if (getPlatformScene() == NULL) {
            throwGgafCriticalException("GgafDirector::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pGod = getPlatformScene()->askGod();
    }
    return _pGod;
}

GgafDirector::~GgafDirector() {
}
