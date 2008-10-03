#include "stdafx.h"

MyLaser001* MyLaser001::_pHeadMyLaser001 = NULL;

MyLaser001::MyLaser001(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {
	_X_prevFrame = 0;
}

void MyLaser001::initialize() {
	_iAnimationMethod = ORDER_LOOP;
	_iAnimationFrame_Interval = 3;

	_pMover -> setXYMoveAngleVelocity(0);
	_pMover -> setXYMoveAngle(0);
	_pMover -> setXYMoveVelocity(_pSpriteModel->_fSize_SpriteModelWidthPx * 1000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -5000, -5000, 5000, 5000);

	setBumpable(false);
}


void MyLaser001::processBehavior() {
	if (switchedToPlay()) {
		//出現時処理
		setBumpable(true);
		_X = GameGlobal::_pMyShip->_X;
		_X_prevFrame = _X;
		_Y = GameGlobal::_pMyShip->_Y;
		_Z = GameGlobal::_pMyShip->_Z;
	} else {
		//通常処理
		nextAnimationFrame();
		//座標に反映
		_pMover -> behave();
		_Y = GameGlobal::_pMyShip->_Y;
	}
}

void MyLaser001::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		declareStop();
	}
}

/*
bool MyLaser001::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyLaser001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyLaser001::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("MyLaser001::processOnHit ショットがヒットしました");
	_TRACE_("MyLaser001ヒットしました。("<<_X<<","<<_Y<<")");
	//declareFinishLife();
	declareStop();
}

void MyLaser001::processFinal() {
	if (switchedToStop()) {
		//消失時処理
		setBumpable(false);
		if (MyLaser001::_pHeadMyLaser001 == this) {
			MyLaser001::_pHeadMyLaser001 = NULL;
		}
		declareMoveFirst();
	}
}

MyLaser001::~MyLaser001() {

}
