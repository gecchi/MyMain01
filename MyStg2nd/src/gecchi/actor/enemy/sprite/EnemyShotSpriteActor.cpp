#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyShotSpriteActor::EnemyShotSpriteActor(const char* prm_name, const char* prm_model) : DefaultSpriteEnemyActor(prm_name, prm_model) {
    _class_name = "EnemyShotSpriteActor";
    _pEffectBegin = NULL;
    _pEffectFinish = NULL;
    _iProgress = 0;
}

void EnemyShotSpriteActor::initialize() {
    _pUvFlipper->setUvFlipMethod(FLIP_ORDER_LOOP, 1);
    setHitAble(true);
}

void EnemyShotSpriteActor::processBehavior() {
    //標準処理（たぶんオーバーライドされるだろうけども)
    _pUvFlipper->behave();
    _pMover->behave();
}

void EnemyShotSpriteActor::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivateTree();
    }

}

void EnemyShotSpriteActor::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyShotSpriteActorヒットしました。("<<_X<<","<<_Y<<")");
    inactivateTree();
}

EnemyShotSpriteActor::~EnemyShotSpriteActor() {
}
