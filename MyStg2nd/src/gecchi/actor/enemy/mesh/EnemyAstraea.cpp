#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/ceres") {
    //レーザーストック
    _pLaserChipDispatcher = NEW LaserChipDispatcher("RotLaser");
    EnemyLaserChip001* pChip;
    for (int i = 0; i < 8; i++) {
        Sleep(2);
        pChip = NEW EnemyLaserChip001("L");
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addLaserChip(pChip);
    }
    addSubLast(_pLaserChipDispatcher); //仮所属

    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 3;
    _shot_interval = 120;
    _angveloTurn = 1000;
}

void EnemyAstraea::initialize() {
    setBumpable(true);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pChecker->setStatus(100, 1, 1, 1);
    _pGeoMover->setMoveVelocity(0);
    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;

    getLordActor()->accept(KIND_MY_SHOT_PA, _pLaserChipDispatcher); //本所属
}

void EnemyAstraea::processBehavior() {
    _X = _X - 100;
    if (_lifeframe % _shot_interval == 0) {

        _pGeoMover->setAutoTargetRzRyMoveAngle(GameGlobal::_pMyShip);
        _pGeoMover->setRzMoveAngleVelocity(
                        _angveloTurn*sgn(_pGeoMover->getDifferenceFromRzMoveAngleTo(_pGeoMover->_angAutoTargetRzMove,TURN_CLOSE_TO))
                    );
        _pGeoMover->setRyMoveAngleVelocity(
                        _angveloTurn*sgn(_pGeoMover->getDifferenceFromRyMoveAngleTo(_pGeoMover->_angAutoTargetRyMove,TURN_CLOSE_TO))
                    );
        _cnt_laserchip = 0;
    }


    _pGeoMover->behave();

    if (_pGeoMover->_angveloRzMove == 0 && _pGeoMover->_angveloRyMove == 0 && _cnt_laserchip < _laser_length) {
        static EnemyLaserChip001* pLaserChip;
        pLaserChip = (EnemyLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaserChip != NULL) {
            pLaserChip->_pGeoMover->setRzRyMoveAngle(_pGeoMover->_angRzMove, _pGeoMover->_angRyMove);
            pLaserChip->_pGeoMover->_angRot[AXIS_Z] = _RZ;
            pLaserChip->_pGeoMover->_angRot[AXIS_Y] = _RY;
            pLaserChip->_pGeoMover->behave();
            pLaserChip->setGeometry(this);
            _cnt_laserchip++;
        }
    }

}

void EnemyAstraea::processJudgement() {
    if (isOffScreen()) {
        adios();
        if (_pLaserChipDispatcher) { //弾解放予約
            _pLaserChipDispatcher->adios(60 * 5);
        }
    }
}

void EnemyAstraea::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9UntransformedActor* pActor_Opponent = (GgafDx9UntransformedActor*)prm_pActor_Opponent;
    setBumpable(false);

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pChecker->_iScorePoint;
    }

    adios();
    if (_pLaserChipDispatcher) { //弾解放予約
        _pLaserChipDispatcher->adios(60 * 5);
    }

    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

bool EnemyAstraea::isOffScreen() {
    if (_X < _X_OffScreenLeft - 800000) {
        return true;
    } else {
        return false;
    }
}

EnemyAstraea::~EnemyAstraea() {
}
