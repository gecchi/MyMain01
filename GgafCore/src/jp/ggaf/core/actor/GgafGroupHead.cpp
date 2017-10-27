#include "jp/ggaf/core/actor/GgafGroupHead.h"

#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"

using namespace GgafCore;

GgafGroupHead::GgafGroupHead(kind prm_kind, GgafStatus* prm_pStat) : GgafActor("GROUP", prm_pStat) {
    _obj_class |= Obj_GgafGroupHead;
    _class_name = "GgafGroupHead";
    _kind = prm_kind;
    setHitAble(false);
    _pSceneDirector = nullptr;

#ifdef MY_DEBUG
    //デバッグ用。名前に種別ビットを表示
    GGAF_DELETEARR(_name);
    const int bitnum = 32;
    char aChar_strbit[bitnum+1];
    UTIL::strbin(prm_kind, aChar_strbit, bitnum);
    std::stringstream ss;
    ss << "kind=" << aChar_strbit << "";
    std::string name = ss.str();
    int len = strlen(name.c_str());
    _name = NEW char[len+1];
    strcpy(_name, name.c_str());
#endif
}

void GgafGroupHead::setKind(kind prm_kind) {
    _kind = prm_kind;

#ifdef MY_DEBUG
    //デバッグ用。名前の種別ビット表示を更新
    GGAF_DELETEARR(_name);
    const int bitnum = 32;
    char aChar_strbit[bitnum+1];
    UTIL::strbin(prm_kind, aChar_strbit, bitnum);
    std::stringstream ss;
    ss << "kind=" << aChar_strbit << "";
    std::string name = ss.str();
    int len = strlen(name.c_str());
    _name = NEW char[len+1];
    strcpy(_name, name.c_str());
#endif
}

GgafSceneDirector* GgafGroupHead::getMySceneDirector() {
    if (_pSceneDirector == nullptr) {
        if (_pParent == nullptr) {
            _TRACE_("【警告】GgafGroupHead::getSceneDirector 所属していないため、Directorがとれません！("<<getName()<<")。そこで勝手にこの世(GgafSpacetime)所属のDirectorを返しました");
            _pSceneDirector = GgafGod::_pGod->_pSpacetime->bringDirector();
        } else {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneDirector = ((GgafMainActor*)(_pParent))->getMySceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneDirector = ((GgafGroupHead*)(_pParent))->getMySceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafSceneDirector)) {
                return (GgafSceneDirector*)_pParent; //Actorツリー頂点
            }
            _TRACE_("【警告】GgafGroupHead::getSceneDirector このツリーにはDirectorがいません！("<<getName()<<")。そこで勝手にこの世(GgafSpacetime)所属のDirectorを返しました");
            _pSceneDirector = GgafGod::_pGod->_pSpacetime->bringDirector();
        }
    }
    return _pSceneDirector;
}

void GgafGroupHead::setMySceneDirector(GgafSceneDirector* prm_pSceneDirector) {
    _pSceneDirector = prm_pSceneDirector;
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setMySceneDirector(prm_pSceneDirector);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            ((GgafGroupHead*)(pActor))->setMySceneDirector(prm_pSceneDirector);
        }
        if (pActor->_is_last_flg) {
            break;
        } else {
            pActor = pActor->getNext();
        }
    }
}

void GgafGroupHead::updateActiveInTheTree() {
#ifdef MY_DEBUG
    if (_pParent) {
    } else {
        throwGgafCriticalException("_is_active_in_the_tree_flg 更新できません。 this="<<NODE_INFO);
    }
#endif
    if (_pParent->_is_active_in_the_tree_flg) {
        _is_active_in_the_tree_flg = _is_active_flg;
    } else {
        _is_active_in_the_tree_flg = false;
    }
}

GgafGod* GgafGroupHead::askGod() {
    if (_pGod == nullptr) {
#ifdef MY_DEBUG
        if (getParent() == nullptr) {
            throwGgafCriticalException("神はこの世に存在する物からのみ謁見できます。まずはこの世に属しなさい！！("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupHead::~GgafGroupHead() {
}
