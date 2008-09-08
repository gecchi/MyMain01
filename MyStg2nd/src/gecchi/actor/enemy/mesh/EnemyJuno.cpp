#include "stdafx.h"

EnemyJuno::EnemyJuno(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
}

void EnemyJuno::initialize() {
	setBumpable(true);
	_X = _X_OffScreen_Right+100;
	_Y = 0;
	_Z = 0;
	_pMover -> setXYMoveVelocityRenge(-8000, 8000);
	_pMover -> setXYMoveVelocity(8000);
	_pMover -> setXYMoveAcceleration(-500);
	_pMover -> setXYMoveAngle(ANGLE90);

	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 5000);
	_pMover -> setAxisRotAngleVelocity(AXIS_X, 5000);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);

	_pMover -> setAxisRotAngle(AXIS_Z, ANGLE180);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyJuno::processBehavior() {
	if (_pMover->_iVelocity_XYMove <= -8000) {
		_pMover -> setXYMoveAcceleration(+500);
	} else if (_pMover->_iVelocity_XYMove >= +8000) {
		_pMover -> setXYMoveAcceleration(-500);
	}
	_X -= 2000;

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
	if (_X < _X_OffScreen_Left-100000) {
		return true;
	} else {
		return false;
	}
}

EnemyJuno::~EnemyJuno() {
}
