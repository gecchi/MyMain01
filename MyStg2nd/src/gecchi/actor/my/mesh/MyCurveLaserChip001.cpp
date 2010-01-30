#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) : CurveLaserChip(prm_name, "12/laser_chip") {
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _pOrg = NULL;
    _is_lockon = false;
}

void MyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);

    registHitAreaCube(60000);

    setHitAble(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.99f;
    _max_radius = 20.0f;
}

void MyCurveLaserChip001::onActive() {
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    CurveLaserChip::onActive();
    _pMover->setMvVelo(80000);
    //_pMover->setMvVeloAcce(300);
    _veloCurve = 1000;
    _pMover->setVxMvVelo(0);
    _pMover->setVyMvVelo(0);
    _pMover->setVzMvVelo(0);


    if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
        _is_lockon = true;
//        _pMover->execTagettingMvAngSequence(_pOrg->_pLockOnTarget,
//                                                   1000, 0,
//                                                   TURN_CLOSE_TO);
    } else {
        _is_lockon = false;
        _pOrg->_pLockOnTarget = NULL;
//        _pMover->stopTagettingMvAngSequence();
//        _pMover->setRzMvAngVelo(0);
//        _pMover->setRyMvAngVelo(0);
//        _pMover->setRzMvAngVeloAcce(0);
//        _pMover->setRyMvAngVeloAcce(0);
    }
}

void MyCurveLaserChip001:: processBehavior() {
    if (_is_lockon && 1 < _dwActiveFrame && _dwActiveFrame < 60) {
        if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
            if (_pOrg->_pLockOnTarget->_X - _X > 0) {
				_pMover->addVxMvVelo(_veloCurve);
            } if (_pOrg->_pLockOnTarget->_X - _X < 0) {
                _pMover->addVxMvVelo(-_veloCurve);
            }
            if (_pOrg->_pLockOnTarget->_Y - _Y > 0) {
                _pMover->addVyMvVelo(_veloCurve);
            } if (_pOrg->_pLockOnTarget->_Y - _Y < 0) {
                _pMover->addVyMvVelo(-_veloCurve);
            }
            if (_pOrg->_pLockOnTarget->_Z - _Z > 0) {
                _pMover->addVzMvVelo(_veloCurve);
            } if (_pOrg->_pLockOnTarget->_Z - _Z < 0) {
                _pMover->addVzMvVelo(-_veloCurve);
            }

        } else {
            _pOrg->_pLockOnTarget = NULL;
        }
    }
    CurveLaserChip::processBehavior();

}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (_pOrg->_pLockOnTarget) {
		if (pOther == _pOrg->_pLockOnTarget) {
			_is_lockon = false;
		}
    } else {
		_pOrg->_pLockOnTarget = pOther;
    }
    //ここにMyのヒットエフェクト
    if (MyStgUtil::calcMyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //ここにMyの消滅エフェクト
        inactivate();
    } else {

    }

}


MyCurveLaserChip001::~MyCurveLaserChip001() {
}

