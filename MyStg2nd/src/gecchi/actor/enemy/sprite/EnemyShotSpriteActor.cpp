#include "stdafx.h"

EnemyShotSpriteActor::EnemyShotSpriteActor(string prm_name, string prm_xname) : DefaultSpriteEnemyActor(prm_name, prm_xname) {
	_pEffectBegin = NULL;
	_pEffectFinish = NULL;
	_iProgress = 0;
}

void EnemyShotSpriteActor::initialize() {
	_iAnimationMethod = GgafDx9SpriteActor::ORDER_LOOP;
	_iAnimationFrame_Interval = 1;

//	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
//	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	setBumpable(false);
}

void EnemyShotSpriteActor::begin() {
	setBumpable(true);
	declarePlay();
}

void EnemyShotSpriteActor::finish() {
	setBumpable(false);
	declareStop();
}

void EnemyShotSpriteActor::processBehavior() {
	if (_iProgress == 0) {
		if (_pEffectBegin != NULL) {

		}
	}

	if (_iProgress == 9) {

	}
	addAnimationFrame();
	_pMover -> behave();
}

void EnemyShotSpriteActor::processJudgement() {
	if (isOffScreen()) {
		finish();
	}
}

void EnemyShotSpriteActor::processOnHit(GgafActor* prm_pActor_Opponent) {
	_TRACE_("EnemyShotSpriteActorÉqÉbÉgÇµÇ‹ÇµÇΩÅB("<<_X<<","<<_Y<<")");
	finish();
}



EnemyShotSpriteActor::~EnemyShotSpriteActor() {
}
