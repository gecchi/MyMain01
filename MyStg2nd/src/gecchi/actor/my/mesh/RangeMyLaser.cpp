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
//		throw_GgafCriticalException("RangeMyLaser::obtain() 子がありません");
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
//				//連続取得
//				pChip->declareMoveLast();
//				pChip->_role = 2;
//			} else {
//				//間隔ありのため空を一つかます
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
//		throw_GgafCriticalException("RangeMyLaser::release() 子がありません");
//	}
//	MyLaserChip* pChip = (MyLaserChip*) getSubFirst();
//	do { //検索
//		if (pChip == prm_pChipSub) {
//			pChip->declareStop();
//			pChip->declareMoveFirst();
//			if (pChip->_role == 1) {
//				//Headの引継ぎ
//
//				_state == 2;
//			}
//			break;
//		} else {
//			if (pChip->isLast()) {
//				pChip = NULL;
//				throw_GgafCriticalException("RangeMyLaser::release() 引数の "<<prm_pChipSub->getClassName()<<"["<<prm_pChipSub->getName()<<"]は居ません");
//			} else {
//				(MyLaserChip*) (pChip -> getNext());
//			}
//		}
//	} while (true);
}

