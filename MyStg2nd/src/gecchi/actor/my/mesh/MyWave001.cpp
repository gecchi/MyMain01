#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyWave001::MyWave001(string prm_name, string prm_model) : DefaultMeshActor(prm_name, prm_model) {
	_class_name = "MyWave001";
}

void MyWave001::initialize() {
	//setAnimationMethod(OSCILLATE_LOOP, 2);

	_pGeoMover -> setMoveAngleRzVelocity(0);
	//_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, 2*1000);
	//_pGeoMover -> setMoveAngleRz(0);
	//_pGeoMover -> setAxisRotAngle(AXIS_Z, 0);
	_pGeoMover -> setMoveVelocity(2000);

	_pChecker -> useHitAreaBoxNum(7);
	_pChecker -> setHitAreaBox(0, -10000, -10000, -10000, 10000, 10000,10000, true,true,true);
	_pChecker -> setHitAreaBox(1, -10000,-140000,-10000, 10000,-120000,10000, true,true,true);
	_pChecker -> setHitAreaBox(2, -10000, 120000,-10000, 10000, 140000,10000, true,true,true);
	_pChecker -> setHitAreaBox(3, -140000,-10000,-10000, -120000, 10000,10000, true,true,true);
	_pChecker -> setHitAreaBox(4, 120000, -10000,-10000,  140000, 10000,10000, true,true,true);
	_pChecker -> setHitAreaBox(5, -10000,-10000,-140000, 10000, 10000,-120000, true,true,true);
	_pChecker -> setHitAreaBox(6, -10000,-10000, 120000,  10000, 10000, 140000, true,true,true);


//	_pChecker -> _pHitAreaBoxs -> setLine(0, -20000, 20000, 20000, 20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(1, 20000, 20000, 20000, -20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(2, 20000, -20000, -20000, -20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(3, -20000, -20000, -20000, 20000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(4, 30000, 30000, -30000, -30000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(5, -30000, 30000, 30000, -30000, true);
//
	_SX = 10000;
	_SY = 10000;
	//setAlpha(0.2);

	setBumpableAlone(true);
	stop();

}


void MyWave001::processBehavior() {
	if (switchedToPlay()) {
		//出現時共通処理
		setBumpableAlone(true);
		setGeometry(GameGlobal::_pMyShip);
		_pGeoMover -> setAxisRotAngle(AXIS_Z, GameGlobal::_pMyShip->_pGeoMover->_angAxisRot[AXIS_Z]);
		_pGeoMover -> setAxisRotAngle(AXIS_Y, GameGlobal::_pMyShip->_pGeoMover->_angAxisRot[AXIS_Y]);
		_pGeoMover -> setMoveAngleRzRy(
				GameGlobal::_pMyShip->_pGeoMover->_angAxisRot[AXIS_Z],
				GameGlobal::_pMyShip->_pGeoMover->_angAxisRot[AXIS_Y]
				   );
//		_X = GameGlobal::_pMyShip->_X;
//		_Y = GameGlobal::_pMyShip->_Y;
//		_Z = GameGlobal::_pMyShip->_Z;
	} else {
		//通常処理
		//nextAnimationFrame();
		//座標に反映
		_pGeoMover -> behave();
		_pChecker -> behave();
	}
}

void MyWave001::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
	if (isOffScreen()) {
		stop();
	}

}

/*
bool MyWave001::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyWave001::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyWave001::processOnHit(GgafActor* prm_pActor_Opponent) {
//_TRACE_("MyWave001::processOnHit ショットがヒットしました");
	//_TRACE_("MyWave001ヒットしました。("<<_X<<","<<_Y<<")");
	//farewell();
	stop();
}

void MyWave001::onStop() {
	//消失時処理
	setBumpableAlone(false);
	moveFirst();
}


MyWave001::~MyWave001() {

}
