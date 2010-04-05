#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyJuno::EnemyJuno(const char* prm_name) : DefaultMeshSetActor(prm_name, "Ceres") {
    _class_name = "EnemyJuno";

    _iMovePatternNo = 0;
}


void EnemyJuno::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -10000, -10000, 10000, 10000);
    _pMover->setFaceAngVelo(AXIS_X, 3000);
}

void EnemyJuno::onActive() {
    setHitAble(true);
}

void EnemyJuno::processBehavior() {
    _pMover->behave();
}

void EnemyJuno::processJudgement() {
    if (isOutOfGameSpace()) {
        setHitAble(false);
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        inactivate();
    }
}

void EnemyJuno::onInactive() {
}

void EnemyJuno::onHit(GgafActor* prm_pOtherActor) {
    setHitAble(false);
    inactivate();
}

EnemyJuno::~EnemyJuno() {
}
