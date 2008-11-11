#include "stdafx.h"

EnemyJuno::EnemyJuno(string prm_name, string prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
	_iMovePatternNo = 0;
}

void EnemyJuno::initialize() {

	_Z = 5000000;
	_pGeoMover -> setMoveVelocity(0);
	_pGeoMover -> setZMoveVelocity(-40000);
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, 5000);
	_pGeoMover -> setAxisRotAngle(AXIS_Y, 90000);


	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyJuno::processBehavior() {
	if (switchedToPlay()) {
		//oŒ»Žžˆ—
		setBumpableOnlySelf(true);
		_X += FormationJuno001::_s_X_FormationWhole;
	}

	_X += FormationJuno001::_s_incX;
	//À•W‚É”½‰f
	_pGeoMover -> behave();
}

void EnemyJuno::processJudgement() {
	if (isOffScreen()) {
		setBumpableOnlySelf(false);
		declareFinishLife();
	}
}

void EnemyJuno::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpableOnlySelf(false);
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
