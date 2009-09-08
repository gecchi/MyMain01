#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name) : GgafActor(prm_name) {
    _class_name = "GgafMainActor";
    _pHeadActor = NULL;
    _pLordActor = NULL;
    setBumpable(false);
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafMainActor* pMainActor_tmp = (GgafMainActor*)getSubFirst();
        while (true) {
            pMainActor_tmp->setLordActor(prm_pLordActor);
            if (pMainActor_tmp->_is_last_flg) {
                break;
            } else {
                pMainActor_tmp = (GgafMainActor*)pMainActor_tmp->getNext();
            }
        }
    }
}

void GgafMainActor::setHeadActor(GgafHeadActor* prm_pHeadActor) {
    _pHeadActor = prm_pHeadActor;
    if (_pSubFirst != NULL) {
        GgafMainActor* pMainActor_tmp = (GgafMainActor*)getSubFirst();
        while (true) {
            pMainActor_tmp->setHeadActor(prm_pHeadActor);
            if (pMainActor_tmp->_is_last_flg) {
                break;
            } else {
                pMainActor_tmp = (GgafMainActor*)pMainActor_tmp->getNext();
            }
        }
    }
}

GgafHeadActor* GgafMainActor::getHeadActor() {
    if (_pHeadActor == NULL) {
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::getHeadActor �������Ă��Ȃ����߁AHeadActor���Ƃ�܂���I("<<getName()<<")");
        } else {
            GgafMainActor* p = dynamic_cast<GgafMainActor*> (_pParent);
            if (p) {
                _pHeadActor = p->getHeadActor();
            } else {
                throwGgafCriticalException("GgafMainActor::getHeadActor ���̃c���[�ɂ�HeadActor�����܂���I("<<getName()<<")");
            }
        }
    }
    return _pHeadActor;
}

GgafLordActor* GgafMainActor::getLordActor() {
    if (_pLordActor == NULL) {
        if (_pParent == NULL) {
            _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
            _TRACE_("�y�x���zGgafMainActor::getLordActor �������Ă��Ȃ����߁ALordActor���Ƃ�܂���I("<<getName()<<")�B�����ŏ���ɂ��̐���LordActor��Ԃ��܂���");
        } else {
            GgafMainActor* p = dynamic_cast<GgafMainActor*> (_pParent);
            if (p) {
                _pLordActor = p->getLordActor();
            } else {
                _pLordActor = GgafGod::_pGod->_pUniverse->getLordActor();
                _TRACE_("�y�x���zGgafMainActor::getLordActor ���̃c���[�ɂ�LordActor�����܂���I("<<getName()<<")�B�����ŏ���ɂ��̐���LordActor��Ԃ��܂���");
            }
        }
    }
    return _pLordActor;
}

GgafGod* GgafMainActor::askGod() {
    if (_pGod == NULL) {
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::askGod �_�͂��̐��ɑ��݂��镨����̂݉y���ł��܂��B�܂��͂��̐��ɑ����Ȃ����I�I("<<getName()<<")");
        } else {
            _pGod = getParent()->askGod();
        }
    }
    return _pGod;
}

GgafMainActor::~GgafMainActor() {
}
