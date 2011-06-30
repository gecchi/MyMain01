#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyMassalia::EnemyMassalia(const char* prm_name) : DefaultMeshActor(prm_name, "Massalia") {
    //MyStgUtil::resetEnemyMassaliaStatus(_pStatus);

    //���[�U�[
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 30;
    _laser_interval = 600;
    _ang_veloTurn = 100;
    _angClearance = 40000;//�J���
    _papapLaserChipStore = NEW LaserChipStore**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipStore[i] = NEW LaserChipStore*[_laser_way];
    }


    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipStore[i][j] = NULL;
        }
    }

    _pCon_RefractionEffectStore =
            (StoreConnection*)(P_GOD->_pStoreManager->getConnection("StCon_EffRefraction001"));

    _pStoreCon_DpEnemyMassaliaLaserChip =
            (StoreConnection*)(P_GOD->_pStoreManager->getConnection(
                                                                   "StCon_DpEnemyMassaliaLaserChip001",
                                                                   //"StCon_DpEnemyMassaliaLaserChip002",
                                                                   _pCon_RefractionEffectStore->refer()
                                                                )
                                   );


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
            GgafDx9Util::getNormalizeVectorZY(Rz, Ry,
                                              vx, vy, vz);
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
    _iMovePatternNo = 0;



}

void EnemyMassalia::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.97, 0.5, 12.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(1.0);
    _pGgafDx9Model->_pTextureBlinker->beat(60*6, 60*2, 60*2, -1);
}

void EnemyMassalia::initialize() {
    setHitAble(true);
    setAlpha(0.99);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 200*1000);
    _pKurokoA->setMvVelo(-1000);
    _iMovePatternNo = 0;
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight;
}


void EnemyMassalia::onActive() {
    //�X�e�[�^�X���Z�b�g
    //MyStgUtil::resetEnemyMassaliaStatus(_pStatus);
    _pKurokoA->setMvVelo(-5000);
    _iMovePatternNo = 0;
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight;

    if (_pEffect_Appearance) {
        _pEffect_Appearance->activate();
    }
}

void EnemyMassalia::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    /////////////���[�t�e�X�g(DefaultMorphMeshActor�p���v)////////////////
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
    /////////////���[�t�e�X�g////////////////
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
            //���@�ɂ����������ɐU�������������
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
            GgafDx9Util::setWorldMatrix_RxRzRy(this, matWorldRot);
            angle Rz, Ry;
            int vX, vY, vZ;
            for (int i = 0; i < _laser_way; i++) {
                for (int j = 0; j < _laser_way; j++) {
                    if (_papapLaserChipStore[i][j] == NULL) {
                        GgafMainActor* p = _pStoreCon_DpEnemyMassaliaLaserChip->refer()->dispatch();
                        if (p == NULL) {
                            //���[�U�[�Z�b�g�͎ؓ��o���Ȃ�
                            continue;
                        } else {
                            _papapLaserChipStore[i][j] = (LaserChipStore*)p;
                            _papapLaserChipStore[i][j]->config(_laser_length, 1);
                        }
                    }

                    pLaserChip = _papapLaserChipStore[i][j]->dispatch();
                    if (pLaserChip) {
                        //���[�U�[�̌������v�Z
                        //���[�J���ł̃V���b�g�̕����x�N�g����(_Xorg,_Yorg,_Zorg)�A
                        //���[���h�ϊ��s��̉�]�����imatWorldRot)�̐����� mat_xx�A
                        //�ŏI�I�ȕ����x�N�g����(vX, vY, vZ) �Ƃ����
                        //
                        //                       | mat_11 mat_12 mat_13 |
                        // | _Xorg _Yorg _Zorg | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                        //                       | mat_31 mat_32 mat_33 |
                        //�����
                        // vX = _Xorg*mat_11 + _Yorg*mat_21 + _Zorg*mat_31
                        // vY = _Xorg*mat_12 + _Yorg*mat_22 + _Zorg*mat_32
                        // vZ = _Xorg*mat_13 + _Yorg*mat_23 + _Zorg*mat_33
                        //�ƂȂ�
                        vX = _papaPosLaser[i][j].X*matWorldRot._11 + _papaPosLaser[i][j].Y*matWorldRot._21 + _papaPosLaser[i][j].Z*matWorldRot._31;
                        vY = _papaPosLaser[i][j].X*matWorldRot._12 + _papaPosLaser[i][j].Y*matWorldRot._22 + _papaPosLaser[i][j].Z*matWorldRot._32;
                        vZ = _papaPosLaser[i][j].X*matWorldRot._13 + _papaPosLaser[i][j].Y*matWorldRot._23 + _papaPosLaser[i][j].Z*matWorldRot._33;
                        GgafDx9Util::getRzRyAng(vX, vY, vZ, Rz, Ry); //���݂̍ŏI�I�Ȍ������ARzRy�Ŏ擾


                        pLaserChip->locate(_X+vX, _Y+vY, _Z+vZ);
                        pLaserChip->_pKurokoA->setRzRyMvAng(Rz, Ry);
                        pLaserChip->_pKurokoA->_angFace[AXIS_Z] = Rz;
                        pLaserChip->_pKurokoA->_angFace[AXIS_Y] = Ry;
                        pLaserChip->activate();
                        //pLaserChip->_pKurokoA->behave();

                        if (i == 0 && j == 0 && pLaserChip->_pChip_front == NULL) {
                            _pSeTransmitter->play3D(0); //���ˉ�
                            changeEffectTechniqueInterim("Flush", 5); //�t���b�V��
                        }
                    }
                }
            }
        } else {
//            for (int i = 0; i < _laser_way; i++) {
//                for (int j = 0; j < _laser_way; j++) {
//                    _papapLaserChipStore[i][j] = NULL;
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
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
        }
        _pSeTransmitter->play3D(1);
        sayonara();
        //���ŃG�t�F�N�g
    } else {

    }

}


void EnemyMassalia::onInactive() {
    //���[�U�[�X�g�A�[�͒x��Ă���߂�
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            if (_papapLaserChipStore[i][j]) {
                _papapLaserChipStore[i][j]->sayonara(60*10);
            }
        }
    }
    sayonara();
}


EnemyMassalia::~EnemyMassalia() {
    _pCon_RefractionEffectStore->close();
    _pStoreCon_DpEnemyMassaliaLaserChip->close();
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipStore[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaPosLaser);
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipStore);


}