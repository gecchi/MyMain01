#include "stdafx.h"

EnemyJuno::EnemyJuno(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
}

void EnemyJuno::initialize() {
	setBumpable(true);
	if (isFirst()) {
		_X = _X_OffScreen_Right/2;
	} else {
		_X = getPrev()->_X;
	}
	_Z = 500*1000;
	_pMover -> setAxisRotAngle(AXIS_Y, -90000);
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyJuno::processBehavior() {
	_X -= 2000;
	_Z -= 10000;

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
