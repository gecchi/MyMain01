#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyCirce::EnemyCirce(const char* prm_name) : DefaultMeshActor(prm_name, "ebi") { //8/をいれとかないとユニークにならない
    _class_name = "EnemyCirce";
    MyStgUtil::resetEnemyCirceStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
}

void EnemyCirce::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void EnemyCirce::initialize() {
    setHitAble(true);
    _pScaler->setScale(100);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setMvVelo(300);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -10000, -10000, -10000, 10000, 10000, 10000);
}

void EnemyCirce::onActive() {
    MyStgUtil::resetEnemyCirceStatus(_pStatus);
    _iMovePatternNo = 0;
}

void EnemyCirce::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pMover->execTagettingMvAngSequence(P_MYSHIP, 50, 0, TURN_CLOSE_TO);
    _pMover->behave();
    _pScaler->behave();
    //_pSeTransmitter->behave();
}


void EnemyCirce::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyCirce::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)P_COMMON_SCENE->_pDispatcher_EffectExplosion001->employ();
    _pSeTransmitter->play3D(0);
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setCoordinateBy(this);
    }

//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        sayonara();
//    }
}

void EnemyCirce::onInactive() {
    sayonara();
}

EnemyCirce::~EnemyCirce() {
}
