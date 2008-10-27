#include "stdafx.h"

MyShot001::MyShot001(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {

}

void MyShot001::initialize() {
	setAnimationMethod(OSCILLATE_LOOP, 2);

	_pMover -> setXYMoveAngleVelocity(0);
	_pMover -> setAxisRotAngleVelocity(AXIS_Z, 1*1000);
	_pMover -> setXYMoveAngle(0);
	_pMover -> setAxisRotAngle(AXIS_Z, 0);
	_pMover -> setXYMoveVelocity(1000);

	_pChecker -> _pHitAreaBoxs = NEW HitAreaBoxs(5);
	_pChecker -> _pHitAreaBoxs -> setBox(0, -10000, -10000, 10000, 10000);
	_pChecker -> _pHitAreaBoxs -> setBox(1, -10000,-140000,-10000, 10000,-120000,10000, true,true,true);
	_pChecker -> _pHitAreaBoxs -> setBox(2, -10000, 120000,-10000, 10000, 140000,10000, true,true,true);

	_pChecker -> _pHitAreaBoxs -> setBox(3, -140000,-10000,-10000, -120000, 10000,10000, true,true,true);
	_pChecker -> _pHitAreaBoxs -> setBox(4, 120000, -10000,-10000,  140000, 10000,10000, true,true,true);

//	_pChecker -> _pHitAreaBoxs -> setLine(0, -20000, 20000, 20000, 20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(1, 20000, 20000, 20000, -20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(2, 20000, -20000, -20000, -20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(3, -20000, -20000, -20000, 20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(4, 30000, 30000, -30000, -30000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(5, -30000, 30000, 30000, -30000, true);
//
	_SX = 10000;
	_SY = 10000;
	setAlpha(0.2);

	setBumpableOnlySelf(true);
	declareStop();

}


void MyShot001::processBehavior() {
	if (switchedToPlay()) {
		//出現時共通処理
		setBumpableOnlySelf(true);
		_X = GameGlobal::_pMyShip->_X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
	} else {
		//通常処理
		nextAnimationFrame();
		//座標に反映
		_pMover -> behave();
		_pChecker -> behave();
	}
}

void MyShot001::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		declareStop();
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

void MyShot001::onStop() {
	//消失時処理
	setBumpableOnlySelf(false);
	declareMoveFirst();
}


MyShot001::~MyShot001() {

}
