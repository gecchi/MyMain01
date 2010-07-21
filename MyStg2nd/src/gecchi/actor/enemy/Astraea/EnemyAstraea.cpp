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
    _laser_interval = 6000;
    _angveloTurn = 100;
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
    _pMover->setMvVelo(-1000);
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
                int vX, vY, vZ;
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
                //さてここで、ローカルのショットの８方向とは、とげとげへの方向のことで、立方体の1辺の半分をaとすると
                //①( a, 0, a√2)   ②( a, a√2, 0)   ③( a, 0,-a√2)   ④( a,-a√2, 0)
                //⑤(-a, 0, a√2)   ⑥(-a, a√2, 0)   ⑦(-a, 0,-a√2)   ⑧(-a,-a√2, 0)
                //である。それぞれ
                //a = とげとげまでの距離 … これを R と置き
                //a√2 = R *√2          … これを S としよう
                double R = _pGgafDx9Model->_fBoundingSphereRadius/2; //とげとげへの距離
                double S = R*SQR2;
                //①( a, 0, a√2)は
                //vX = R*mat_11                + S*mat_31
                //vY = R*mat_12                + S*mat_32
                //vZ = R*mat_13                + S*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (R*matWorldRot._11 + S*matWorldRot._31)*PX_UNIT*LEN_UNIT;
                    vY = (R*matWorldRot._12 + S*matWorldRot._32)*PX_UNIT*LEN_UNIT;
                    vZ = (R*matWorldRot._13 + S*matWorldRot._33)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //②( a, a√2, 0)は
                //vX = R*mat_11  + S*mat_21
                //vY = R*mat_12  + S*mat_22
                //vZ = R*mat_13  + S*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (R*matWorldRot._11 + S*matWorldRot._21)*PX_UNIT*LEN_UNIT;
                    vY = (R*matWorldRot._12 + S*matWorldRot._22)*PX_UNIT*LEN_UNIT;
                    vZ = (R*matWorldRot._13 + S*matWorldRot._23)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //③( a, 0,-a√2)は
                //vX = R*mat_11                - S*mat_31
                //vY = R*mat_12                - S*mat_32
                //vZ = R*mat_13                - S*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (R*matWorldRot._11 - S*matWorldRot._31)*PX_UNIT*LEN_UNIT;
                    vY = (R*matWorldRot._12 - S*matWorldRot._32)*PX_UNIT*LEN_UNIT;
                    vZ = (R*matWorldRot._13 - S*matWorldRot._33)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //④( a,-a√2, 0)は
                //vX = R*mat_11  - S*mat_21
                //vY = R*mat_12  - S*mat_22
                //vZ = R*mat_13  - S*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (R*matWorldRot._11 - S*matWorldRot._21)*PX_UNIT*LEN_UNIT;
                    vY = (R*matWorldRot._12 - S*matWorldRot._22)*PX_UNIT*LEN_UNIT;
                    vZ = (R*matWorldRot._13 - S*matWorldRot._23)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //⑤(-a, 0, a√2)は
                //vX = -R*mat_11                + S*mat_31
                //vY = -R*mat_12                + S*mat_32
                //vZ = -R*mat_13                + S*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (-R*matWorldRot._11 + S*matWorldRot._31)*PX_UNIT*LEN_UNIT;
                    vY = (-R*matWorldRot._12 + S*matWorldRot._32)*PX_UNIT*LEN_UNIT;
                    vZ = (-R*matWorldRot._13 + S*matWorldRot._33)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //⑥(-a, a√2, 0)は
                //vX = -R*mat_11  + S*mat_21
                //vY = -R*mat_12  + S*mat_22
                //vZ = -R*mat_13  + S*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (-R*matWorldRot._11 + S*matWorldRot._21)*PX_UNIT*LEN_UNIT;
                    vY = (-R*matWorldRot._12 + S*matWorldRot._22)*PX_UNIT*LEN_UNIT;
                    vZ = (-R*matWorldRot._13 + S*matWorldRot._23)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //⑦(-a, 0,-a√2)は
                //vX = -R*mat_11                - S*mat_31
                //vY = -R*mat_12                - S*mat_32
                //vZ = -R*mat_13                - S*mat_33
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (-R*matWorldRot._11 - S*matWorldRot._31)*PX_UNIT*LEN_UNIT;
                    vY = (-R*matWorldRot._12 - S*matWorldRot._32)*PX_UNIT*LEN_UNIT;
                    vZ = (-R*matWorldRot._13 - S*matWorldRot._33)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                    pActor->activate();
                }
                //⑧(-a,-a√2, 0)は
                //vX = -R*mat_11  - S*mat_21
                //vY = -R*mat_12  - S*mat_22
                //vZ = -R*mat_13  - S*mat_23
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    vX = (-R*matWorldRot._11 - S*matWorldRot._21)*PX_UNIT*LEN_UNIT;
                    vY = (-R*matWorldRot._12 - S*matWorldRot._22)*PX_UNIT*LEN_UNIT;
                    vZ = (-R*matWorldRot._13 - S*matWorldRot._23)*PX_UNIT*LEN_UNIT;
                    GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                    pActor->setGeometry(_X+vX, _Y+vY, _Z+vZ);
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
    _pDpcon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paWayRz);
    DELETEARR_IMPOSSIBLE_NULL(_paWayRy);
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher);


}
