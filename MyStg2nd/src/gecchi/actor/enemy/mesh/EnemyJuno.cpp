#include "stdafx.h"

EnemyJuno::EnemyJuno(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
}

void EnemyJuno::initialize() {
	setBumpable(true);
	_Z = 1000000;
	_pMover -> setXYMoveVelocity(0);
	_pMover -> setZMoveVelocity(-20000);
	_pMover -> setAxisRotAngle(AXIS_Y, 90000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyJuno::processHappen(int prm_no) {

	if (prm_no == HAPPEN_PLAY_BEGIN) {
		CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
		_X = (pRndGen->genrand_int32() % (_X_OffScreen_Right*2)) - _X_OffScreen_Right; // _X_OffScreen_Right > 0
		_Y = (pRndGen->genrand_int32() % (_Y_OffScreen_Top*2)) - _Y_OffScreen_Top;     // _Y_OffScreen_Top   > 0
	}
}
void EnemyJuno::processBehavior() {

	//À•W‚É”½‰f
	_pMover -> behave();
}

void EnemyJuno::processJudgement() {
	if (isOffScreen()) {
		declareFinishLife();
	}
}

void EnemyJuno::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpable(false);
	declareFinishLife();
}

bool EnemyJuno::isOffScreen() {
	if (_Z < -1000000) {
		return true;
	} else {
		return false;
	}
}

EnemyJuno::~EnemyJuno() {
}
