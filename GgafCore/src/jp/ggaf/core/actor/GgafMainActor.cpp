#include "stdafx.h"

GgafMainActor::GgafMainActor(string prm_name) : GgafActor(prm_name) {
    setBumpable(false);
	_class_name = "GgafMainActor";
    _pHeadActor = NULL;
	_pLordActor = NULL;
}

void GgafMainActor::setLordActor(GgafLordActor* prm_pLordActor) {
	_pLordActor = prm_pLordActor;
    if (_pSubFirst != NULL) {
        GgafMainActor* pMainActor_tmp = (GgafMainActor*)getSubFirst();
        while(true) {
            pMainActor_tmp -> setLordActor(prm_pLordActor);
            if (pMainActor_tmp -> _isLast) {
                break;
            } else {
			    pMainActor_tmp = (GgafMainActor*)pMainActor_tmp -> getNext();
            }
        }
    }
}

void GgafMainActor::setHeadActor(GgafHeadActor* prm_pHeadActor) {
    _pHeadActor = prm_pHeadActor;
    if (_pSubFirst != NULL) {
        GgafMainActor* pMainActor_tmp = (GgafMainActor*)getSubFirst();
        while(true) {
            pMainActor_tmp -> setHeadActor(prm_pHeadActor);
            if (pMainActor_tmp -> _isLast) {
                break;
            } else {
			    pMainActor_tmp = (GgafMainActor*)pMainActor_tmp -> getNext();
            }
        }
    }
}


GgafHeadActor* GgafMainActor::getHeadActor() {
	if (_pHeadActor == NULL) {
		if (_pParent == NULL) {
			throw_GgafCriticalException("GgafMainActor::getHeadActor �������Ă��Ȃ����߁AHeadActor���Ƃ�܂���I("<<getName()<<")");
		} else {
			_pHeadActor = ((GgafMainActor*)_pParent)->getHeadActor();
		}
	}

	return _pHeadActor;
}

GgafLordActor* GgafMainActor::getLordActor() {
	return _pLordActor;
}

GgafGod* GgafMainActor::askGod() {
	if (_pGod == NULL) {
		if (_pParent == NULL) {
			throw_GgafCriticalException("GgafMainActor::askGod �_�͐��E����̂݉y���ł��܂��B�܂��͐��E�ɑ����Ȃ����I�I("<<getName()<<")");
		} else {
			_pGod = getParent()->askGod();
		}
	}
	return _pGod;
}

GgafMainActor::~GgafMainActor() {
}
