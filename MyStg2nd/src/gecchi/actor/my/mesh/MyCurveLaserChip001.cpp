#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "12/laser_chip") { //LaserChip系は最大12セット
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _pOrg = NULL;
    _lockon = 0;

}

void MyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 100 * 1000;
    _fAlpha = 0.99f;
    _fBoundingSphereRadius = 50.0f;

}

void MyCurveLaserChip001::onActive() {
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    CurveLaserChip::onActive();
    _pMover->setMvVelo(0);
    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 1;
        } else {
            //先端以外
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 0;
        } else {
            //先端以外
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
        _pOrg->_pLockOnTarget = NULL;
    }
    _renge = 150000;
    _pMover->forceVxMvVeloRange(-_renge, _renge);
    _pMover->forceVyMvVeloRange(-_renge, _renge);
    _pMover->forceVzMvVeloRange(-_renge, _renge);

    _pMover->forceVxMvAcceRange(-_renge / 20, _renge / 20);
    _pMover->forceVyMvAcceRange(-_renge / 20, _renge / 20);
    _pMover->forceVzMvAcceRange(-_renge / 20, _renge / 20);
}

void MyCurveLaserChip001::processBehavior() {
    if (_lockon == 1) {
        if (getPartFrame() < 180) {
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
                int dx = _pOrg->_pLockOnTarget->_X - (_X + _pMover->_veloVxMv*10);
                int dy = _pOrg->_pLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*7);
                int dz = _pOrg->_pLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*10);
                _pMover->setVxMvAcce(dx);
                _pMover->setVyMvAcce(dy);
                _pMover->setVzMvAcce(dz);
            } else {
                _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
            }
        } else {
            _lockon = 2;
        }
    } else if (_lockon == 2) {
        int dx, dy, dz;
        if (_pChip_front == NULL) {
//            _pMover->addVxMvAcce(_pMover->_acceVxMv);
//            _pMover->addVyMvAcce(_pMover->_acceVyMv);
//            _pMover->addVzMvAcce(_pMover->_acceVzMv);
        } else if (_pChip_front->_pChip_front == NULL) {
            //新たなターゲットを作成
            dx = _pChip_front->_X - (_X + _pMover->_veloVxMv);
            dy = _pChip_front->_Y - (_Y + _pMover->_veloVyMv);
            dz = _pChip_front->_Z - (_Z + _pMover->_veloVzMv);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*2);
            dy = _pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*2);
            dz = _pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*2);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else {
            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        }
    }
    if (_pChip_front == NULL) {
        _pSeReflector->behave();
    }
    CurveLaserChip::processBehavior();//座標を移動させてから呼び出すこと
}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
    if (pOther->getKind() & KIND_ENEMY) {
        //敵の場合
        if (_pOrg->_pLockOnTarget) {
            if (pOther == _pOrg->_pLockOnTarget) {
                _lockon = 2; //非ロックオン（ロックオン→非ロックオン）

                //中間先頭チップがヒットした場合の処理。(_chip_kind=3の場合)
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //先端チップへ今後の方針を伝える。（先端チップは当たり判定がないため）
                    MyCurveLaserChip001* pTip = (MyCurveLaserChip001*)_pChip_front; //先端チップ
                    pTip->_lockon = 2; //先端に伝える
                    //今後の移動方角(加速度)を伝えるのだが、先端チップや自身や移動方向は、急激な角度に曲がっている可能性が極めて高く
                    //不自然な角度のカーブを描きかねないので、やや後方のチップが存在するならば、そちらの移動方向をコピーする。
                    LaserChip* pChipPrev = this;
                    for (int i = 0; i < 3; i++) { //最高3つ後方まで在れば採用
                        if (pChipPrev->_pChip_behind) {
                            pChipPrev = pChipPrev->_pChip_behind;
                        } else {
                            break;
                        }
                    }
                    pTip->_pMover->setVxMvVelo(pChipPrev->_pMover->_veloVxMv*2);
                    pTip->_pMover->setVyMvVelo(pChipPrev->_pMover->_veloVyMv*2);
                    pTip->_pMover->setVzMvVelo(pChipPrev->_pMover->_veloVzMv*2);
                    //ターゲットに向かっている最中であるため、殆どの場合減速中である。
                    //そのま加速度を設定すると、いずれ逆方向に向かうことになってしまう。。
                    //本来向かうべき方向に近似するため、正負逆を設定する。
                    pTip->_pMover->setVxMvAcce(-(pChipPrev->_pMover->_acceVxMv));
                    pTip->_pMover->setVyMvAcce(-(pChipPrev->_pMover->_acceVyMv));
                    pTip->_pMover->setVzMvAcce(-(pChipPrev->_pMover->_acceVzMv));
                }
            }
        } else {
            _pOrg->_pLockOnTarget = pOther;
        }
        //ここにMyのヒットエフェクト
        if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
            //ここにMyの消滅エフェクト
            inactivate();
        } else {

        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        inactivate();
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

