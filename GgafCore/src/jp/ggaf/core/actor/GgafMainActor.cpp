#include "stdafx.h"

GgafMainActor::GgafMainActor(string prm_name) : GgafActor(prm_name) {
    setBumpable(false);
	_class_name = "GgafMainActor";
    _pHeadAcor = NULL;
}

void GgafMainActor::setHeadActor(GgafHeadActor* prm_pHeadActor) {
    _pHeadAcor = prm_pHeadActor;
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
	return 	_pHeadAcor;

}

GgafGod* GgafMainActor::askGod() {
	if (_pGod == NULL) {
		if (getParent() == NULL) {
			throw_GgafCriticalException("GgafMainActor::askGod 神は世界からのみ謁見できます。まずは世界に属しなさい！！("<<getName()<<")");
		} else {
			_pGod = getParent()->askGod();
		}
	}
	return _pGod;
}

GgafMainActor::~GgafMainActor() {
}
