#include "stdafx.h"

EnemyVesta::EnemyVesta(string prm_name, string prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
	_class_name = "EnemyVesta";

	_iMovePatternNo = 0;
}

void EnemyVesta::initialize() {
	setBumpableAlone(true);
	_X = _X_OffScreenRight+100;
	_Y = 0;
	_Z = 0;
	_pGeoMover -> setMoveVelocityRenge(-8000, 8000);
	_pGeoMover -> setMoveVelocity(8000);
	_pGeoMover -> setMoveAcceleration(-500);
	_pGeoMover -> setMoveAngleRz(ANGLE90);

	_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 5000);
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, 5000);
	_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, 0);

	_pGeoMover -> setAxisRotAngle(AXIS_Z, ANGLE180);

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyVesta::processBehavior() {
	if (_pGeoMover->_iVelocity_Move <= -8000) {
		_pGeoMover -> setMoveAcceleration(+500);
	} else if (_pGeoMover->_iVelocity_Move >= +8000) {
		_pGeoMover -> setMoveAcceleration(-500);
	}
	_X -= 2000;

	//À•W‚É”½‰f
	_pGeoMover -> behave();
}

void EnemyVesta::processJudgement() {
	if (isOffScreen()) {
		declareFinishLife();
	}
}

void EnemyVesta::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpableAlone(false);
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
