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

//オーバーライド
void EnemyShotSpriteActor::happen(int prm_event) {
	switch (prm_event) {
	case EVENT_PLAY_BEGIN:
		setBumpable(true);
		break;
	case EVENT_STOP_BEGIN:
		setBumpable(false);
		break;
	default:
		break;
	}
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
	_TRACE_("EnemyShotSpriteActorヒットしました。("<<_X<<","<<_Y<<")");
	finish();
}



EnemyShotSpriteActor::~EnemyShotSpriteActor() {
}
