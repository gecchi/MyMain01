#include "stdafx.h"

Laser001Actor* Laser001Actor::_pHeadLaser001Actor = NULL;

Laser001Actor::Laser001Actor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {
	_X_prevFrame = 0;
}

void Laser001Actor::initialize() {
	_iAnimationMethod = ORDER_LOOP;
	_iAnimationFrame_Interval = 3;

	_pMover -> setXYMoveAngleVelocity(0);
	_pMover -> setXYMoveAngle(0);
	_pMover -> setXYMoveVelocity(_pSpriteModel->_fSize_SpriteModelWidthPx * 1000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -5000, -5000, 5000, 5000);

	setBumpable(false);
}

void Laser001Actor::shotBegin() {
	_X = GameGlobal::_pMyShipActor->_X;
	_X_prevFrame = _X;
	_Y = GameGlobal::_pMyShipActor->_Y;
	_Z = GameGlobal::_pMyShipActor->_Z;
	setBumpable(true);
	declarePlay();
}

void Laser001Actor::shotFinish() {
	setBumpable(false);
	if (Laser001Actor::_pHeadLaser001Actor == this) {
		Laser001Actor::_pHeadLaser001Actor = NULL;
	}
	declareStop();
	declareMoveFirst();
}

void Laser001Actor::processBehavior() {
	addAnimationFrame();
	//座標に反映
	_pMover -> behave();

	_Y = GameGlobal::_pMyShipActor->_Y;
//	_X -= (_X_prevFrame - GameGlobal::_pMyShipActor->_X);
//	_X_prevFrame = _X;
}

void Laser001Actor::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		shotFinish();
	}
}

/*
bool Laser001Actor::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("Laser001Actor::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void Laser001Actor::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("Laser001Actor::processOnHit ショットがヒットしました");
	_TRACE_("Laser001Actorヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	shotFinish();
}



Laser001Actor::~Laser001Actor() {
}
