#include "stdafx.h"

EnemyShotSpriteActor::EnemyShotSpriteActor(string prm_name, string prm_xname) : DefaultSpriteEnemyActor(prm_name, prm_xname) {
	_pEffectBegin = NULL;
	_pEffectFinish = NULL;
	_iProgress = 0;
}

void EnemyShotSpriteActor::initialize() {
	setAnimationMethod(ORDER_LOOP, 1);
//	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
//	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	setBumpable(false);
}

void EnemyShotSpriteActor::processBehavior() {
	//標準処理（たぶんオーバーライドされるだろうけども)
	nextAnimationFrame();
	_pMover -> behave();
}

void EnemyShotSpriteActor::processJudgement() {
	if (isOffScreen()) {
		declareStop();
	}

}

void EnemyShotSpriteActor::processOnHit(GgafActor* prm_pActor_Opponent) {
	_TRACE_("EnemyShotSpriteActorヒットしました。("<<_X<<","<<_Y<<")");
	declareStop();
}



EnemyShotSpriteActor::~EnemyShotSpriteActor() {
}
