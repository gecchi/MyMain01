#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshActor(prm_name, "Astraea") {
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);

    //���[�U�[�X�g�b�N
    _laser_way = 3;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 30;
    _shot_interval = 480;
    _angveloTurn = 200;

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
}


void EnemyAstraea::onActive() {
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);
    _pMover->setMvVelo(-5000);
    _frame_shot_after = 1000;
    _iMovePatternNo = 0;
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight;
}

void EnemyAstraea::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    /////////////���[�t�e�X�g(DefaultMorphMeshActor�p���v)////////////////
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
    /////////////���[�t�e�X�g////////////////
    if (_iMovePatternNo == 0) {
        _pMover->setFaceAngVelo(AXIS_X, _angveloTurn);
        _pMover->setFaceAngVelo(AXIS_Z, _angveloTurn*1.5);
        _pMover->setFaceAngVelo(AXIS_Y, _angveloTurn*0.5);
        _pMover->setMvVelo(-3000);
        _iMovePatternNo = 1;
    }
    if (_iMovePatternNo == 1 ) {
        if (getBehaveingFrame() % _shot_interval == 0 && _X > pMYSHIP->_X-400000) {
            _pMover->execTagettingFaceAngSequence(GameGlobal::_pMyShip,
                                                _angveloTurn*20, 0,
                                                TURN_COUNTERCLOCKWISE, false);
            _iMovePatternNo = 2;
            _cnt_laserchip = 0;
        }
    }
    if (_iMovePatternNo == 2) {
        if (!_pMover->isTagettingFaceAng()) {
            _iMovePatternNo = 3;
            _frame_shot_after = 0;
        }
    }

    if (_iMovePatternNo == 3) {
        _pMover->setFaceAngVelo(AXIS_X, _angveloTurn*40);
        _pMover->setFaceAngVelo(AXIS_Z, 0);
        _pMover->setFaceAngVelo(AXIS_Y, 0);
        _pMover->setMvVelo(0);
        if (_cnt_laserchip < _laser_length) {
            _cnt_laserchip++;

            static EnemyAstraeaLaserChip001* pLaserChip;

            angle angClearance = 10000;//�J���
            GgafDx9Util::getWayAngle2D(_pMover->_angFace[AXIS_Z], _laser_way, angClearance, _paWayRz);
            GgafDx9Util::getWayAngle2D(_pMover->_angFace[AXIS_Y], _laser_way, angClearance, _paWayRy);


            for (int i = 0; i < _laser_way; i++) {

                for (int j = 0; j < _laser_way; j++) {


                    if (_papapLaserChipDispatcher[i][j] == NULL) {
                        GgafMainActor* p = pCOMMONSCENE->_pDispatcher_LaserChipDispatcher->employ();
                        if (p == NULL) {
                            //���[�U�[�Z�b�g�͎ؓ��o���Ȃ�
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
                            _pSeReflector->play3D(0); //���ˉ�
                            chengeEffectTechniqueInterim("Flush", 5); //�t���b�V��
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
    chengeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        _pSeReflector->play3D(1);
        sayonara();
        //���ŃG�t�F�N�g
    } else {

    }
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
}


void EnemyAstraea::onInactive() {
//    //���[�U�[�͒x��Ă���f�B�X�p�b�`���[�ɖ߂�
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
