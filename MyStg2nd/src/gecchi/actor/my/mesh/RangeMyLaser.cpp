#include "stdafx.h"

RangeMyLaser::RangeMyLaser(string prm_name) :
	GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this),
			NEW StgChecker(this)) {
	_class_name = "RangeMyLaser";
	setBumpableOnlySelf(false);
	_pChecker = (StgChecker*) _pGeoChecker;
}

MyLaserChip* RangeMyLaser::obtain() {
//	if (_pSubFirst == NULL) {
//		throw_GgafCriticalException("RangeMyLaser::obtain() �q������܂���");
//	}
//	MyLaserChip* pChip = (MyLaserChip*) getSubFirst();
//	if (pChip->isPlaying() || pChip->_willPlayNextFrame) {
//		pChip = NULL;
//	} else {
//		if (pChip->_role == 0) {
//			if (pChip->getPrev()->_role == 0) {
//				pChip->_role = 3;
//
//
//
//
//
//
//
//			pChip->_role = 1;
//			pChip->declareMoveLast();
//
//		} else if (pChip->getPrev()->_role == 0) {
//			if (_dwFrame_LastObtain + 1 == _dwFrame) {
//				//�A���擾
//				pChip->declareMoveLast();
//				pChip->_role = 2;
//			} else {
//				//�Ԋu����̂��ߋ������܂�
//				pChip->_role = 3;
//				pChip->declareMoveLast();
//				pChip = (MyLaserChip*) (pChip -> getNext());
//				if (pChip->isPlaying() || pChip->_willPlayNextFrame) {
//					pChip = NULL;
//				} else {
//					pChip->declareMoveLast();
//					pChip->_role = 2;
//				}
//			}
//		}
//	}
//	return pChip;
	return NULL;
}

void RangeMyLaser::release(MyLaserChip* prm_pChipSub) {
//	if (_pSubFirst == NULL) {
//		throw_GgafCriticalException("RangeMyLaser::release() �q������܂���");
//	}
//	MyLaserChip* pChip = (MyLaserChip*) getSubFirst();
//	do { //����
//		if (pChip == prm_pChipSub) {
//			pChip->declareStop();
//			pChip->declareMoveFirst();
//			if (pChip->_role == 1) {
//				//Head�̈��p��
//
//				_state == 2;
//			}
//			break;
//		} else {
//			if (pChip->isLast()) {
//				pChip = NULL;
//				throw_GgafCriticalException("RangeMyLaser::release() ������ "<<prm_pChipSub->getClassName()<<"["<<prm_pChipSub->getName()<<"]�͋��܂���");
//			} else {
//				(MyLaserChip*) (pChip -> getNext());
//			}
//		}
//	} while (true);
}

