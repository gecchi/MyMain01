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
    _pMover->setMoveVelocity(60000);
    _pMover->setMoveVeloAcceleration(300);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);

    registHitAreaCube(60000);

    setHitAble(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.99f;
    _max_radius = 20.0f;
}

void MyCurveLaserChip001::onActive() {
    CurveLaserChip::onActive();
    _pMover->setMoveVelocity(60000);
    _pMover->setMoveVeloAcceleration(300);
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
        _is_lockon = true;
    } else {
        _is_lockon = false;
        _pOrg->_pLockOnTarget = NULL;
        _pMover->stopTagettingMoveAngleSequence();
        _pMover->setRyMoveAngleVelocity(0);
        _pMover->setRzMoveAngleVelocity(0);
        _pMover->setRyMoveAngleVeloAcceleration(0);
        _pMover->setRzMoveAngleVeloAcceleration(0);
    }
}

void MyCurveLaserChip001:: processBehavior() {
    if (_is_lockon && 0 < _dwActiveFrame && _dwActiveFrame < 120) {
        if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
            if (_pMover->isExecutingTagettingMoveAngle()) {

            } else {
                    //_pMover->setMoveAngle(_pOrg->_pLockOnTarget);

                _pMover->executeTagettingMoveAngleSequence(_pOrg->_pLockOnTarget,
                                                           1000, 0,
                                                           TURN_CLOSE_TO);
            }
        } else {
            _pOrg->_pLockOnTarget = NULL;
            _pMover->stopTagettingMoveAngleSequence();
            _pMover->setRyMoveAngleVelocity(0);
            _pMover->setRzMoveAngleVelocity(0);
            _pMover->setRyMoveAngleVeloAcceleration(0);
            _pMover->setRzMoveAngleVeloAcceleration(0);
        }
    }
    CurveLaserChip::processBehavior();


}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (_pOrg->_pLockOnTarget) {

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

