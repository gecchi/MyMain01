#include "stdafx.h"

EnemyPallas::EnemyPallas(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
}

void EnemyPallas::initialize() {
	setBumpable(true);
	_X = _X_OffScreenRight+100;
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

void EnemyPallas::processBehavior() {
	if (_pMover->_iVelocity_XYMove <= -8000) {
		_pMover -> setXYMoveAcceleration(+500);
	} else if (_pMover->_iVelocity_XYMove >= +8000) {
		_pMover -> setXYMoveAcceleration(-500);
	}
	_X -= 2000;

	//À•W‚É”½‰f
	_pMover -> behave();
}

void EnemyPallas::processJudgement() {
	if (isOffScreen()) {
		declareFinishLife();
	}
}

void EnemyPallas::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpable(false);
	declareFinishLife();
}

bool EnemyPallas::isOffScreen() {
	if (_X < _X_OffScreenLeft-100000) {
		return true;
	} else {
		return false;
	}
}

EnemyPallas::~EnemyPallas() {
}
