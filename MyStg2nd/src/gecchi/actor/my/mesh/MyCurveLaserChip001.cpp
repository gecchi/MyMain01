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
    _lockon = 0;

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
    _veloCurve = 1000;

    if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
        if (_pChip_front == NULL) {
            //先頭チップ
            _lockon = 1;
        } else {
            //先頭以外
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先頭チップ
            _lockon = 0;
        } else {
            //先頭以外
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
        _pOrg->_pLockOnTarget = NULL;
    }

    _renge = 120000;
    _pMover->setVxMvVeloRenge(-_renge, _renge);
    _pMover->setVyMvVeloRenge(-_renge, _renge);
    _pMover->setVzMvVeloRenge(-_renge, _renge);

    _pMover->setVxMvAcceRenge(-_renge / 20, _renge / 20);
    _pMover->setVyMvAcceRenge(-_renge / 20, _renge / 20);
    _pMover->setVzMvAcceRenge(-_renge / 20, _renge / 20);
    _cnt_curve = 0;
}

void MyCurveLaserChip001::processBehavior() {
    if (_lockon == 1) {

        if (1 < getPartFrame() && getPartFrame() < 180) {
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
                int dx = _pOrg->_pLockOnTarget->_X - (_X + _pMover->_veloVxMv*10);
                int dy = _pOrg->_pLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*7);
                int dz = _pOrg->_pLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*10);
                _pMover->setVxMvAcce(dx);
                _pMover->setVyMvAcce(dy);
                _pMover->setVzMvAcce(dz);
            } else {
                _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
                _pOrg->_pLockOnTarget = NULL;
            }
        } else {

        }
    } else if (_lockon == 2) {
        if (_pChip_front == NULL) {
            _pMover->addVxMvAcce(_pMover->_acceVxMv);
            _pMover->addVyMvAcce(_pMover->_acceVyMv);
            _pMover->addVzMvAcce(_pMover->_acceVzMv);
        } else if (_pChip_front->_pChip_front == NULL) {
            //新たなターゲットを作成
            int dx = _pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            int dy = _pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            int dz = _pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else {
            int dx = _pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            int dy = _pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            int dz = _pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        }
    }

    //これにより発射元の根元から表示される
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
        //_pChip_behind == NULL の判定だけではだめ。_pChip_behind->isActive()と判定すること
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
            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
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
            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
        }
    }
}

void MyCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

MyCurveLaserChip001::~MyCurveLaserChip001() {
}

