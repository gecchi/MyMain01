#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCirce::EnemyCirce(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCirce)) { //8/をいれとかないとユニークにならない
    _class_name = "EnemyCirce";
    iMovePatternNo_ = 0;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
}

void EnemyCirce::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyCirce::initialize() {
    setHitAble(true);
    _pScaler->setScale(1000);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setMvVelo(3000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _X = PX2CO(200);
}

void EnemyCirce::onActive() {
    _pStatus->reset();
    iMovePatternNo_ = 0;
}

void EnemyCirce::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->execTurnMvAngSequence(P_MYSHIP, 50, 0, TURN_CLOSE_TO);
    _pKurokoA->behave();
    _pScaler->behave();
    //_pSeTransmitter->behave();
}


void EnemyCirce::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyCirce::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 =
            (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
    _pSeTransmitter->play3D(0);
    if (pExplo001) {
        pExplo001->locateAs(this);
        pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
    }

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        sayonara();
    }
}

void EnemyCirce::onInactive() {
    sayonara();
}

EnemyCirce::~EnemyCirce() {
}
