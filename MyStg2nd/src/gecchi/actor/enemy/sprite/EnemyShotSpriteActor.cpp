#include "stdafx.h"

EnemyShotSpriteActor::EnemyShotSpriteActor(string prm_name, string prm_model) : DefaultSpriteEnemyActor(prm_name, prm_model) {
	_pEffectBegin = NULL;
	_pEffectFinish = NULL;
	_iProgress = 0;
}

void EnemyShotSpriteActor::initialize() {
	setAnimationMethod(ORDER_LOOP, 1);
	setBumpableOnlySelf(true);
}

void EnemyShotSpriteActor::processBehavior() {
	//標準処理（たぶんオーバーライドされるだろうけども)
	nextAnimationFrame();
	_pGeoMover -> behave();
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
