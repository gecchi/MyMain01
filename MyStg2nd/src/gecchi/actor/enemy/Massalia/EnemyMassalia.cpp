#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EnemyMassalia::EnemyMassalia(const char* prm_name) :
        DefaultMeshActor(prm_name, "Massalia", STATUS(EnemyMassalia)) {
    //レーザー
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 30;
    _laser_interval = 600;
    _ang_veloTurn = 100;
    _angClearance = 40000;//開き具合
    _papapLaserChipDepo = NEW LaserChipDepository**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipDepo[i] = NEW LaserChipDepository*[_laser_way];
    }


    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipDepo[i][j] = NULL;
        }
    }

    _pCon_RefractionEffectDepository = connectDepositoryManager("DpCon_EffRefraction001", NULL);

    _pDepoCon_DpEnemyMassaliaLaserChip = connectDepositoryManager(
                                                                   "DpCon_DpEnemyMassaliaLaserChip001",
                                                                   //"DpCon_DpEnemyMassaliaLaserChip002",
                                                                   _pCon_RefractionEffectDepository->use()
                                                                );


    _papaPosLaser = NEW PosLaser*[_laser_way];
    angle* paAngWay = NEW angle[_laser_way];
    GgafDxUtil::getWayAngle2D(0, _laser_way, _angClearance, paAngWay);
    angle Rz,Ry;
    float vx, vy, vz;
    for (int i = 0; i < _laser_way; i++) {
        Rz = GgafDxUtil::simplifyAng(paAngWay[i]);
        _papaPosLaser[i] = NEW PosLaser[_laser_way];
        for (int j = 0; j < _laser_way; j++) {
            Ry = GgafDxUtil::simplifyAng(paAngWay[j]);
            GgafDxUtil::getNormalizeVectorZY(Rz, Ry,
                                              vx, vy, vz);
            _papaPosLaser[i][j].X = PX2CO(vx * 100);
            _papaPosLaser[i][j].Y = PX2CO(vy * 100);
            _papaPosLaser[i][j].Z = PX2CO(vz * 100);
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(paAngWay);

    _pEffect_Appearance = NULL;

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "yume_Sbend", GgafRepeatSeq::nextVal("CH_yume_Sbend"));
    _pSeTransmitter->set(1, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
    _iMovePatternNo = 0;



}

void EnemyMassalia::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.97, 0.5, 12.0);
    _pModel->_pTextureBlinker->setBlink(1.0);
    _pModel->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
}

void EnemyMassalia::initialize() {
    setHitAble(true);
    setAlpha(0.99);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(200));
    _pKurokoA->setMvVelo(-1000);
    _iMovePatternNo = 0;
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight;
}


void EnemyMassalia::onActive() {
    //ステータスリセット
    //MyStgUtil::resetEnemyMassaliaStatus(_pStatus);
    _pKurokoA->setMvVelo(-5000);
    _iMovePatternNo = 0;
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight;

    if (_pEffect_Appearance) {
        _pEffect_Appearance->activate();
    }
}

void EnemyMassalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDxInput::isBeingPressedKey(DIK_1)) {
//        _pMorpher->beat(1, 30, 3, 22);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmed(1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAcceStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAcceStep(2, 0, 0, -0.004f);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _pMorpher->beat(3, 20, 13, 2);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_9)) {
//        _pMorpher->stopImmed(3);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _pMorpher->beat(4, 60, 3, 20);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pMorpher->stopImmed(4);
//    }
//    _pMorpher->behave();

//    if (GgafDxInput::isBeingPressedKey(DIK_1)) {
//        _pMorpher->intoTargetLinerUntil(1, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 1.0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_9)) {
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _pMorpher->intoTargetLinerUntil(1, 0, 30);
//        _pMorpher->intoTargetLinerUntil(2, 0, 30);
//        _pMorpher->intoTargetLinerUntil(3, 0, 30);
//        _pMorpher->intoTargetLinerUntil(4, 1.0, 30);
//    } else if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pMorpher->intoTargetLinerUntil(4, 0, 30);
//    }
//    _pMorpher->behave();
    /////////////モーフテスト////////////////
    if (_iMovePatternNo == 0) {
        _pKurokoA->setFaceAngVelo(AXIS_X, 0);
        _pKurokoA->setFaceAngVelo(AXIS_Z, _ang_veloTurn*1.5);
        _pKurokoA->setFaceAngVelo(AXIS_Y, _ang_veloTurn*0.5);
        _pKurokoA->setMvVelo(-3000);
        _iMovePatternNo++;
    } else if (_iMovePatternNo == 1 && _X > P_MYSHIP->_X-400000) {
        if (getBehaveingFrame() % _laser_interval == 0) {
            _pKurokoA->execTurnFaceAngSequence(P_MYSHIP,
                                                _ang_veloTurn*20, 0,
                                                TURN_COUNTERCLOCKWISE, false);
            _iMovePatternNo++;
            _cnt_laserchip = 0;
        } else {
        }
    } else if (_iMovePatternNo == 2) {
        if (!_pKurokoA->isTurningFaceAng()) {
            //自機にがいた方向に振り向きが完了時
            _iMovePatternNo++;
        }
    } else if (_iMovePatternNo == 3) {
        _pKurokoA->setFaceAngVelo(AXIS_X, _ang_veloTurn*40);
        _pKurokoA->setFaceAngVelo(AXIS_Z, 0);
        _pKurokoA->setFaceAngVelo(AXIS_Y, 0);
        _pKurokoA->setMvVelo(0);
        if (_cnt_laserchip < _laser_length) {
            _cnt_laserchip++;

            LaserChip* pLaserChip;
            D3DXMATRIX matWorldRot;
            GgafDxUtil::setWorldMatrix_RxRzRy(this, matWorldRot);
            angle Rz, Ry;
            int vX, vY, vZ;
            for (int i = 0; i < _laser_way; i++) {
                for (int j = 0; j < _laser_way; j++) {
                    if (_papapLaserChipDepo[i][j] == NULL) {
                        GgafMainActor* p = _pDepoCon_DpEnemyMassaliaLaserChip->use()->dispatch();
                        if (p == NULL) {
                            //レーザーセットは借入出来ない
                            continue;
                        } else {
                            _papapLaserChipDepo[i][j] = (LaserChipDepository*)p;
                            _papapLaserChipDepo[i][j]->config(_laser_length, 1);
                        }
                    }

                    pLaserChip = _papapLaserChipDepo[i][j]->dispatch();
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
                        vX = _papaPosLaser[i][j].X*matWorldRot._11 + _papaPosLaser[i][j].Y*matWorldRot._21 + _papaPosLaser[i][j].Z*matWorldRot._31;
                        vY = _papaPosLaser[i][j].X*matWorldRot._12 + _papaPosLaser[i][j].Y*matWorldRot._22 + _papaPosLaser[i][j].Z*matWorldRot._32;
                        vZ = _papaPosLaser[i][j].X*matWorldRot._13 + _papaPosLaser[i][j].Y*matWorldRot._23 + _papaPosLaser[i][j].Z*matWorldRot._33;
                        GgafDxUtil::getRzRyAng(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得


                        pLaserChip->locate(_X+vX, _Y+vY, _Z+vZ);
                        pLaserChip->_pKurokoA->setRzRyMvAng(Rz, Ry);
                        pLaserChip->_pKurokoA->_angFace[AXIS_Z] = Rz;
                        pLaserChip->_pKurokoA->_angFace[AXIS_Y] = Ry;
                        pLaserChip->activate();
                        //pLaserChip->_pKurokoA->behave();

                        if (i == 0 && j == 0 && pLaserChip->_pChip_front == NULL) {
                            _pSeTransmitter->play3D(0); //発射音
                            changeEffectTechniqueInterim("Flush", 5); //フラッシュ
                        }
                    }
                }
            }
        } else {
//            for (int i = 0; i < _laser_way; i++) {
//                for (int j = 0; j < _laser_way; j++) {
//                    _papapLaserChipDepo[i][j] = NULL;
//                }
//            }
            _iMovePatternNo = 0;
        }
    }

    _pSeTransmitter->behave();
    _pKurokoA->behave();
}

void EnemyMassalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(1);
        sayonara();
        //消滅エフェクト
    } else {

    }

}


void EnemyMassalia::onInactive() {
    //レーザーデポジトリは遅れてから戻す
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            if (_papapLaserChipDepo[i][j]) {
                _papapLaserChipDepo[i][j]->sayonara(60*10);
            }
        }
    }
    sayonara();
}


EnemyMassalia::~EnemyMassalia() {
    _pCon_RefractionEffectDepository->close();
    _pDepoCon_DpEnemyMassaliaLaserChip->close();
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDepo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser);
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDepo);


}
