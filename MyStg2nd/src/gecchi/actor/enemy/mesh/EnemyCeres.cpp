#include "stdafx.h"

EnemyCeres::EnemyCeres(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
}

void EnemyCeres::initialize() {
	setBumpable(true);
	_X = -256000;
	_Y = -100000;
	_Z = -800000;
	_pMover -> setAxisRotAngle(AXIS_X, 0);
	_pMover -> setAxisRotAngle(AXIS_Y, -45000);
	_pMover -> setAxisRotAngle(AXIS_Z, 0);

	_pMover -> setXYMoveAngle(900000, 0);
	_pMover -> setXYMoveVelocity(4000);

	_pMover -> setAxisRotAngleVelocity(AXIS_X, 5000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyCeres::processBehavior() {
	if (_Z < 0 ) {
		_Z += 4000;
	} else {
		_Z = 0;
	}

	if (_iMovePatternNo == 1 && _pMover -> _auto_xymove_angle_target_Flg == false) {
		_pMover -> setXYMoveVelocity(2000);
		_pMover -> setXYMoveAcceleration(100);
		_iMovePatternNo++;
	}

	if (_iMovePatternNo == 0 && _X > 450000) {
		_pMover -> setXYMoveAngle(90000);
		_pMover -> setXYMoveAngleVelocity(3000);
		_pMover -> setTargetXYMoveAngle(ANGLE180);
		_pMover -> setXYMoveVelocity(1000);

		_pMover -> setAxisRotAngleVelocity(AXIS_Y, -4000);
		_pMover -> setTargetAxisRotAngle(AXIS_Y, ANGLE180);

		_iMovePatternNo++;
	}

	//À•W‚É”½‰f
	_pMover -> behave();
}

void EnemyCeres::processJudgement() {
	if (isOffScreen()) {
		declareFinishLife();
	}
}

void EnemyCeres::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpable(false);
	declareFinishLife();
}

bool EnemyCeres::isOffScreen() {
	if (_X < _X_OffScreenLeft-100000) {
		return true;
	} else {
		return false;
	}
}

EnemyCeres::~EnemyCeres() {
}
