#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/ebi2") {
    //レーザーストック
    _pLaserChipRotation = NEW LaserChipRotationActor("RotLaser");
    EnemyLaserChip001* pChip;
    for (int i = 0; i < 5; i++) {
        Sleep(2);
        pChip = NEW EnemyLaserChip001("L");
        pChip->inactivateImmediately();
        _pLaserChipRotation->addLaserChip(pChip);
    }
    addSubLast(_pLaserChipRotation); //仮所属

    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 4;
    _shot_interval = 120;
    _angveloTurn = 3000;
}

void EnemyAstraea::initialize() {
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pChecker->setStatus(100, 1, 1, 1);
    _pGeoMover->setMoveVelocity(0);
    _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
    _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;

    getLordActor()->accept(KIND_MY_SHOT_PA, _pLaserChipRotation); //本所属
}

void EnemyAstraea::processBehavior() {
    _X = _X - 100;
    if (_lifeframe % _shot_interval == 0) {

        _pGeoMover->setAutoTargetMoveAngle(GameGlobal::_pMyShip);
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
        EnemyLaserChip001* pLaser = (EnemyLaserChip001*)_pLaserChipRotation->obtain();
        if (pLaser != NULL) {
            pLaser->setGeometry(this);
            pLaser->_pGeoMover->setRzRyMoveAngle(_pGeoMover->_angRzMove, _pGeoMover->_angRyMove);
            _cnt_laserchip++;
        }
    }

}

void EnemyAstraea::processJudgement() {
    if (isOffScreen()) {
        arigatou_sayounara();
        if (_pLaserChipRotation) { //弾解放予約
            _pLaserChipRotation->arigatou_sayounara(60 * 5);
        }
    }
}

void EnemyAstraea::processOnHit(GgafActor* prm_pActor_Opponent) {
    GgafDx9UntransformedActor* pActor_Opponent = (GgafDx9UntransformedActor*)prm_pActor_Opponent;
    setBumpable(false);

    if (pActor_Opponent->getHeadActor()->_kind & KIND_MY) {
        GameGlobal::_dwScore += _pChecker->_iScorePoint;
    }

    arigatou_sayounara();
    if (_pLaserChipRotation) { //弾解放予約
        _pLaserChipRotation->arigatou_sayounara(60 * 5);
    }

    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
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
