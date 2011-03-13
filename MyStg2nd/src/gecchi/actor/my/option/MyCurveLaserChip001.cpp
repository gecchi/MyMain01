#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "MyCurveLaserChip001") {
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;

}

void MyCurveLaserChip001::initialize() {
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 6 * 1000;
    _fAlpha = 0.99f;
    _fBoundingSphereRadius = 60.0f;

}

void MyCurveLaserChip001::onActive() {
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    CurveLaserChip::onActive();
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    _pKuroko->setMvVelo(0);
    _pKuroko->setVxMvAcce(0);
    _pKuroko->setVyMvAcce(0);
    _pKuroko->setVzMvAcce(0);
    _isLockon = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 1;
            _isLockon = true;
        } else {
            //先端以外
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
            _isLockon = ((MyCurveLaserChip001*) _pChip_front)->_isLockon;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 0;
        } else {
            //先端以外
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
            _isLockon = ((MyCurveLaserChip001*) _pChip_front)->_isLockon;//一つ前のロックオン情報を引き継ぐ
        }
    }
    _renge = 150000;
    _pKuroko->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge / 30;
    _pKuroko->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);


}

void MyCurveLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();

    if (_lockon == 1) {
        if (getActivePartFrame() < 120) {
            _maxAcceRange+=100;
            _pKuroko->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor() && _pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) > 0) {
                                                                                 //体力の判定はオプション側で行うことにした
            if (pMainLockOnTarget) {
                if (pMainLockOnTarget->isActiveActor()) {
                    float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
                    rate = rate > 0 ? rate : 0;
                    int fdx = pMainLockOnTarget->_X - (_X + _pKuroko->_veloVxMv*rate);
                    int fdy = pMainLockOnTarget->_Y - (_Y + _pKuroko->_veloVyMv*rate);
                    int fdz = pMainLockOnTarget->_Z - (_Z + _pKuroko->_veloVzMv*rate);
                    _pKuroko->setVxMvAcce(fdx);
                    _pKuroko->setVyMvAcce(fdy);
                    _pKuroko->setVzMvAcce(fdz);
                } else {


                }
            } else {
                _lockon = 2;
            }
        } else {
            _lockon = 2;
        }
    }



    int dx, dy, dz;
    if (_lockon == 2) {
        if (_isLockon) {
            _isLockon = false;
            //先端ならば特別に、オプションの反対の座標をターゲットする
            if (_pChip_front == NULL) {
                _new_target_X = _X + (_X - _pOrg->_X);
                _new_target_Y = _Y + (_Y - _pOrg->_Y);
                _new_target_Z = _Z + (_Z - _pOrg->_Z);
                dx = _new_target_X - (_X );
                dy = _new_target_Y - (_Y );
                dz = _new_target_Z - (_Z );
                _pKuroko->setVxMvAcce(dx);
                _pKuroko->setVyMvAcce(dy);
                _pKuroko->setVzMvAcce(dz);
            }
        }



        _maxAcceRange+=100;
        _pKuroko->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
        if (_pChip_front == NULL) {
            _maxAcceRange+=100;
            //上の処理１回と、毎回 _maxAcceRange+=100;
        } else if (_pChip_front->_pChip_front == NULL) {
            //新たなターゲットを作成
            dx = _pChip_front->_X - (_X + _pKuroko->_veloVxMv);
            dy = _pChip_front->_Y - (_Y + _pKuroko->_veloVyMv);
            dz = _pChip_front->_Z - (_Z + _pKuroko->_veloVzMv);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*2);
            dy = _pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*2);
            dz = _pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*2);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*3);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        } else {
            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*3);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        }
    }
    if (_pChip_front == NULL) {
        _pSeTransmitter->behave();
    }

//    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
//        _lockon = 1;
//        _isLockon = true;
//    }

//    _pKuroko->_angFace[AXIS_X] =  _pOrg->_pKuroko->_angFace[AXIS_Y];
    CurveLaserChip::processBehavior();//座標を移動させてから呼び出すこと

    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        locateWith(_pOrg);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyCurveLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    //ヒットエフェクト
    //無し

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                _lockon = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //中間先頭チップがヒットした場合、先端にも伝える
                    ((MyCurveLaserChip001*)_pChip_front)->_lockon = 2;
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合
            }
        } else {
            //オプション非ロックオン中に命中した場合
        }

        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力

            //破壊されたエフェクト
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
            if (pExplo001) {
                pExplo001->locateWith(this);
                pExplo001->activate();
            }
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                _pOrg->_pLockonController->lockon(pOther);
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, _default_stamina);
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                _pOrg->_pLockonController->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら

        //破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->locateWith(this);
            pExplo001->activate();
        }
        sayonara();
    }
}
//void MyCurveLaserChip001::processFinal() {
//    CurveLaserChip::processFinal();
//    //ロックオンが消滅ならば、切る
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
//        }
//    }
//}

void MyCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

MyCurveLaserChip001::~MyCurveLaserChip001() {
}

