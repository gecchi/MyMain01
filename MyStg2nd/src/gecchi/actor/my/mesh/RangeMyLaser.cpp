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
//		throw_GgafCriticalException("RangeMyLaser::obtain() q‚ª‚ ‚è‚Ü‚¹‚ñ");
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
//				//˜A‘±æ“¾
//				pChip->declareMoveLast();
//				pChip->_role = 2;
//			} else {
//				//ŠÔŠu‚ ‚è‚Ì‚½‚ß‹ó‚ğˆê‚Â‚©‚Ü‚·
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
//		throw_GgafCriticalException("RangeMyLaser::release() q‚ª‚ ‚è‚Ü‚¹‚ñ");
//	}
//	MyLaserChip* pChip = (MyLaserChip*) getSubFirst();
//	do { //ŒŸõ
//		if (pChip == prm_pChipSub) {
//			pChip->declareStop();
//			pChip->declareMoveFirst();
//			if (pChip->_role == 1) {
//				//Head‚ÌˆøŒp‚¬
//
//				_state == 2;
//			}
//			break;
//		} else {
//			if (pChip->isLast()) {
//				pChip = NULL;
//				throw_GgafCriticalException("RangeMyLaser::release() ˆø”‚Ì "<<prm_pChipSub->getClassName()<<"["<<prm_pChipSub->getName()<<"]‚Í‹‚Ü‚¹‚ñ");
//			} else {
//				(MyLaserChip*) (pChip -> getNext());
//			}
//		}
//	} while (true);
}

