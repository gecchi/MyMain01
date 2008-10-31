#include "stdafx.h"

EnemyVesta::EnemyVesta(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
}

void EnemyVesta::initialize() {
	setBumpableOnlySelf(true);
	_X = _X_OffScreenRight+100;
	_Y = 0;
	_Z = 0;
	_pMover -> setMoveVelocityRenge(-8000, 8000);
	_pMover -> setMoveVelocity(8000);
	_pMover -> setMoveAcceleration(-500);
	_pMover -> setXYMoveAngle(ANGLE90);

	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 5000);
	_pMover -> setAxisRotAngleVelocity(AXIS_X, 5000);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);

	_pMover -> setAxisRotAngle(AXIS_Z, ANGLE180);

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyVesta::processBehavior() {
	if (_pMover->_iVelocity_Move <= -8000) {
		_pMover -> setMoveAcceleration(+500);
	} else if (_pMover->_iVelocity_Move >= +8000) {
		_pMover -> setMoveAcceleration(-500);
	}
	_X -= 2000;

	//À•W‚É”½‰f
	_pMover -> behave();
}

void EnemyVesta::processJudgement() {
	if (isOffScreen()) {
		declareFinishLife();
	}
}

void EnemyVesta::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpableOnlySelf(false);
	declareFinishLife();
}

bool EnemyVesta::isOffScreen() {
	if (_Y < _Y_OffScreenBottom-100000) {
		return true;
	} else {
		return false;
	}
}

EnemyVesta::~EnemyVesta() {
}
