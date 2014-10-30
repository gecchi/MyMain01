#include "jp/ggaf/core/actor/GgafGroupHead.h"

#include "jp/ggaf/core/actor/GgafMainActor.h"
#include "jp/ggaf/core/scene/GgafUniverse.h"

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
    _pSceneDirector = nullptr;
}

GgafSceneDirector* GgafGroupHead::getSceneDirector() {
    if (_pSceneDirector == nullptr) {
        if (_pParent == nullptr) {
            _DTRACE_("�y�x���zGgafGroupHead::getSceneDirector �������Ă��Ȃ����߁ADirector���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafUniverse)������Director��Ԃ��܂���");
            _pSceneDirector = GgafGod::_pGod->_pUniverse->getSceneDirector();
        } else {
            if (_pParent->instanceOf(Obj_GgafMainActor)) {
                _pSceneDirector = ((GgafMainActor*)(_pParent))->getSceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafGroupHead)) {
                _pSceneDirector = ((GgafGroupHead*)(_pParent))->getSceneDirector();
            } else if (_pParent->instanceOf(Obj_GgafSceneDirector)) {
                return (GgafSceneDirector*)_pParent; //Actor�c���[���_
            }
            _DTRACE_("�y�x���zGgafGroupHead::getSceneDirector ���̃c���[�ɂ�Director�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafUniverse)������Director��Ԃ��܂���");
            _pSceneDirector = GgafGod::_pGod->_pUniverse->getSceneDirector();
        }
    }
    return _pSceneDirector;
}

void GgafGroupHead::setSceneDirector(GgafSceneDirector* prm_pSceneDirector) {
    _pSceneDirector = prm_pSceneDirector;
    GgafActor* pActor = getSubFirst();
    while (pActor) {
        if (pActor->instanceOf(Obj_GgafMainActor)) {
            ((GgafMainActor*)(pActor))->setSceneDirector(prm_pSceneDirector);
        } else if (pActor->instanceOf(Obj_GgafGroupHead)) {
            ((GgafGroupHead*)(pActor))->setSceneDirector(prm_pSceneDirector);
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
        throwGgafCriticalException("GgafGroupHead::updateActiveInTheTree() _is_active_in_the_tree_flg �X�V�ł��܂���B name="<<getName()<<" this="<<this);
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
            throwGgafCriticalException("GgafGroupHead::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupHead::~GgafGroupHead() {
}
