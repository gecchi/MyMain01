#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafMainActor::GgafMainActor(const char* prm_name) : GgafActor(prm_name) {
    setBumpable(false);
    _class_name = "GgafMainActor";
    _pHeadActor = NULL;
    _pLordActor = NULL;
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
    _pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafMainActor* pMainActor_tmp = (GgafMainActor*)getSubFirst();
        while (true) {
            pMainActor_tmp->setLordActor(prm_pLordActor);
            if (pMainActor_tmp->_isLast) {
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
            if (pMainActor_tmp->_isLast) {
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
            throwGgafCriticalException("GgafMainActor::getLordActor �������Ă��Ȃ����߁ALordActor���Ƃ�܂���I("<<getName()<<")");
        } else {
            GgafMainActor* p = dynamic_cast<GgafMainActor*> (_pParent);
            if (p) {
                _pLordActor = p->getLordActor();
            } else {
                throwGgafCriticalException("GgafMainActor::getLordActor ���̃c���[�ɂ�LordActor�����܂���I("<<getName()<<")");
            }
        }
    }
    return _pLordActor;
}

GgafGod* GgafMainActor::askGod() {
    if (_pGod == NULL) {
        if (_pParent == NULL) {
            throwGgafCriticalException("GgafMainActor::askGod �_�͐��E����̂݉y���ł��܂��B�܂��͐��E�ɑ����Ȃ����I�I("<<getName()<<")");
        } else {
            _pGod = getParent()->askGod();
        }
    }
    return _pGod;
}

GgafMainActor::~GgafMainActor() {
}
