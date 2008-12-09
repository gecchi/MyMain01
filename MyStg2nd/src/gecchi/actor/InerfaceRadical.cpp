#include "stdafx.h"

InerfaceRadical::InerfaceRadical(string prm_name, string prm_model) : DefaultSpriteMyActor(prm_name, prm_model) {
	_class_name = "InerfaceRadical";
}

void InerfaceRadical::initialize() {
	setAnimationMethod(OSCILLATE_LOOP, 2);

	_pGeoMover -> setMoveAngleRzVelocity(0);
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, 2*1000);
	_pGeoMover -> setMoveAngleRz(0);
	_pGeoMover -> setAxisRotAngle(AXIS_Z, 0);
	_pGeoMover -> setMoveVelocity(1000);

	_pChecker -> useHitArea(7);
	_pChecker -> setHitArea(0, -10000, -10000, -10000, 10000, 10000,10000, true,true,true);
	_pChecker -> setHitArea(1, -10000,-140000,-10000, 10000,-120000,10000, true,true,true);
	_pChecker -> setHitArea(2, -10000, 120000,-10000, 10000, 140000,10000, true,true,true);
	_pChecker -> setHitArea(3, -140000,-10000,-10000, -120000, 10000,10000, true,true,true);
	_pChecker -> setHitArea(4, 120000, -10000,-10000,  140000, 10000,10000, true,true,true);
	_pChecker -> setHitArea(5, -10000,-10000,-140000, 10000, 10000,-120000, true,true,true);
	_pChecker -> setHitArea(6, -10000,-10000, 120000,  10000, 10000, 140000, true,true,true);


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


void InerfaceRadical::processBehavior() {
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
		_pGeoMover -> behave();
		_pChecker -> behave();
	}
}

void InerfaceRadical::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		declareStop();
	}

}

/*
bool InerfaceRadical::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("InerfaceRadical::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void InerfaceRadical::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("InerfaceRadical::processOnHit ショットがヒットしました");
	//_TRACE_("InerfaceRadicalヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	declareStop();
}

void InerfaceRadical::onStop() {
	//消失時処理
	setBumpableOnlySelf(false);
	declareMoveFirst();
}


InerfaceRadical::~InerfaceRadical() {

}
