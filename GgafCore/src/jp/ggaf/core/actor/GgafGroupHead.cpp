#include "stdafx.h"

using namespace GgafCore;

GgafGroupHead::GgafGroupHead(actorkind prm_kind, GgafStatus* prm_pStat) : GgafActor("GROUP", prm_pStat) {
    _obj_class |= Obj_GgafGroupHead;
    _class_name = "GgafGroupHead";

    char aChar_strbit[33];
    UTIL::strbin(prm_kind, aChar_strbit);
    std::stringstream ss;
    ss << "kind=" << aChar_strbit << "";
    std::string name = ss.str();
    strcpy(_name, name.c_str());

    _kind = prm_kind;
    setHitAble(false);
    _pDirector = NULL;
}

GgafDirector* GgafGroupHead::getSceneDirector() {
    if (_pDirector == NULL) {
        if (_pParent == NULL) {
            _TRACE_("【警告】GgafGroupHead::getSceneDirector 所属していないため、Directorがとれません！("<<getName()<<")。そこで勝手にこの世(GgafUniverse)所属のDirectorを返しました");
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector();
        } else {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pDirector = ((GgafMainActor*)(_pParent))->getSceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pDirector = ((GgafGroupHead*)(_pParent))->getSceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafDirector)) {
                return (GgafDirector*)_pParent; //Actorツリー頂点
            }
            _TRACE_("【警告】GgafGroupHead::getSceneDirector このツリーにはDirectorがいません！("<<getName()<<")。そこで勝手にこの世(GgafUniverse)所属のDirectorを返しました");
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector();
        }
    }
    return _pDirector;
}

void GgafGroupHead::setSceneDirector(GgafDirector* prm_pDirector) {
    _pDirector = prm_pDirector;
    if (_pSubFirst) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->instanceOf(Obj_GgafMainActor)) {
                ((GgafMainActor*)(pActor))->setSceneDirector(prm_pDirector);
            } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
                ((GgafGroupHead*)(pActor))->setSceneDirector(prm_pDirector);
            }
            if (pActor->_is_last_flg) {
                break;
            } else {
                pActor = pActor->getNext();
            }
        }
    }
}

void GgafGroupHead::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (getParent()) {
    } else {
        throwGgafCriticalException("GgafGroupHead::updateActiveInTheTree() _is_active_in_the_tree_flg 更新できません。 name="<<getName()<<" this="<<this);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }
}

GgafGod* GgafGroupHead::askGod() {
    if (_pGod == NULL) {
#ifdef MY_DEBUG
        if (getParent() == NULL) {
            throwGgafCriticalException("GgafGroupHead::askGod 神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupHead::~GgafGroupHead() {
}
