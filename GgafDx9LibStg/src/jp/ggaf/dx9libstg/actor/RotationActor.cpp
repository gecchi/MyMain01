#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDummyActor(prm_name) {
	_class_name = "RotationActor";
    setBumpable(false);
}

GgafActor* RotationActor::get() {
	if (_pSubFirst == NULL) {
		throw_GgafCriticalException("RotationActor::getFreeOne() 子がありません");
	}
	GgafActor* pActor = getSubFirst();
	do {
		if(pActor->isPlaying() || pActor->_willPlayNextFrame) {
			if (pActor->isLast()) {
				pActor = NULL;
				break;
			} else {
				pActor = pActor->getNext();
			}
		} else {
			pActor->declareMoveLast();
			break;
		}
	} while(true);
	return pActor;
}

RotationActor::~RotationActor() {
}
