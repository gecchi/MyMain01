#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyIris::EnemyIris(const char* prm_name) : DefaultMeshActor(prm_name, "Iris") {
    _class_name = "EnemyIris";
    _iMovePatternNo = 0;
    _pProgram_IrisMove = NULL;
}

void EnemyIris::initialize() {
    setBumpable(true);
    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
    _pMover->_synchronize_RyFaceAngle_to_RyMoveAngle_flg = true;
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
}

void EnemyIris::processBehavior() {

    //座標に反映
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
