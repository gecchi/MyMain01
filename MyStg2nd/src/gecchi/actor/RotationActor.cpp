#include "stdafx.h"

RotationActor::RotationActor(string prm_name) : GgafDummyActor(prm_name) {
	_class_name = "RotationActor";
    setBumpable(false);
}

GgafActor* RotationActor::getFreeOne() {
	if (_pSubFirst == NULL) {
		throw_GgafCriticalException("RotationActor::getFreeOne() Žq‚ª‚ ‚è‚Ü‚¹‚ñ");
	}
	GgafActor* pActor = getSubFirst();
	do {
		if(pActor->isPlaying()) {
			if (pActor->isLast()) {
				pActor = NULL;
			} else {
				pActor = pActor->getNext();
			}
		} else {
			break;
		}
	} while(true);
	return pActor;
}

RotationActor::~RotationActor() {
}
