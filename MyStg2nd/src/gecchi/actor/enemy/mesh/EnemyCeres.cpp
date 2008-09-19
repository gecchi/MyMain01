#include "stdafx.h"

EnemyCeres::EnemyCeres(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;



}

void EnemyCeres::initialize() {
	setBumpable(true);
	_X = -256000;
	_Y = -100000;
	_Z = -1800000;
	_X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2 - 150000;
	_Y_turn = 200000;
	_iBeginVelocity = 4000;
	_incZ =  (_Z / GgafDx9Util::getDistance(0, _X_turn, _Z, _X) ) *_iBeginVelocity;

	_pMover -> setAxisRotAngle(AXIS_X, 0);
	_pMover -> setAxisRotAngle(AXIS_Y, sgn(_Z) * GgafDx9Util::getAngle(abs(_Z), abs(_X_turn-_X)));
	_pMover -> setAxisRotAngle(AXIS_Z, 0);

	_pMover -> setXYMoveAngle(_Y_turn, 0);
	_pMover -> setXYMoveVelocity(_iBeginVelocity);

	_pMover -> setAxisRotAngleVelocity(AXIS_X, 5000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);
}

void EnemyCeres::processBehavior() {
	if (_Z < 0 ) {
		_Z += _incZ;
	} else {
		_Z = 0;
	}


	if (_iMovePatternNo == 0 && _X > _X_turn) {
		_pMover -> setXYMoveAngle(90000);
		_pMover -> setXYMoveAngleVelocity(3000);
		_pMover -> setTargetXYMoveAngle(ANGLE180);
		_pMover -> setXYMoveVelocity(1000);

		_pMover -> setAxisRotAngleVelocity(AXIS_Y, -4000);
		_pMover -> setTargetAxisRotAngle(AXIS_Y, ANGLE180);

		//’e‚ðŒ‚‚Á‚Ä‚Ý‚é

		angle way[10] ;
		GgafDx9Util::getWayAngle(180000, 10, 10000, way);
		EnemyShot001Actor* pTama;
		for (int i = 0; i < 10; i++) {
			pTama = (EnemyShot001Actor*)(GameGlobal::_pSceneCommon->_pEnemyShots001Rotation->get());
			if (pTama) {
				pTama -> setGeometry (_X, _Y, 0);
				pTama -> _pMover -> setXYMoveAngle(way[i]);
				pTama -> begin();
			}
		}

		_iMovePatternNo++;
	}

	if (_iMovePatternNo == 1 && _pMover -> _auto_xymove_angle_target_Flg == false) {
		_pMover -> setXYMoveVelocity(2000);
		_pMover -> setXYMoveAcceleration(100);
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
