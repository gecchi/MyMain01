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
    _slow_renge = 80000;
    _cnt_rev = 0;
}

void MyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);

    registHitAreaCube(60000);

    setHitAble(true);
    _SX = _SY = _SZ = 80*1000;
    _fAlpha = 0.99f;
    _max_radius = 20.0f;
    int renge = 100000;
    _pMover->setVxMvVeloRenge(-renge, renge);
    _pMover->setVyMvVeloRenge(-renge, renge);
    _pMover->setVzMvVeloRenge(-renge, renge);

    _pMover->setVxMvAcceRenge(-renge/10, renge/10);
    _pMover->setVyMvAcceRenge(-renge/10, renge/10);
    _pMover->setVzMvAcceRenge(-renge/10, renge/10);

}

void MyCurveLaserChip001::onActive() {
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    CurveLaserChip::onActive();
    _pMover->setMvVelo(0);
    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    //_pMover->setMvAcce(300);
    _veloCurve = 1000;

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
//        _pMover->setRzMvAngAcce(0);
//        _pMover->setRyMvAngAcce(0);
    }
}

void MyCurveLaserChip001:: processBehavior() {
    int asobiX,asobiY,asobiZ;
    if (_pChip_front) {
        asobiX = abs(_pChip_front->_pMover->_veloVxMv -_pMover->_veloVxMv) / 2;
        asobiY = abs(_pChip_front->_pMover->_veloVyMv -_pMover->_veloVyMv) / 2;
        asobiZ = abs(_pChip_front->_pMover->_veloVzMv -_pMover->_veloVzMv) / 2;
    }

    if (_is_lockon && 1 < _dwActiveFrame && _dwActiveFrame < 300) {
        if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {

            int dx = _pOrg->_pLockOnTarget->_X - _X;
            int dy = _pOrg->_pLockOnTarget->_Y - _Y;
            int dz = _pOrg->_pLockOnTarget->_Z - _Z;

            if (-_slow_renge < dx && dx < _slow_renge) {
                _pMover->setVxMvAcce(0);
                _pMover->_veloVxMv *= 0.6;
            } else {
                _pMover->setVxMvAcce(dx/200);
                //_TRACE_("dx="<<dx);
            }

            if (-_slow_renge < dy && dy < _slow_renge) {
                _pMover->setVyMvAcce(0);
                _pMover->_veloVyMv *= 0.6;
            } else {
                _pMover->setVyMvAcce(dy/200);
            }

            if (-_slow_renge < dz && dz < _slow_renge) {
                _pMover->setVzMvAcce(0);
                _pMover->_veloVzMv *= 0.6;
            } else {
                _pMover->setVzMvAcce(dz/200);
            }



        } else {
            _pOrg->_pLockOnTarget = NULL;
        }
    } else {
        //_pMover->setMvVelo(80000);
    }

    if (_pChip_front) {

        if (_pChip_front->_pMover->_veloVxMv + asobiX < _pMover->_veloVxMv) {
            _pMover->_veloVxMv = _pChip_front->_pMover->_veloVxMv + asobiX;
        }
        if (_pChip_front->_pMover->_veloVxMv - asobiX > _pMover->_veloVxMv) {
            _pMover->_veloVxMv = _pChip_front->_pMover->_veloVxMv - asobiX;
        }

        if (_pChip_front->_pMover->_veloVyMv + asobiY < _pMover->_veloVyMv) {
            _pMover->_veloVyMv = _pChip_front->_pMover->_veloVyMv + asobiY;
        }
        if (_pChip_front->_pMover->_veloVyMv - asobiY > _pMover->_veloVyMv) {
            _pMover->_veloVyMv = _pChip_front->_pMover->_veloVyMv - asobiY;
        }

        if (_pChip_front->_pMover->_veloVzMv + asobiZ < _pMover->_veloVzMv) {
            _pMover->_veloVzMv = _pChip_front->_pMover->_veloVzMv + asobiZ;
        }
        if (_pChip_front->_pMover->_veloVzMv - asobiZ > _pMover->_veloVzMv) {
            _pMover->_veloVzMv = _pChip_front->_pMover->_veloVzMv - asobiZ;
        }
        //_pMover->setFaceAng(_pMover->_veloVxMv, _pMover->_veloVyMv, _pMover->_veloVzMv);
    }
    CurveLaserChip::processBehavior();

}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (_pOrg->_pLockOnTarget) {
        if (pOther == _pOrg->_pLockOnTarget) {
            _is_lockon = false; //一回ヒットしたらロックオンは外す
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
void MyCurveLaserChip001::processFinal() {
    CurveLaserChip::processFinal();
    //ロックオンが消滅ならば、切る
    if (_pOrg->_pLockOnTarget) {
        if (_pOrg->_pLockOnTarget->_pStatus->get(STAT_Stamina) <= 0) {
            _pOrg->_pLockOnTarget = NULL;
        }
    }
}

MyCurveLaserChip001::~MyCurveLaserChip001() {
}

