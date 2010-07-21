#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshActor(prm_name, "Astraea") {
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);

    //レーザーストック
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 30;
    _laser_interval = 600;
    _angveloTurn = 200;
    _shot_interval = 30;

    _papapLaserChipDispatcher = NEW LaserChipDispatcher**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipDispatcher[i] = NEW LaserChipDispatcher*[_laser_way];
    }
    _paWayRz = NEW angle[_laser_way];
    _paWayRy = NEW angle[_laser_way];

    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipDispatcher[i][j] = NULL;
        }
    }

    _pDispatcher_Shot = NULL;
    _pDpcon = (DispatcherConnection*)(pGOD->_pDispatcherManager->connect("DpCon_Shot004"));


    _pSeReflector->useSe(2);
    _pSeReflector->set(0, "yume_Sbend", GgafRepeatSeq::nextVal("CH_yume_Sbend"));
    _pSeReflector->set(1, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
    _frame_shot_after = 1000;
    _iMovePatternNo = 0;
}

void EnemyAstraea::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 12.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(1.0);
    _pGgafDx9Model->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.97;
}
void EnemyAstraea::initialize() {
    setHitAble(true);
    setAlpha(0.99);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 200*1000);
    _pMover->setMvVelo(-5000);
    _frame_shot_after = 1000;
    _iMovePatternNo = 0;
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight;
    _pDispatcher_Shot = _pDpcon->view();
}


void EnemyAstraea::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);
    _pMover->setMvVelo(-5000);
    _frame_shot_after = 1000;
    _iMovePatternNo = 0;
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight;
}

void EnemyAstraea::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->loopTriangleWave(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAcceStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pMorpher->loopTriangleWave(3, 20, 13, 2);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmediately(3);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pMorpher->loopTriangleWave(4, 60, 3, 20);
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
    if (_iMovePatternNo == 0) {
        _pMover->setFaceAngVelo(AXIS_X, 0);
        _pMover->setFaceAngVelo(AXIS_Z, _angveloTurn*1.5);
        _pMover->setFaceAngVelo(AXIS_Y, _angveloTurn*0.5);
        _pMover->setMvVelo(-3000);
        _iMovePatternNo = 1;
    } else if (_iMovePatternNo == 1 ) {
        if (getBehaveingFrame() % _laser_interval == 0 && _X > pMYSHIP->_X-400000) {
            _pMover->execTagettingFaceAngSequence(GameGlobal::_pMyShip,
                                                _angveloTurn*20, 0,
                                                TURN_COUNTERCLOCKWISE, false);
            _iMovePatternNo = 2;
            _cnt_laserchip = 0;
        } else {
            //８方向ショット
            if (getBehaveingFrame() % _shot_interval == 0) {
                angle Rz, Ry;
                GgafDx9DrawableActor* pActor;
                static double SQR2 = 1.41421356;
                D3DXMATRIX matWorldRot;
                GgafDx9Util::setWorldMatrix_RxRzRy(this, matWorldRot);
                //＜８方向ショット向きを、RzRyで取得する＞
                //ローカルでのショットの方向ベクトルを(_Xorg,_Yorg,_Zorg)、
                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                //
                //                      | mat_11 mat_12 mat_13 |
                //| _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                //                      | mat_31 mat_32 mat_33 |
                //
                //vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                //vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                //vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                //
                //さてここで、ローカルのショットの８方向とは、とげとげへの方向のことで、
                //�@( 2a, 0, a√2)   �A( 2a, a√2, 0)   �B( 2a, 0,-a√2)   �C( 2a,-a√2, 0)
                //�D(-2a, 0, a√2)   �E(-2a, a√2, 0)   �F(-2a, 0,-a√2)   �G(-2a,-a√2, 0)
                //である。それぞれ 2a=モデル境界球半径(R)と置いた場合
                //a√2 = R/2*√2 …これを
                int R = _pGgafDx9Model->_fBoundingSphereRadius*PX_UNIT*LEN_UNIT;
                int ASQR2 = A2*SQR2/2;
                //�@( 2a, 0, a√2)は
                //vX = 2*mat_11                + √2*mat_31
                //vY = 2*mat_12                + √2*mat_32
                //vZ = 2*mat_13                + √2*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       2.0*matWorldRot._11 + SQR2*matWorldRot._31,
                       2.0*matWorldRot._12 + SQR2*matWorldRot._32,
                       2.0*matWorldRot._13 + SQR2*matWorldRot._33,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�A( 2a, a√2, 0)は
                //vX = 2*mat_11  + √2*mat_21
                //vY = 2*mat_12  + √2*mat_22
                //vZ = 2*mat_13  + √2*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       2.0*matWorldRot._11 + SQR2*matWorldRot._21,
                       2.0*matWorldRot._12 + SQR2*matWorldRot._22,
                       2.0*matWorldRot._13 + SQR2*matWorldRot._23,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�B( 2a, 0,-a√2)は
                //vX = 2*mat_11                - √2*mat_31
                //vY = 2*mat_12                - √2*mat_32
                //vZ = 2*mat_13                - √2*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       2.0*matWorldRot._11 - SQR2*matWorldRot._31,
                       2.0*matWorldRot._12 - SQR2*matWorldRot._32,
                       2.0*matWorldRot._13 - SQR2*matWorldRot._33,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�C( 2a,-a√2, 0)は
                //vX = 2*mat_11  - √2*mat_21
                //vY = 2*mat_12  - √2*mat_22
                //vZ = 2*mat_13  - √2*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       2.0*matWorldRot._11 - SQR2*matWorldRot._21,
                       2.0*matWorldRot._12 - SQR2*matWorldRot._22,
                       2.0*matWorldRot._13 - SQR2*matWorldRot._23,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�D(-2a, 0, a√2)は
                //vX = -2*mat_11                + √2*mat_31
                //vY = -2*mat_12                + √2*mat_32
                //vZ = -2*mat_13                + √2*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       -2.0*matWorldRot._11 + SQR2*matWorldRot._31,
                       -2.0*matWorldRot._12 + SQR2*matWorldRot._32,
                       -2.0*matWorldRot._13 + SQR2*matWorldRot._33,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�E(-2a, a√2, 0)は
                //vX = -2*mat_11  + √2*mat_21
                //vY = -2*mat_12  + √2*mat_22
                //vZ = -2*mat_13  + √2*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       -2.0*matWorldRot._11 + SQR2*matWorldRot._21,
                       -2.0*matWorldRot._12 + SQR2*matWorldRot._22,
                       -2.0*matWorldRot._13 + SQR2*matWorldRot._23,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�F(-2a, 0,-a√2)は
                //vX = -2*mat_11                - √2*mat_31
                //vY = -2*mat_12                - √2*mat_32
                //vZ = -2*mat_13                - √2*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       -2.0*matWorldRot._11 - SQR2*matWorldRot._31,
                       -2.0*matWorldRot._12 - SQR2*matWorldRot._32,
                       -2.0*matWorldRot._13 - SQR2*matWorldRot._33,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //�G(-2a,-a√2, 0)は
                //vX = -2*mat_11  - √2*mat_21
                //vY = -2*mat_12  - √2*mat_22
                //vZ = -2*mat_13  - √2*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    GgafDx9Util::getRzRyAng(
                       -2.0*matWorldRot._11 - SQR2*matWorldRot._21,
                       -2.0*matWorldRot._12 - SQR2*matWorldRot._22,
                       -2.0*matWorldRot._13 - SQR2*matWorldRot._23,
                       Rz, Ry
                    ); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
            }

        }
    } else if (_iMovePatternNo == 2) {
        if (!_pMover->isTagettingFaceAng()) {
            _iMovePatternNo = 3;
            _frame_shot_after = 0;
        }
    } else if (_iMovePatternNo == 3) {
        _pMover->setFaceAngVelo(AXIS_X, _angveloTurn*40);
        _pMover->setFaceAngVelo(AXIS_Z, 0);
        _pMover->setFaceAngVelo(AXIS_Y, 0);
        _pMover->setMvVelo(0);
        if (_cnt_laserchip < _laser_length) {
            _cnt_laserchip++;

            static EnemyAstraeaLaserChip001* pLaserChip;

            angle angClearance = 10000;//開き具合
            GgafDx9Util::getWayAngle2D(_pMover->_angFace[AXIS_Z], _laser_way, angClearance, _paWayRz);
            GgafDx9Util::getWayAngle2D(_pMover->_angFace[AXIS_Y], _laser_way, angClearance, _paWayRy);


            for (int i = 0; i < _laser_way; i++) {

                for (int j = 0; j < _laser_way; j++) {


                    if (_papapLaserChipDispatcher[i][j] == NULL) {
                        GgafMainActor* p = pCOMMONSCENE->_pDispatcher_LaserChipDispatcher->employ();
                        if (p == NULL) {
                            //レーザーセットは借入出来ない
                            continue;
                        } else {
                            _papapLaserChipDispatcher[i][j] = (LaserChipDispatcher*)p;
                            _papapLaserChipDispatcher[i][j]->_num_continual_employ_max = _laser_length;
                            _papapLaserChipDispatcher[i][j]->_num_chip_interval = 0;
                            _papapLaserChipDispatcher[i][j]->activate();

                        }
                    }

                    pLaserChip = (EnemyAstraeaLaserChip001*)_papapLaserChipDispatcher[i][j]->employ();
                    if (pLaserChip != NULL) {
                        pLaserChip->activate();
                        pLaserChip->setGeometry(this);
                        pLaserChip->_pMover->setRzRyMvAng(_paWayRz[i], _paWayRy[j]);
                        pLaserChip->_pMover->_angFace[AXIS_Z] = _paWayRz[i];
                        pLaserChip->_pMover->_angFace[AXIS_Y] = _paWayRy[j];
                        pLaserChip->_pMover->behave();

                        if (i == 0 && j == 0 && pLaserChip->_pChip_front == NULL) {
                            _pSeReflector->play3D(0); //発射音
                            chengeEffectTechniqueInterim("Flush", 5); //フラッシュ
                        }
                    }
                }
            }
        } else {
            _iMovePatternNo = 0;
        }
    }

    _pSeReflector->behave();
    _pMover->behave();
}

void EnemyAstraea::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void EnemyAstraea::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    chengeEffectTechniqueInterim("Flush", 2); //フラッシュ
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        _pSeReflector->play3D(1);
        sayonara();
        //消滅エフェクト
    } else {

    }
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
}


void EnemyAstraea::onInactive() {
//    //レーザーは遅れてからディスパッチャーに戻す
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            if (_papapLaserChipDispatcher[i][j]) {
                _papapLaserChipDispatcher[i][j]->inactivateAfter(60);
            }
        }
    }
    sayonara();
}


EnemyAstraea::~EnemyAstraea() {
    DELETEARR_IMPOSSIBLE_NULL(_paWayRz);
    DELETEARR_IMPOSSIBLE_NULL(_paWayRy);
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher);


}
