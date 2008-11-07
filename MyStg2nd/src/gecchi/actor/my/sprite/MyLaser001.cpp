#include "stdafx.h"

MyLaser001::MyLaser001(string prm_name, string prm_xname) : DefaultSpriteMyActor(prm_name, prm_xname) {

}

void MyLaser001::initialize() {
	setAnimationMethod(ORDER_LOOP, 1);

	_pGeoMover -> setMoveVelocity(_pSpriteModel->_fSize_SpriteModelWidthPx * 1000);

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -5000, -5000, 5000, 5000);

	_pActor_Radical = NULL;

	setBumpableOnlySelf(true);
}



void MyLaser001::processBehavior() {
	if (switchedToPlay()) {
		//出現時処理
		setBumpableOnlySelf(true);
		setGeometry(_pActor_Radical);
		_pGeoMover -> setAxisRotAngle(AXIS_Z, _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Z]);
		_pGeoMover -> setAxisRotAngle(AXIS_Y, _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Y]);
		_pGeoMover -> setMoveAngleRzRy(
				     _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Z],
				     _pActor_Radical->_pGeoMover->_angAxisRot[AXIS_Y]
				   );
		_X_begin = _pActor_Radical->_X;
		_Y_begin = _pActor_Radical->_Y;
		_Z_begin = _pActor_Radical->_Z;

	} else {
		//通常処理
		nextAnimationFrame();

	}
	//座標に反映
	_pGeoMover -> behave();

	_X += (_pActor_Radical->_X - _X_begin);
	_Y += (_pActor_Radical->_Y - _Y_begin);
	_Z = _pActor_Radical->_Z;


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

void MyLaser001::onStop() {
	setBumpableOnlySelf(false);
}

MyLaser001::~MyLaser001() {

}
