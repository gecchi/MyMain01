#include "stdafx.h"

Laser001Actor::Laser001Actor(string prm_name, string prm_xname) : DefaultSpriteActor(prm_name, prm_xname) {

}

void Laser001Actor::initialize() {
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

void Laser001Actor::shotBegin() {
	_X = GameGlobal::_pMyShipActor->_X;
	_Y = GameGlobal::_pMyShipActor->_Y;
	_Z = GameGlobal::_pMyShipActor->_Z;
	setBumpable(true);
	declarePlay();
}

void Laser001Actor::shotFinish() {
	setBumpable(false);
	declareStop();
	declareMoveFirst();
}

void Laser001Actor::processBehavior() {
	addAnimationFrame();

	//���W�ɔ��f
	_pMover -> behave();

}

void Laser001Actor::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		shotFinish();
	}
}

/*
bool Laser001Actor::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("Laser001Actor::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"��"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void Laser001Actor::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("Laser001Actor::processOnHit �V���b�g���q�b�g���܂���");
	_TRACE_("Laser001Actor�q�b�g���܂����B("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	shotFinish();
}



Laser001Actor::~Laser001Actor() {
}
