#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCirce::EnemyCirce(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCirce)) { //8/をいれとかないとユニークにならない
    _class_name = "EnemyCirce";
    iMovePatternNo_ = 0;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyCirce::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
}

void EnemyCirce::initialize() {
    setHitAble(true);
    _pScaler->setScale(1000);
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setMvVelo(3000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _X = PX_C(200);
}

void EnemyCirce::onActive() {
    _pStatus->reset();
    iMovePatternNo_ = 0;
}

void EnemyCirce::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->turnMvAngTwd(P_MYSHIP,
                            50, 0, TURN_CLOSE_TO, true);
    _pKurokoA->behave();
    _pScaler->behave();
    //_pSeTx->behave();
}


void EnemyCirce::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyCirce::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyCirce::onInactive() {
    sayonara();
}

EnemyCirce::~EnemyCirce() {
}
