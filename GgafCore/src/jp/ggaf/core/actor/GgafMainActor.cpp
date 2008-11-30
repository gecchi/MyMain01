#include "stdafx.h"

GgafMainActor::GgafMainActor(string prm_name) : GgafActor(prm_name) {
    setBumpable(false);
	_class_name = "GgafMainActor";
    _pHeadActor = NULL;
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
	return 	_pHeadActor;

}

GgafGod* GgafMainActor::askGod() {
	if (_pGod == NULL) {
		if (getParent() == NULL) {
			throw_GgafCriticalException("GgafMainActor::askGod ê_ÇÕê¢äEÇ©ÇÁÇÃÇ›âyå©Ç≈Ç´Ç‹Ç∑ÅBÇ‹Ç∏ÇÕê¢äEÇ…ëÆÇµÇ»Ç≥Ç¢ÅIÅI("<<getName()<<")");
		} else {
			_pGod = getParent()->askGod();
		}
	}
	return _pGod;
}

GgafMainActor::~GgafMainActor() {
}
