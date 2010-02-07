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

    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
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
            _is_lockon = ((MyCurveLaserChip001*) _pChip_front)->_is_lockon;//一つ前のロックオン情報を引き継ぐ
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
    _renge = 120000;
    _pMover->setVxMvVeloRenge(-_renge, _renge);
    _pMover->setVyMvVeloRenge(-_renge, _renge);
    _pMover->setVzMvVeloRenge(-_renge, _renge);

    _pMover->setVxMvAcceRenge(-_renge / 30, _renge / 30);
    _pMover->setVyMvAcceRenge(-_renge / 30, _renge / 30);
    _pMover->setVzMvAcceRenge(-_renge / 30, _renge / 30);
}

void MyCurveLaserChip001::processBehavior() {
    int asobiX, asobiY, asobiZ;
//    if (getPartFrame() == 0) {
//        return;
//    }
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

        if (1 < getPartFrame() && getPartFrame() < 10000) {
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {

                int dx = _pOrg->_pLockOnTarget->_X - (_X + _pMover->_veloVxMv*8);
                int dy = _pOrg->_pLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*7);
                int dz = _pOrg->_pLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*8);

                if (-_slow_renge < dx && dx < _slow_renge) {
                    //_pMover->_veloVxMv *= 0.4;
                } else {
                }
                _pMover->setVxMvAcce(dx);

                if (-_slow_renge < dy && dy < _slow_renge) {
                   // _pMover->_veloVyMv *= 0.4;
                } else {
                }
                _pMover->setVyMvAcce(dy);

                if (-_slow_renge < dz && dz < _slow_renge) {
                    //_pMover->_veloVzMv *= 0.4;
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
    if (getPartFrame() > 0) {
        CurveLaserChip::processBehavior();
    }
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}

void MyCurveLaserChip001::processPreJudgement() {

    if (_pChip_front == NULL) {
        //先頭は何もなし
    } else if (_pChip_behind == NULL) {
        //末尾
    } else if (_pChip_front->isActive() && _pChip_behind->isActive()) {
        //_pChip_behind == NULL の判定だけではだめ_pChip_behind->isActive()と判定すること
        //なぜならemployの瞬間に_pChip_behind != NULL となるが、active()により有効になるのは次フレームだから
        //_X,_Y,_Z にはまだ変な値が入っている。
        MyCurveLaserChip001* pF = (MyCurveLaserChip001*)_pChip_front;
        MyCurveLaserChip001* pB = (MyCurveLaserChip001*)_pChip_behind;
        //中間
        _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
        _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
        _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
    }

    CurveLaserChip::processPreJudgement();
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
            _is_lockon = false;
        }
    }
}

void MyCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _is_lockon = false;
}

MyCurveLaserChip001::~MyCurveLaserChip001() {
}

