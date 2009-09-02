#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshSetActor(prm_name, "ceres") {
    //レーザーストック
    _laser_way = 4;
    _X = 0;
    _Y = 0;
    _Z = 0;
    _laser_length = 10;
    _shot_interval = 120;
    _angveloTurn = 1000;


    _papLaserChipDispatcher = NEW LaserChipDispatcher*[_laser_way];
    _paWay = NEW angle[_laser_way];

    EnemyLaserChip001* pChip;

    for (int i = 0; i < _laser_way; i++) {
        _papLaserChipDispatcher[i] = NEW LaserChipDispatcher("RotLaser");
        for (int j = 0; j < _laser_length*2; j++) {
            Sleep(2);
            pChip = NEW EnemyLaserChip001("ELC001");
            pChip->inactivateImmediately();
            _papLaserChipDispatcher[i]->addLaserChip(pChip);
        }
        addSubLast(_papLaserChipDispatcher[i]); //仮所属
    }



}

void EnemyAstraea::initialize() {
    setBumpable(true);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 1, 1, 1);
    _pMover->setMoveVelocity(0);
    _pMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
    _pMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;
    for (int i = 0; i < _laser_way; i++) {
        getLordActor()->accept(KIND_ENEMY_SHOT_PA, _papLaserChipDispatcher[i]->extract()); //本所属
    }
}

void EnemyAstraea::processBehavior() {
    _X = _X - 100;
    if (_lifeframe % _shot_interval == 0) {

        _pMover->setTargetRzRyMoveAngle(GameGlobal::_pMyShip);
        _pMover->setRzMoveAngleVelocity(
                        _angveloTurn*sgn(_pMover->getDifferenceFromRzMoveAngleTo(_pMover->_angTargetRzMove,TURN_CLOSE_TO))
                    );
        _pMover->setRyMoveAngleVelocity(
                        _angveloTurn*sgn(_pMover->getDifferenceFromRyMoveAngleTo(_pMover->_angTargetRyMove,TURN_CLOSE_TO))
                    );
        _cnt_laserchip = 0;
    }


    _pMover->behave();

    if (_pMover->_angveloRzMove == 0 && _pMover->_angveloRyMove == 0 && _cnt_laserchip < _laser_length) {
        static EnemyLaserChip001* pLaserChip;
        GgafDx9Util::getWayAngle2D(_RY, _laser_way, 20000, _paWay);

        for (int i = 0; i < _laser_way; i++) {
            pLaserChip = (EnemyLaserChip001*)_papLaserChipDispatcher[i]->employ();
            if (pLaserChip != NULL) {
                pLaserChip->_pMover->setRzRyMoveAngle(_pMover->_angRzMove, _paWay[i]);
                pLaserChip->_pMover->_angRot[AXIS_Z] = _RZ;
                pLaserChip->_pMover->_angRot[AXIS_Y] = _paWay[i];
                pLaserChip->_pMover->behave();
                pLaserChip->setGeometry(this);
            }
        }
        _cnt_laserchip++;
    }

}

void EnemyAstraea::processJudgement() {
    if (isGone()) {
        adios();
        for (int i = 0; i < _laser_way; i++) {
            if (_papLaserChipDispatcher[i]) { //弾解放予約
                _papLaserChipDispatcher[i]->adios(60 * 5);
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
        if (_papLaserChipDispatcher[i]) { //弾解放予約
            _papLaserChipDispatcher[i]->adios(60 * 5);
        }
    }
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
}

int EnemyAstraea::isGone() {
    if (_X < _X_ScreenLeft - 800000) {
        return true;
    } else {
        return false;
    }
}

EnemyAstraea::~EnemyAstraea() {
    DELETEARR_IMPOSSIBLE_NULL(_paWay);

    DELETEARR_IMPOSSIBLE_NULL(_papLaserChipDispatcher);

}
