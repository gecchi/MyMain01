#include "stdafx.h"

using namespace GgafCore;

GgafDirector::GgafDirector(GgafScene* prm_pScene_platform) : GgafActor(prm_pScene_platform->getName(), NULL) {
    _obj_class |= Obj_GgafDirector;
    _class_name = "GgafDirector";

    _pScene_platform = prm_pScene_platform;
    setHitAble(false);
}

void GgafDirector::remove() {
    throwGgafCriticalException("[GgafDirector::remove] Error! GgafDirectorはremove()によって削除は行えません！");
}

GgafGroupHead* GgafDirector::addSubGroup(actorkind prm_kind, GgafMainActor* prm_pMainActor) {
    if (prm_pMainActor->_pDirector) {
        //_TRACE_("【警告】GgafDirector::addSubGroup("<<getName()<<") すでに"<<prm_pMainActor->_pDirector->_pScene_platform->getName()<<"シーンの監督に所属しています。が、"<<_pScene_platform->getName()<<"シーンの監督に乗り換えます");
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
    prm_pMainActor->setPlatformScene(_pScene_platform);
    return pSubGroupActor;
}

GgafGroupHead* GgafDirector::addSubGroup(GgafMainActor* prm_pMainActor) {
    //_pStatus->get() はint 型だが、例え負の数になっていたとしても、ビットの情報に影響はない
    //したがって actorkind へキャストしても問題ない。
    //TODO:64bitCPUの場合これは危ない。あとで考える・・・。
    return addSubGroup((actorkind)(prm_pMainActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)), prm_pMainActor);
}



GgafGroupHead* GgafDirector::searchSubGroupHead(actorkind prm_kind) {
    if (_pSubFirst == NULL) {
        return NULL;
    } else {
        GgafActor* pSubActor = _pSubFirst;
        GgafGroupHead* pSubGroupHead_ret = NULL;
        do {
            if (pSubActor->instanceOf(Obj_GgafGroupHead)) {
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

void GgafDirector::updateActiveInTheTree() {
    if (getPlatformScene()) {
        if (_pScene_platform->_is_active_in_the_tree_flg) {
            _is_active_in_the_tree_flg = _is_active_flg;
        } else {
            _is_active_in_the_tree_flg = false;
        }
    } else {
        throwGgafCriticalException("GgafDirector::updateActiveInTheTree() _is_active_in_the_tree_flg 更新できません。 name="<<getName()<<" this="<<this);
    }
}

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
