#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMorphMeshActor(prm_name, "4/8box") {
    //レーザーストック
    _laser_way = 4;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 12;
    _shot_interval = 120;
    _angveloTurn = 1000;


    _papapLaserChipDispatcher = NEW LaserChipDispatcher**[_laser_way];
    for (int i = 0; i < _laser_way; i++) {
        _papapLaserChipDispatcher[i] = NEW LaserChipDispatcher*[_laser_way];
    }
    _paWayRz = NEW angle[_laser_way];
    _paWayRy = NEW angle[_laser_way];
    EnemyLaserChip001* pChip;

    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            _papapLaserChipDispatcher[i][j] = NEW LaserChipDispatcher("RotLaser");
            for (int k = 0; k < _laser_length*2; k++) { //_laser_length の２倍分ストック
                Sleep(1);
                pChip = NEW EnemyLaserChip001("ELC001");
                pChip->inactivateImmediately();
                _papapLaserChipDispatcher[i][j]->addLaserChip(pChip);
            }
            addSubLast(_papapLaserChipDispatcher[i][j]); //仮所属
        }
    }



}

void EnemyAstraea::initialize() {
    setBumpable(true);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 1, 1, 1);
    _pMover->setMoveVelocity(0);
    _pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;
    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            getLordActor()->accept(KIND_ENEMY_SHOT_NOMAL, _papapLaserChipDispatcher[i][j]->extract()); //本所属
        }
    }
}

void EnemyAstraea::processBehavior() {
    /////////////モーフテスト(DefaultMorphMeshActor継承要)////////////////
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pMorpher->loopTriangleWave(1, 30, 3, 22);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pMorpher->stopImmediately(1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pMorpher->intoTargetAccelerationStep(2, 1.0f, 0, 0.002f);
//    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
//        _pMorpher->intoTargetAccelerationStep(2, 0, 0, -0.004f);
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
    /////////////モーフテスト////////////////


    _X = _X - 100;
    if (_lifeframe % _shot_interval == 0) {

        _pMover->setSuspendTarget_RzRyMoveAngle(GameGlobal::_pMyShip);
        _pMover->setRzMoveAngleVelocity(
                        _angveloTurn*sgn(_pMover->getRzMoveAngleDistance(_pMover->_angTargetRzMove,TURN_CLOSE_TO))
                    );
        _pMover->setRyMoveAngleVelocity(
                        _angveloTurn*sgn(_pMover->getRyMoveAngleDistance(_pMover->_angTargetRyMove,TURN_CLOSE_TO))
                    );
        _cnt_laserchip = 0;
    }


    _pMover->behave();

    if (_pMover->_angveloRzMove == 0 && _pMover->_angveloRyMove == 0 && _cnt_laserchip < _laser_length) {
        static EnemyLaserChip001* pLaserChip;

        angle angClearance = 20000;

        GgafDx9Util::getWayAngle2D(_RY, _laser_way, angClearance, _paWayRy);
        GgafDx9Util::getWayAngle2D(_RZ, _laser_way, angClearance, _paWayRz);

        for (int i = 0; i < _laser_way; i++) {
            for (int j = 0; j < _laser_way; j++) {
                pLaserChip = (EnemyLaserChip001*)_papapLaserChipDispatcher[i][j]->employ();
                if (pLaserChip != NULL) {
                    pLaserChip->setGeometry(this);
                    pLaserChip->_pMover->setRzRyMoveAngle(_paWayRz[i], _paWayRy[j]);
                    pLaserChip->_pMover->_angFace[AXIS_Z] = _paWayRz[i];
                    pLaserChip->_pMover->_angFace[AXIS_Y] = _paWayRy[j];
                    //とりあえずまっすぐ飛ばす、しかし、ターゲットは保存したいのでここで角速度０でたーげっと。
                    pLaserChip->_pMover->executeTagettingMoveAngleSequence(GameGlobal::_pMyShip,
                                                               0, TURN_CLOSE_TO);

                    pLaserChip->_pMover->behave();

                }
            }
        }
        _cnt_laserchip++;
    }

}

void EnemyAstraea::processJudgement() {
    if (wasGone()) {
        adios();
        for (int i = 0; i < _laser_way; i++) {
            for (int j = 0; j < _laser_way; j++) {
                if (_papapLaserChipDispatcher[i][j]) { //弾解放予約
                    _papapLaserChipDispatcher[i][j]->adios(60 * 5);
                }
            }
        }
    }
}

void EnemyAstraea::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9GeometricActor* pActor_Opponent = (GgafDx9GeometricActor*)prm_pActor_Opponent;
    setBumpable(false);

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pStgChecker->_iScorePoint;
    }
    _TRACE_(" EnemyAstraea::EnemyAstraea::processOnHit()  "<<getName()<<" "<<_lifeframe);
    adios();
    for (int i = 0; i < _laser_way; i++) {
        for (int j = 0; j < _laser_way; j++) {
            if (_papapLaserChipDispatcher[i][j]) { //弾解放予約
                _papapLaserChipDispatcher[i][j]->adios(60 * 5);
            }
        }
    }
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

int EnemyAstraea::wasGone() {
    if (_X < _X_ScreenLeft - 800000) {
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
