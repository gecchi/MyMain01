#include "stdafx.h"

StgChecker::StgChecker(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryChecker(prm_pActor) {
	_pHitAreaBoxs = NULL;
	_iStaminaPointOriginally = 1;//Œ³—ˆ‚Ì‘Ï‹v—Í
	_iScorePointOriginally = 0;  //Œ³—ˆ‚Ì“¾“_
	_iStaminaPoint = 1;          //‘Ï‹v—Í
	_iScorePoint = 0;            //“¾“_
	_iAttackPoint = 0; //UŒ‚—Í
	_iDefensePoint = 0; //–hŒä—Í
}


void StgChecker::behave() {
}


bool StgChecker::isBump(GgafDx9GeometryChecker* prm_pOtherChecker) {
	GgafDx9UntransformedActor* pOtherActor     = prm_pOtherChecker->_pActor;
	HitAreaBoxs*                 pOtherHitAreaBoxs = ((StgChecker*)prm_pOtherChecker)->_pHitAreaBoxs;
	if (_pHitAreaBoxs == NULL || pOtherHitAreaBoxs == NULL) {
		return false;
	}

	//Ž©•ª‚Ì” ‚Æ‘ŠŽè‚Ì” 
	if (_pHitAreaBoxs->_paBox != NULL && pOtherHitAreaBoxs->_paBox != NULL) {
		for (int i = 0; i < _pHitAreaBoxs->_iBoxNum; i++) {
			for (int j = 0; j < pOtherHitAreaBoxs->_iBoxNum; j++) {

				if (_pActor->_Z+_pHitAreaBoxs->_paBox[i].z2 >= pOtherActor->_Z + pOtherHitAreaBoxs->_paBox[j].z1) {
					if (_pActor->_Z+_pHitAreaBoxs->_paBox[i].z1 <= pOtherActor->_Z + pOtherHitAreaBoxs->_paBox[j].z2) {
						if (_pActor->_X+_pHitAreaBoxs->_paBox[i].x2 >= pOtherActor->_X + pOtherHitAreaBoxs->_paBox[j].x1) {
							if (_pActor->_X+_pHitAreaBoxs->_paBox[i].x1 <= pOtherActor->_X + pOtherHitAreaBoxs->_paBox[j].x2) {
								if (_pActor->_Y+_pHitAreaBoxs->_paBox[i].y2 >= pOtherActor->_Y + pOtherHitAreaBoxs->_paBox[j].y1) {
									if (_pActor->_Y+_pHitAreaBoxs->_paBox[i].y1 <= pOtherActor->_Y + pOtherHitAreaBoxs->_paBox[j].y2) {
										return true;
									}
								}
							}
						}
					}
				}

			}
		}
	}

	return false;
}

StgChecker::~StgChecker() {
	TRACE("StgChecker::~StgChecker() _pActor="<<_pActor->getName()<<" start--->");
	if (_pHitAreaBoxs != NULL) {
		delete _pHitAreaBoxs;
	}
	TRACE("StgChecker::~StgChecker() _pActor="<<_pActor->getName()<<" <---end");
}
