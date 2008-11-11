#include "stdafx.h"


//initialize()までに上書き可能な設定可能なパラメータ
//_X,_Y,_Z 初期位置、但し _Z<0 であること。（折り返しが逆になって変だから）
//_X_turn,_Y_turn 折り返しXY座標
//_iBeginVelocity 折り返し地点に行くまでの加速度
//
EnemyCeres::EnemyCeres(string prm_name, string prm_model) : DefaultMeshEnemyActor(prm_name, prm_model) {
	_iMovePatternNo = 0;
//	_X = -100*1000;
//	_Y = -100*1000;
//	_Z = 0;

	_X = -356000; //開始座標
	_Y = -100000;
	_Z = -680000;
	_X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2 - 300000;
	_Y_turn = -10000;
	_Z_turn = 0;
	_iBeginVelocity = 5000;

}

void EnemyCeres::initialize() {
	setBumpableOnlySelf(true);

//	_pGeoMover->setMoveVelocity(1000);
//	_pGeoMover->_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;
//
//	//_pGeoMover->setMoveAngleRzVelocityRenge(-2000, 2000);
////	//_pGeoMover -> setMoveAngleRz(0,-100*1000,-100*1000);
////	_pGeoMover -> setMoveAngle(100*1000,0,-100);









//	_incZ =  (1.0*abs(_Z) / (GgafDx9Util::getDistance(_X, _Y, _X_turn, _Y_turn) / (_iBeginVelocity * sgn(_Z) * -1)) );//_incZがおかしい?

	_pGeoMover -> setMoveAngle(_X_turn, _Y_turn, _Z_turn);
	_pGeoMover -> setMoveVelocity(_iBeginVelocity);
	_pGeoMover -> _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = true;
	_pGeoMover -> _synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, 6000);

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);

}

void EnemyCeres::processBehavior() {
//	if (_dwFrame > 5) {
//		_TRACE_(_dwFrame << ":("<<_X<<","<<_Y<<","<<_Z<<")");
//	}
//
//	if (_dwFrame == 100) {
//		_pGeoMover -> setMoveAngleRy(0);
//	} else if (_dwFrame == 200) {
//		_TRACE_("_dwFrame="<<_dwFrame);
//		//_pGeoMover -> setMoveAngleRy(ANGLE45);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE45);
//	} else if (_dwFrame == 300) {
////		_pGeoMover -> setMoveAngleRy(ANGLE90);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE90);
//	} else if (_dwFrame == 400) {
////		_pGeoMover -> setMoveAngleRy(ANGLE135);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE135);
//	} else if (_dwFrame == 500) {
////		_pGeoMover -> setMoveAngleRy(ANGLE180);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE180);
//	} else if (_dwFrame == 600) {
////		_pGeoMover -> setMoveAngleRy(ANGLE225);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE225);
//	} else if (_dwFrame == 700) {
////		_pGeoMover -> setMoveAngleRy(ANGLE270);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE270);
//	} else if (_dwFrame == 800) {
////		_pGeoMover -> setMoveAngleRy(ANGLE315);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE315);
//	} else if (_dwFrame == 900) {
////		_pGeoMover -> setMoveAngleRy(ANGLE360);
//		_pGeoMover->setMoveAngleRyVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRy(ANGLE360);
//	}


	//方向転換
	if (_iMovePatternNo == 0 && _X > _X_turn) {

		_pGeoMover -> setMoveAngleRyVelocity(-4000);
		_pGeoMover -> setMoveAngleRzVelocity(-4000);
		_pGeoMover -> setTargetMoveAngleRz(0);
		_pGeoMover -> setTargetMoveAngleRy(ANGLE180);

		//弾を撃ってみる

		angle way[10] ;
		GgafDx9Util::getWayAngle(180000, 10, 10000, way);
		EnemyShot001* pTama;
		RotationActor* pShots001 = GameGlobal::_pSceneCommon->_pEnemyShots001Rotation;
		for (int i = 0; i < 10; i++) {
			pTama = (EnemyShot001*)pShots001->obtain();
			if (pTama) {
				pTama -> setGeometry (_X, _Y, 0);
				pTama -> _pGeoMover -> setMoveAngleRz(way[i]);
				pTama -> declarePlay();
			}
		}

		_iMovePatternNo++;
	}

	_pGeoMover -> behave();
}

//void EnemyCeres::processBehavior() {
//
//	//方向転換
//	if (_iMovePatternNo == 0 && _X > _X_turn) {
//		_pGeoMover -> setMoveAngleRz(sgn(_incZ)*-1*90000);
//		_pGeoMover -> setMoveAngleRzVelocity(sgn(_incZ)*-1*3000);
//		_pGeoMover -> setTargetMoveAngleRz(ANGLE180);
//		_pGeoMover -> setMoveVelocity(1000);
//
//		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Y, sgn(_incZ)*-1*4000);
//		_pGeoMover -> setTargetAxisRotAngle(AXIS_Y, ANGLE180);
//
//		//弾を撃ってみる
//
//		angle way[10] ;
//		GgafDx9Util::getWayAngle(180000, 10, 10000, way);
//		EnemyShot001* pTama;
//		RotationActor* pShots001 = GameGlobal::_pSceneCommon->_pEnemyShots001Rotation;
//		for (int i = 0; i < 10; i++) {
//			pTama = (EnemyShot001*)pShots001->obtain();
//			if (pTama) {
//				pTama -> setGeometry (_X, _Y, 0);
//				pTama -> _pGeoMover -> setMoveAngleRz(way[i]);
//				pTama -> declarePlay();
//			}
//		}
//
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 1 && _pGeoMover -> _auto_move_angle_rz_target_Flg == false) {
//		_pGeoMover -> setMoveVelocity(2000);
//		_pGeoMover -> setMoveAcceleration(100);
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 2 && _X < -100000) {
//		//_TRACE_("Ceres:"<<getName()<<" (_X,_Y,_Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//
//		_pGeoMover -> setMoveVelocity(0);
//		_pGeoMover -> setZMoveVelocity(0);
//		_pGeoMover -> setMoveAcceleration(0);
//		_pGeoMover -> setZMoveAcceleration(0);
//		_pGeoMover -> setXYZMove(
//				5000,
//				GameGlobal::_pMyShip->_X,
//				GameGlobal::_pMyShip->_Y,
//				GameGlobal::_pMyShip->_Z
//				);
//		_iMovePatternNo++;
//	}
//	//_TRACE_("VX,VY="<<(_pGeoMover ->_vX_Move)<<","<<(_pGeoMover ->_vY_Move));
//
//	//座標に反映
//	_pGeoMover -> behave();
//	//_TRACE_("ab VX,VY="<<(_pGeoMover ->_vX_Move)<<","<<(_pGeoMover ->_vY_Move));
//	if (_incZ > 0) {
//		if (_Z > 0) {
//			_Z = 0;
//			_pGeoMover -> setZMoveVelocity(0);
//		}
//	} else if (_incZ < 0) {
//		if (_Z < 0) {
//			_Z = 0;
//			_pGeoMover -> setZMoveVelocity(0);
//		}
//	}
//
//	//_TRACE_("Ceres("<<_X<<","<<_Y<<","<<_Z<<")"<<_incZ <<"/"<<(_pGeoMover ->_iVelocity_ZMove));
//}

void EnemyCeres::processJudgement() {
	if (isOffScreen()) {
		declareFinishLife();
	}
}

void EnemyCeres::processOnHit(GgafActor* prm_pActor_Opponent) {
	setBumpableOnlySelf(false);
	declareFinishLife();
	EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
	if (pExplo001) {
		pExplo001->setGeometry(this);
		pExplo001->declarePlay();
	}
}

bool EnemyCeres::isOffScreen() {
	if (_X < _X_OffScreenLeft-800000) {
		return true;
	} else {
		return false;
	}
}

EnemyCeres::~EnemyCeres() {
}
