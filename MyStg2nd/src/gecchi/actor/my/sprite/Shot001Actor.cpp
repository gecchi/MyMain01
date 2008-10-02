#include "stdafx.h"

Shot001Actor::Shot001Actor(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {

}

void Shot001Actor::initialize() {
	_iAnimationMethod = OSCILLATE_LOOP;
	_iAnimationFrame_Interval = 2;

	_pMover -> setXYMoveAngleVelocity(0);
	_pMover -> setAxisRotAngleVelocity(AXIS_Z, 10*1000);
	_pMover -> setXYMoveAngle(0);
	_pMover -> setAxisRotAngle(AXIS_Z, 0);
	_pMover -> setXYMoveVelocity(1000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 6);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);

	_pChecker -> _pHitArea2D -> setLine(0, -20000, 20000, 20000, 20000, true);
	_pChecker -> _pHitArea2D -> setLine(1, 20000, 20000, 20000, -20000, true);
	_pChecker -> _pHitArea2D -> setLine(2, 20000, -20000, -20000, -20000, true);
	_pChecker -> _pHitArea2D -> setLine(3, -20000, -20000, -20000, 20000, true);
	_pChecker -> _pHitArea2D -> setLine(4, 30000, 30000, -30000, -30000, true);
	_pChecker -> _pHitArea2D -> setLine(5, -30000, 30000, 30000, -30000, true);
//
	setBumpable(false);
	declareStop();

}


//オーバーライド
void EnemyShot001Actor::happen(int prm_event) {
	switch (prm_event) {

	case EVENT_PLAY_BEGIN:
		//出現時共通処理
		setBumpable(true);
		_X = GameGlobal::_pMyShipActor->_X;
		_Y = GameGlobal::_pMyShipActor->_Y;
		_Z = GameGlobal::_pMyShipActor->_Z;
		break;

	case EVENT_STOP_BEGIN:
		//消失時共通処理
		setBumpable(false);
		declareMoveFirst();
		break;

	default:
		break;
	}
}

void Shot001Actor::processBehavior() {
	addAnimationFrame();

	//座標に反映
	_pMover -> behave();

}

void Shot001Actor::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		playFinish();
	}
}

/*
bool Shot001Actor::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("Shot001Actor::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void Shot001Actor::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("Shot001Actor::processOnHit ショットがヒットしました");
	_TRACE_("Shot001Actorヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	playFinish();
}



Shot001Actor::~Shot001Actor() {
}
