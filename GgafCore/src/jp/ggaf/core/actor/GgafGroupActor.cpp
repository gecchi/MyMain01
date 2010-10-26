#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafGroupActor::GgafGroupActor(actorkind prm_kind) : GgafActor("GROUP") {
    _obj_class |= Obj_GgafGroupActor;
    _class_name = "GgafGroupActor";

    char aChar_strbit[33];
    GgafUtil::strbin(prm_kind, aChar_strbit);
    stringstream ss;
    ss <<  "kind=" << aChar_strbit << "";
    string name = ss.str();
    strcpy(_name, name.c_str());

    _kind = prm_kind;
    setHitAble(false);
    _pLordActor = NULL;
}

GgafLordActor* GgafGroupActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("�y�x���zGgafGroupActor::getLordActor �������Ă��Ȃ����߁ALordActor���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafUniverse)������LordActor��Ԃ��܂���");
        } else {
            if (_pParent->_obj_class & Obj_GgafMainActor) {
                _pLordActor = ((GgafMainActor*)(_pParent))->getLordActor();
            } else if (_pParent->_obj_class & Obj_GgafGroupActor) {
                _pLordActor = ((GgafGroupActor*)(_pParent))->getLordActor();
            } else if (_pParent->_obj_class & Obj_GgafLordActor) {
                return (GgafLordActor*)_pParent;
            }
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("�y�x���zGgafMainActor::getLordActor ���̃c���[�ɂ�LordActor�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐�(GgafUniverse)������LordActor��Ԃ��܂���");
        }
    }
    return _pLordActor;
}

void GgafGroupActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_obj_class & Obj_GgafMainActor) {
                ((GgafMainActor*)(pActor))->setLordActor(prm_pLordActor);
            } else if (pActor->_obj_class & Obj_GgafGroupActor) {
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
            throwGgafCriticalException("GgafGroupActor::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        }
#endif
        _pGod = getParent()->askGod();
    }
    return _pGod;
}

GgafGroupActor::~GgafGroupActor() {
}
