#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshActor(prm_name, "Astraea") {
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);

    //レーザー
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 30;
    _laser_interval = 300;
    _angveloTurn = 100;
    _angClearance = 30000;//開き具合
    _papapLaserChipStore = NEW LaserChipStore**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipStore[i] = NEW LaserChipStore*[_laser_way];
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipStore[i][j] = NULL;
        }
    }

    _pCon_RefractionEffectStore =
            (StoreConnection*)(P_GOD->_pStoreManager->getConnection("StCon_EffRefraction001"));
    _pCon_LaserChipStoreDp =
            (StoreConnection*)(P_GOD->_pStoreManager->getConnection(
                                                           "StCon_EnemyAstraeaLaserChip001StoreDp",
                                                           //"StCon_EnemyAstraeaLaserChip002StoreDp",
                                                           _pCon_RefractionEffectStore->refer()
                                                      ));

    _papaPosLaser = NEW PosLaser*[_laser_way];
    angle* paAngWay = NEW angle[_laser_way];
    GgafDx9Util::getWayAngle2D(0, _laser_way, _angClearance, paAngWay);
    angle Rz,Ry;
    float vx, vy, vz;
    for (int i = 0; i < _laser_way; i++) {
        Rz = GgafDx9Util::simplifyAng(paAngWay[i]);
        _papaPosLaser[i] = NEW PosLaser[_laser_way];
        for (int j = 0; j < _laser_way; j++) {
            Ry = GgafDx9Util::simplifyAng(paAngWay[j]);
            GgafDx9Util::getNormalizeVectorZY(Rz, Ry, vx, vy, vz);
            _papaPosLaser[i][j].X = vx * 100*1000;
            _papaPosLaser[i][j].Y = vy * 100*1000;
            _papaPosLaser[i][j].Z = vz * 100*1000;
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);

    _pEffect_Appearance = NULL;

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "yume_Sbend", GgafRepeatSeq::nextVal("CH_yume_Sbend"));
    _pSeTransmitter->set(1, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
    useProgress(4);
}

void EnemyAstraea::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.97, 0.5, 12.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(1.0);
    _pGgafDx9Model->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
}

void EnemyAstraea::initialize() {
    setHitAble(true);
    setAlpha(0.99);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 200*1000);
    _pMvNavigator->setRzRyMvAng(0, ANGLE180);
    _pMvNavigator->setMvVelo(3000);
}


void EnemyAstraea::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight;

    if (_pEffect_Appearance) {
        _pEffect_Appearance->activate();
    }

    _pPrg->set(ASTRAEA_PROG_MOVE);
}

void EnemyAstraea::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->beat(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAcceStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->beat(3, 20, 13, 2);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmediately(3);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->beat(4, 60, 3, 20);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pMorpher->stopImmediately(4);
//    }
//    _pMorpher->behave();

//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->intoTargetLinerUntil(1, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 1.0, 30);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    }
//    _pMorpher->behave();
    /////////////モーフテスト////////////////


    switch (_pPrg->get()) {
        case ASTRAEA_PROG_MOVE: {
            if (_pPrg->isJustChanged()) {
                _pMvNavigator->setFaceAngVelo(AXIS_X, 0);
                _pMvNavigator->setFaceAngVelo(AXIS_Z, _angveloTurn*0.3);
                _pMvNavigator->setFaceAngVelo(AXIS_Y, _angveloTurn*0.5);
                _pMvNavigator->setMvVelo(2000);
            }
            if (getActivePartFrame() % _laser_interval == 0) {
                _pPrg->change(ASTRAEA_PROG_TURN);
            }
            break;
        }

        case ASTRAEA_PROG_TURN: {
            if (_pPrg->isJustChanged()) {
                //ターン開始
                _pMvNavigator->execTurnFaceAngSequence(
                                   P_MYSHIP,
                                   _angveloTurn*20, 0,
                                   TURN_COUNTERCLOCKWISE, false);
                _cnt_laserchip = 0;
            }
            if (_pMvNavigator->isTurningFaceAng()) {
                //ターン中
            } else {
                //自機にがいた方向に振り向きが完了時
                _pMvNavigator->setFaceAngVelo(AXIS_X, _angveloTurn*40);
                _pMvNavigator->setFaceAngVelo(AXIS_Z, 0);
                _pMvNavigator->setFaceAngVelo(AXIS_Y, 0);
                _pMvNavigator->setMvVelo(0);
                _pPrg->change(ASTRAEA_PROG_FIRE);
            }
            break;
        }

        case ASTRAEA_PROG_FIRE: {
            if (_pPrg->isJustChanged()) {
                //レーザーセット、借入
                GgafActorStoreDispatcher* pLaserChipStoreDp =
                        (GgafActorStoreDispatcher*)(_pCon_LaserChipStoreDp->refer());
                bool can_fire = false;
                for (int i = 0; i < _laser_way; i++) {
                    for (int j = 0; j < _laser_way; j++) {
                        _papapLaserChipStore[i][j] = (LaserChipStore*)(pLaserChipStoreDp->dispatch());
                        if (_papapLaserChipStore[i][j]) {
                            _papapLaserChipStore[i][j]->config(_laser_length, 1);
                            can_fire = true;
                        }
                    }
                }
                if (can_fire) {
                    _pSeTransmitter->play3D(0); //発射音
                    changeEffectTechniqueInterim("Flush", 5); //フラッシュ
                }
            }
            if (_cnt_laserchip < _laser_length) {
                _cnt_laserchip++;
                LaserChip* pLaserChip;
                PosLaser* p;
                D3DXMATRIX matWorldRot;
                GgafDx9Util::setWorldMatrix_RxRzRy(this, matWorldRot);
                angle Rz, Ry;
                int vX, vY, vZ;
                for (int i = 0; i < _laser_way; i++) {
                    for (int j = 0; j < _laser_way; j++) {
                        if (_papapLaserChipStore[i][j]) {
                            pLaserChip = _papapLaserChipStore[i][j]->dispatch();
                            if (pLaserChip) {
                                //レーザーの向きを計算
                                //ローカルでのショットの方向ベクトルを(_Xorg,_Yorg,_Zorg)、
                                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                                //
                                //                       | mat_11 mat_12 mat_13 |
                                // | _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                                //                       | mat_31 mat_32 mat_33 |
                                //よって
                                // vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                                // vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                                // vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                                //となる
                                p = &(_papaPosLaser[i][j]);
                                vX = p->X*matWorldRot._11 + p->Y*matWorldRot._21 + p->Z*matWorldRot._31;
                                vY = p->X*matWorldRot._12 + p->Y*matWorldRot._22 + p->Z*matWorldRot._32;
                                vZ = p->X*matWorldRot._13 + p->Y*matWorldRot._23 + p->Z*matWorldRot._33;
                                GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                                pLaserChip->locate(_X+vX, _Y+vY, _Z+vZ);
                                pLaserChip->_pMvNavigator->setRzRyMvAng(Rz, Ry);
                                pLaserChip->_pMvNavigator->_angFace[AXIS_Z] = Rz;
                                pLaserChip->_pMvNavigator->_angFace[AXIS_Y] = Ry;
                            }
                        }
                    }
                }
            } else {
                _pPrg->change(ASTRAEA_PROG_MOVE);
            }
            break;
        }
    }
    _pSeTransmitter->behave();
    _pMvNavigator->behave();
}

void EnemyAstraea::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAstraea::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(1);
        sayonara();
        //消滅エフェクト
    } else {

    }

}


void EnemyAstraea::onInactive() {
    //レーザーストアーは遅れてから戻す
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            if (_papapLaserChipStore[i][j]) {
                _papapLaserChipStore[i][j]->sayonara(60*10);
            }
        }
    }
    sayonara();
}


EnemyAstraea::~EnemyAstraea() {
    _pCon_RefractionEffectStore->close();
    _pCon_LaserChipStoreDp->close();
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipStore[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser);
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipStore);


}
