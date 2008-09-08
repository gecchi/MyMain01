#include "stdafx.h"

EnemyShot001Actor::EnemyShot001Actor(string prm_name, string prm_xname) : EnemyShotSpriteActor(prm_name, prm_xname) {
	declareStop();
}

void EnemyShot001Actor::initialize() {
	_iAnimationMethod = ORDER_LOOP;
	_iAnimationFrame_Interval = 1;
	_X = 0;
	_Y = 0;
	_Z = 0;
	_pMover -> setXYMoveAngle(GameGlobal::_pMyShipActor->_X, GameGlobal::_pMyShipActor->_Y);
	_pMover -> setXYMoveVelocity(1000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);

	setBumpable(true);
}


void EnemyShot001Actor::processBehavior() {
	addAnimationFrame();

	//座標に反映
	_pMover -> behave();

}

void EnemyShot001Actor::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		finish();
	}
}



void EnemyShot001Actor::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("EnemyShot001Actor::processOnHit ショットがヒットしました");
	_TRACE_("EnemyShot001Actorヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();

	//体力計算
	if (_pChecker->_iStaminaPoint < 0) {
		declareStop();
	}


}

EnemyShot001Actor::~EnemyShot001Actor() {
}
