#include "stdafx.h"

MyShot001::MyShot001(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {

}

void MyShot001::initialize() {
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


void MyShot001::processBehavior() {
	if (switchedToPlay()) {
		//出現時共通処理
		setBumpable(true);
		_X = GameGlobal::_pMyShip->_X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
	} else {
		//通常処理
		nextAnimationFrame();
		//座標に反映
		_pMover -> behave();
	}
}

void MyShot001::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		declareStop();
	}

	if (switchedToStop()) {
		//消失時共通処理
		setBumpable(false);
		declareMoveFirst();
	}

}

/*
bool MyShot001::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyShot001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyShot001::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("MyShot001::processOnHit ショットがヒットしました");
	_TRACE_("MyShot001ヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	declareStop();
}



MyShot001::~MyShot001() {
}
