#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMorphMeshActor(prm_name, "4/8box") {
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);

    //���[�U�[�X�g�b�N
    _laser_way = 2;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 20;
    _shot_interval = 120;
    _angveloTurn = 3000;

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
    prepareSe1("yume_Sbend", GgafRepeatSeq::getNext(5)); //���[�U�[����(�`�����l����0,1,2,3,4,0,1,2,3,4 �ƂȂ�)
    prepareSe2("bomb1");     //����
}

void EnemyAstraea::initialize() {
    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pMover->setMvVelo(0);
    _pMover->relateRzRyFaceAngToMvAng(true);
}


void EnemyAstraea::onActive() {
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyAstraeaStatus(_pStatus);
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

    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
        _pMorpher->intoTargetLinerUntil(1, 1.0, 30);
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
        _pMorpher->intoTargetLinerUntil(2, 1.0, 30);
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
        _pMorpher->intoTargetLinerUntil(3, 1.0, 30);
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
        _pMorpher->intoTargetLinerUntil(1, 0, 30);
        _pMorpher->intoTargetLinerUntil(2, 0, 30);
        _pMorpher->intoTargetLinerUntil(3, 0, 30);
        _pMorpher->intoTargetLinerUntil(4, 1.0, 30);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
        _pMorpher->intoTargetLinerUntil(4, 0, 30);
    }
    _pMorpher->behave();
    /////////////���[�t�e�X�g////////////////


    _X = _X - 5000;
    if (getBehaveingFrame() % _shot_interval == 0) {

        _pMover->setStopTarget_RzRyMvAng(GameGlobal::_pMyShip);
        _pMover->setRzMvAngVelo(
                        _angveloTurn*sgn(_pMover->getRzMvAngDistance(_pMover->_angTargetRzMv,TURN_CLOSE_TO))
                    );
        _pMover->setRyMvAngVelo(
                        _angveloTurn*sgn(_pMover->getRyMvAngDistance(_pMover->_angTargetRyMv,TURN_CLOSE_TO))
                    );
        _cnt_laserchip = 0;
    }


    _pMover->behave();

    if (_pMover->_angveloRzMv == 0 && _pMover->_angveloRyMv == 0 && _cnt_laserchip < _laser_length) {

        static EnemyAstraeaLaserChip001* pLaserChip;

        angle angClearance = 150000;//�J���

        GgafDx9Util::getWayAngle2D(_RY, _laser_way, angClearance, _paWayRy);
        GgafDx9Util::getWayAngle2D(_RZ, _laser_way, angClearance, _paWayRz);

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
                } else {
                    if (i == 0 && j == 0) {
                        playSe1(); //���ˉ�
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
                }
            }
        }
        _cnt_laserchip++;
    }

}

void EnemyAstraea::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyAstraea::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    chengeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        playSe2();
        inactivate(); //����Ȃ�
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


bool EnemyAstraea::isOutOfGameSpace() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 300000) {
        return true;
    } else {
        return false;
    }
}

EnemyAstraea::~EnemyAstraea() {
    DELETEARR_IMPOSSIBLE_NULL(_paWayRz);
    DELETEARR_IMPOSSIBLE_NULL(_paWayRy);
    for (int i = 0; i < _laser_way; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapLaserChipDispatcher);


}
