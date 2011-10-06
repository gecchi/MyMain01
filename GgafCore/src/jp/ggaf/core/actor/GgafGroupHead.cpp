#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGroupHead::GgafGroupHead(actorkind prm_kind, GgafStatus* prm_pStat) : GgafActor("GROUP", prm_pStat) {
    _obj_class |= Obj_GgafGroupHead;
    _class_name = "GgafGroupHead";

    char aChar_strbit[33];
    GgafUtil::strbin(prm_kind, aChar_strbit);
    stringstream ss;
    ss <<  "kind=" << aChar_strbit << "";
    string name = ss.str();
    strcpy(_name, name.c_str());

    _kind = prm_kind;
    setHitAble(false);
    _pDirector = NULL;
}

GgafDirector* GgafGroupHead::getSceneDirector() {
    if (_pDirector == NULL) {
        if (_pParent == NULL) {
            _TRACE_("�y�x���zGgafGroupHead::getSceneDirector �������Ă��Ȃ����߁ADirector���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafUniverse)������Director��Ԃ��܂���");
            _pDirector = GgafGod::_pGod->_pUniverse->getDirector();
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pDirector = ((GgafMainActor*)(_pParent))->getSceneDirector();
            } else if (_pParent->_obj_class & Obj_GgafGroupHead) {
                _pDirector = ((GgafGroupHead*)(_pParent))->getSceneDirector();
            } else if (_pParent->_obj_class & Obj_GgafDirector) {
                return (GgafDirector*)_pParent; //Actor�c���[���_
            }
            _TRACE_("�y�x���zGgafGroupHead::getSceneDirector ���̃c���[�ɂ�Director�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafUniverse)������Director��Ԃ��܂���");
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
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setSceneDirector(prm_pDirector);
            } else if (pActor->_obj_class & Obj_GgafGroupHead) {
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

GgafGod* GgafGroupHead::askGod() {
    if (_pGod == NULL) {
#ifdef MY_DEBUG
        if (getParent() == NULL) {
            throwGgafCriticalException("GgafGroupHead::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupHead::~GgafGroupHead() {
}
