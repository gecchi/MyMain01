#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) :
    CurveLaserChip(prm_name, "12/laser_chip") {
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _pOrg = NULL;
    _is_lockon = false;

    _cnt_rev = 0;
}

void MyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);

    registHitAreaCube(60000);

    setHitAble(true);
    _SX = _SY = _SZ = 200 * 1000;
    _fAlpha = 0.99f;
    _max_radius = 50.0f;


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
        if (_pChip_front == NULL) {
            _is_lockon = true;
        } else {
            _is_lockon = ((MyCurveLaserChip001*) _pChip_front)->_is_lockon;
        }
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

    _slow_renge = 10000;
    _renge = 100000;
    _pMover->setVxMvVeloRenge(-_renge, _renge);
    _pMover->setVyMvVeloRenge(-_renge, _renge);
    _pMover->setVzMvVeloRenge(-_renge, _renge);

    _pMover->setVxMvAcceRenge(-_renge / 10, _renge / 10);
    _pMover->setVyMvAcceRenge(-_renge / 10, _renge / 10);
    _pMover->setVzMvAcceRenge(-_renge / 10, _renge / 10);
}

void MyCurveLaserChip001::processBehavior() {
    int asobiX, asobiY, asobiZ;
//    if (_pChip_front) {
//        asobiX = abs(_pChip_front->_pMover->_veloVxMv - _pMover->_veloVxMv);
//        asobiY = abs(_pChip_front->_pMover->_veloVyMv - _pMover->_veloVyMv);
//        asobiZ = abs(_pChip_front->_pMover->_veloVzMv - _pMover->_veloVzMv);
//    } else {
//        asobiX = 0;
//        asobiY = 0;
//        asobiZ = 0;
//    }

    if (_is_lockon) {

        if (1 < getPartFrame() && getPartFrame() < 120) {
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {

                int dx = _pOrg->_pLockOnTarget->_X - _X;
                int dy = _pOrg->_pLockOnTarget->_Y - _Y;
                int dz = _pOrg->_pLockOnTarget->_Z - _Z;
                if (-_slow_renge < dx && dx < _slow_renge) {
                    _pMover->_veloVxMv *= 0.4;
                } else {
                }
                _pMover->setVxMvAcce(dx);

                if (-_slow_renge < dy && dy < _slow_renge) {
                    _pMover->_veloVyMv *= 0.4;
                } else {
                }
                _pMover->setVyMvAcce(dy);

                if (-_slow_renge < dz && dz < _slow_renge) {
                    _pMover->_veloVzMv *= 0.4;
                } else {
                }
                _pMover->setVzMvAcce(dz);

            } else {
                _is_lockon = false;
                _pOrg->_pLockOnTarget = NULL;
            }
        } else {

        }
    } else {
    }

//    if (_pChip_front && _pChip_front->_pChip_front) {
//        _pChip_front->_pMover->_veloVxMv = (_pMover->_veloVxMv + _pChip_front->_pChip_front->_pMover->_veloVxMv) / 2;
//        _pChip_front->_pMover->_veloVyMv = (_pMover->_veloVyMv + _pChip_front->_pChip_front->_pMover->_veloVyMv) / 2;
//        _pChip_front->_pMover->_veloVzMv = (_pMover->_veloVzMv + _pChip_front->_pChip_front->_pMover->_veloVzMv) / 2;
//    }

//    if (0 < getPartFrame() && getPartFrame() <= 3) {
//        _pMover->setVxMvAcceRenge(-_renge / 30, _renge / 30);
//        _pMover->setVyMvAcceRenge(-_renge / 30, _renge / 30);
//        _pMover->setVzMvAcceRenge(-_renge / 30, _renge / 30);
//    } else if (5 < getPartFrame() && getPartFrame() <= 6) {
//        _pMover->setVxMvAcceRenge(-_renge / 20, _renge / 20);
//        _pMover->setVyMvAcceRenge(-_renge / 20, _renge / 20);
//        _pMover->setVzMvAcceRenge(-_renge / 20, _renge / 20);
//    } else {
//        _pMover->setVxMvAcceRenge(-_renge / 10, _renge / 10);
//        _pMover->setVyMvAcceRenge(-_renge / 10, _renge / 10);
//        _pMover->setVzMvAcceRenge(-_renge / 10, _renge / 10);
//    }

    CurveLaserChip::processBehavior();

}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
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

