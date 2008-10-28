#include "stdafx.h"

StgChecker::StgChecker(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryChecker(prm_pActor) {
	_pHitAreaBoxs = NULL;
	__int64 a;

	_iStaminaPointOriginally = 1;//�����̑ϋv��
	_iScorePointOriginally = 0;  //�����̓��_
	_iStaminaPoint = 1;          //�ϋv��
	_iScorePoint = 0;            //���_
	_iAttackPoint = 0; //�U����
	_iDefensePoint = 0; //�h���
}

void StgChecker::useHitArea(int n) {
	if (_pHitAreaBoxs == NULL) {
		_pHitAreaBoxs = NEW HitAreaBoxs(n);
	} else {
		throw_GgafCriticalException("StgChecker::useHitArea HitAreaBoxs�͊��� new ����Ă��܂��B");
	}
}

void StgChecker::setHitArea(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ) {
	if (_pHitAreaBoxs == NULL) {
		throw_GgafCriticalException("StgChecker::setHitArea �܂� useHitArea �����s���āA�v�f����錾���Ă��������B");
	} else {
		_pHitAreaBoxs->setBox(prm_index, x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);
	}
}

void StgChecker::behave() {
	if (_pActor == NULL || _pHitAreaBoxs == NULL) {
		return;
	}

	static int cx, cy, cz;

	for (int i = 0; i < _pHitAreaBoxs->_iBoxNum; i++) {
		if (!_pHitAreaBoxs->_paBase[i].rotX && !_pHitAreaBoxs->_paBase[i].rotY && !_pHitAreaBoxs->_paBase[i].rotZ) {
			continue;
		}
		cx = _pHitAreaBoxs->_paBase[i].cx;
		cy = _pHitAreaBoxs->_paBase[i].cy;
		cz = _pHitAreaBoxs->_paBase[i].cz;

		if (_pHitAreaBoxs->_paBase[i].rotX) {
			_pHitAreaBoxs->_paHitArea[i].cy = (cy*GgafDx9Util::COS[_pActor->_RX]) - (cz*GgafDx9Util::SIN[_pActor->_RX]);
			_pHitAreaBoxs->_paHitArea[i].cz = (cy*GgafDx9Util::SIN[_pActor->_RX]) + (cz*GgafDx9Util::COS[_pActor->_RX]);
			cy = _pHitAreaBoxs->_paHitArea[i].cy;
			cz = _pHitAreaBoxs->_paHitArea[i].cz;
		}

		if (_pHitAreaBoxs->_paBase[i].rotY) {
			_pHitAreaBoxs->_paHitArea[i].cz = (cz*GgafDx9Util::COS[_pActor->_RY]) - (cx*GgafDx9Util::SIN[_pActor->_RY]);
			_pHitAreaBoxs->_paHitArea[i].cx = (cz*GgafDx9Util::SIN[_pActor->_RY]) + (cx*GgafDx9Util::COS[_pActor->_RY]);
			cz = _pHitAreaBoxs->_paHitArea[i].cz;
			cx = _pHitAreaBoxs->_paHitArea[i].cx;
		}

		if (_pHitAreaBoxs->_paBase[i].rotZ) {
			_pHitAreaBoxs->_paHitArea[i].cx = (cx*GgafDx9Util::COS[_pActor->_RZ]) - (cy*GgafDx9Util::SIN[_pActor->_RZ]);
			_pHitAreaBoxs->_paHitArea[i].cy = (cx*GgafDx9Util::SIN[_pActor->_RZ]) + (cy*GgafDx9Util::COS[_pActor->_RZ]);
			cx = _pHitAreaBoxs->_paHitArea[i].cx;
			cy = _pHitAreaBoxs->_paHitArea[i].cy;
		}

		_pHitAreaBoxs->_paHitArea[i].x1 = cx - _pHitAreaBoxs->_paBase[i].hdx;
		_pHitAreaBoxs->_paHitArea[i].y1 = cy - _pHitAreaBoxs->_paBase[i].hdy;
		_pHitAreaBoxs->_paHitArea[i].z1 = cz - _pHitAreaBoxs->_paBase[i].hdz;
		_pHitAreaBoxs->_paHitArea[i].x2 = cx + _pHitAreaBoxs->_paBase[i].hdx;
		_pHitAreaBoxs->_paHitArea[i].y2 = cy + _pHitAreaBoxs->_paBase[i].hdy;
		_pHitAreaBoxs->_paHitArea[i].z2 = cz + _pHitAreaBoxs->_paBase[i].hdz;

	}


}


bool StgChecker::isBump(GgafDx9GeometryChecker* prm_pOtherChecker) {
	GgafDx9UntransformedActor* pOtherActor     = prm_pOtherChecker->getTargetActor();
	HitAreaBoxs*               pOtherHitAreaBoxs = ((StgChecker*)prm_pOtherChecker)->getHitAreaBoxs();
	if (_pActor == NULL || pOtherActor == NULL || _pHitAreaBoxs == NULL || pOtherHitAreaBoxs == NULL) {
		return false;
	}

	//�����̔��Ƒ���̔�
	if (_pHitAreaBoxs->_paHitArea != NULL && pOtherHitAreaBoxs->_paHitArea != NULL) {

		for (int i = 0; i < _pHitAreaBoxs->_iBoxNum; i++) {
			for (int j = 0; j < pOtherHitAreaBoxs->_iBoxNum; j++) {

				if (_pActor->_Z + _pHitAreaBoxs->_paHitArea[i].z2 >= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[i].z1) {
					if (_pActor->_Z + _pHitAreaBoxs->_paHitArea[i].z1 <= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[i].z2) {
						if (_pActor->_X + _pHitAreaBoxs->_paHitArea[i].x2 >= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[i].x1) {
							if (_pActor->_X + _pHitAreaBoxs->_paHitArea[i].x1 <= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[i].x2) {
								if (_pActor->_Y + _pHitAreaBoxs->_paHitArea[i].y2 >= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[i].y1) {
									if (_pActor->_Y + _pHitAreaBoxs->_paHitArea[i].y1 <= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[i].y2) {
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
