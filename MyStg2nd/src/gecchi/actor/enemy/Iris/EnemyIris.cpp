#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyIris::EnemyIris(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "Iris") {
    _class_name = "EnemyIris";
    _iMovePatternNo = 0;
    _pProgram_IrisMove = NULL;
}

void EnemyIris::initialize() {
    setBumpable(true);
    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
    _pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;
    _pMover->setFaceAngleVelocity(AXIS_X, 4000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pStgChecker->setStatus(100, 99999, 99999, 99999);
    useSe1("yume_shototsu");
    onActive();
}

void EnemyIris::onActive() {
    if (_pProgram_IrisMove) {
        _pMover->executeSplineMoveProgram(_pProgram_IrisMove, 0); //スプライン移動をプログラムしておく
    }
    _iMovePatternNo = 0;
}

void EnemyIris::processBehavior() {
    //スプライン移動中
    if (_iMovePatternNo == 0 && !(_pProgram_IrisMove->isExecuting())) {
        _iMovePatternNo++;
    }
    //スプライン移動終了
    if (_iMovePatternNo == 1) {
        _pMover->executeTagettingMoveAngleSequence(pMYSHIP->_X+800000, _Y, pMYSHIP->_Z, 2000, TURN_CLOSE_TO);
        _iMovePatternNo++;
    }
    //自機とZ軸が接近
    if (_iMovePatternNo == 2) {
        if (_Z-20000 < pMYSHIP->_Z && pMYSHIP->_Z < _Z+20000) {
            _pMover->executeTagettingMoveAngleSequence(MyShip::_lim_behaind - 500000 , _Y, _Z, 2000, TURN_CLOSE_TO);
            _pMover->setMoveVeloAcceleration(100);
            _iMovePatternNo++;
        }
    }
    _pMover->behave();

}

void EnemyIris::processJudgement() {
//    if (isOutOfGameSpace()) {
//        adios();
//    }
}

void EnemyIris::processOnHit(GgafActor* prm_pActor_Opponent) {
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe1();
    if (pExplo001 != NULL) {
        pExplo001->setGeometry(this);
        pExplo001->activate();
    }
    adios();
}

EnemyIris::~EnemyIris() {
    DELETE_POSSIBLE_NULL(_pProgram_IrisMove);
}
