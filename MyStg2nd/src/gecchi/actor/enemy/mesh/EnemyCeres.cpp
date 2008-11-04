#include "stdafx.h"


//initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^
//_X,_Y,_Z �����ʒu�A�A�� _Z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j
//_X_turn,_Y_turn �܂�Ԃ�XY���W
//_iBeginVelocity �܂�Ԃ��n�_�ɍs���܂ł̉����x
//
EnemyCeres::EnemyCeres(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;
	_X = -100*1000;
	_Y = -100*1000;
	_Z = 0;

//	_X = -556000; //�J�n���W
//	_Y = -100000;
//	_Z = -480000;
//	_X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2 - 50000;
//	_Y_turn = -10000;
//	_Z_turn = 0;
//	_iBeginVelocity = 5000;

}

void EnemyCeres::initialize() {
	setBumpableOnlySelf(true);

	_pMover->setMoveVelocity(1000);
	_pMover->_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = true;

	//_pMover->setMoveAngleRzVelocityRenge(-2000, 2000);

//	//_pMover -> setMoveAngleRz(0,-100*1000,-100*1000);
//
//
//	_pMover -> setMoveAngle(100*1000,0,-100);









//	_incZ =  (1.0*abs(_Z) / (GgafDx9Util::getDistance(_X, _Y, _X_turn, _Y_turn) / (_iBeginVelocity * sgn(_Z) * -1)) );//_incZ����������?
//
//	_pMover -> setMoveAngle(_X_turn, _Y_turn, _Z_turn);
//	_pMover -> setMoveVelocity(_iBeginVelocity);
//	//_pMover -> setZMoveVelocity(_incZ);
//
//	_pMover -> setAxisRotAngle(AXIS_Z, _pMover->_angRz_Move);
//	_pMover -> setAxisRotAngle(AXIS_Y, _pMover->_angRy_Move);
//	_pMover -> setAxisRotAngleVelocity(AXIS_X, 6000);

	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);

}

void EnemyCeres::processBehavior() {
//	if (_dwFrame > 5) {
//		_TRACE_(_dwFrame << ":("<<_X<<","<<_Y<<","<<_Z<<")");
//	}
//
	if (_dwFrame == 100) {
		_pMover -> setMoveAngleRy(0);
	} else if (_dwFrame == 200) {
		_TRACE_("_dwFrame="<<_dwFrame);
		//_pMover -> setMoveAngleRy(ANGLE45);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE45);
	} else if (_dwFrame == 300) {
//		_pMover -> setMoveAngleRy(ANGLE90);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE90);
	} else if (_dwFrame == 400) {
//		_pMover -> setMoveAngleRy(ANGLE135);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE135);
	} else if (_dwFrame == 500) {
//		_pMover -> setMoveAngleRy(ANGLE180);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE180);
	} else if (_dwFrame == 600) {
//		_pMover -> setMoveAngleRy(ANGLE225);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE225);
	} else if (_dwFrame == 700) {
//		_pMover -> setMoveAngleRy(ANGLE270);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE270);
	} else if (_dwFrame == 800) {
//		_pMover -> setMoveAngleRy(ANGLE315);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE315);
	} else if (_dwFrame == 900) {
//		_pMover -> setMoveAngleRy(ANGLE360);
		_pMover->setMoveAngleRyVelocity(2000);
		_pMover -> setTargetMoveAngleRy(ANGLE360);
	}

























	_pMover -> behave();
}

//void EnemyCeres::processBehavior() {
//
//	//�����]��
//	if (_iMovePatternNo == 0 && _X > _X_turn) {
//		_pMover -> setMoveAngleRz(sgn(_incZ)*-1*90000);
//		_pMover -> setMoveAngleRzVelocity(sgn(_incZ)*-1*3000);
//		_pMover -> setTargetMoveAngleRz(ANGLE180);
//		_pMover -> setMoveVelocity(1000);
//
//		_pMover -> setAxisRotAngleVelocity(AXIS_Y, sgn(_incZ)*-1*4000);
//		_pMover -> setTargetAxisRotAngle(AXIS_Y, ANGLE180);
//
//		//�e�������Ă݂�
//
//		angle way[10] ;
//		GgafDx9Util::getWayAngle(180000, 10, 10000, way);
//		EnemyShot001* pTama;
//		RotationActor* pShots001 = GameGlobal::_pSceneCommon->_pEnemyShots001Rotation;
//		for (int i = 0; i < 10; i++) {
//			pTama = (EnemyShot001*)pShots001->obtain();
//			if (pTama) {
//				pTama -> setGeometry (_X, _Y, 0);
//				pTama -> _pMover -> setMoveAngleRz(way[i]);
//				pTama -> declarePlay();
//			}
//		}
//
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 1 && _pMover -> _auto_move_angle_rz_target_Flg == false) {
//		_pMover -> setMoveVelocity(2000);
//		_pMover -> setMoveAcceleration(100);
//		_iMovePatternNo++;
//	}
//
//	if (_iMovePatternNo == 2 && _X < -100000) {
//		//_TRACE_("Ceres:"<<getName()<<" (_X,_Y,_Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//
//		_pMover -> setMoveVelocity(0);
//		_pMover -> setZMoveVelocity(0);
//		_pMover -> setMoveAcceleration(0);
//		_pMover -> setZMoveAcceleration(0);
//		_pMover -> setXYZMove(
//				5000,
//				GameGlobal::_pMyShip->_X,
//				GameGlobal::_pMyShip->_Y,
//				GameGlobal::_pMyShip->_Z
//				);
//		_iMovePatternNo++;
//	}
//	//_TRACE_("VX,VY="<<(_pMover ->_vX_Move)<<","<<(_pMover ->_vY_Move));
//
//	//���W�ɔ��f
//	_pMover -> behave();
//	//_TRACE_("ab VX,VY="<<(_pMover ->_vX_Move)<<","<<(_pMover ->_vY_Move));
//	if (_incZ > 0) {
//		if (_Z > 0) {
//			_Z = 0;
//			_pMover -> setZMoveVelocity(0);
//		}
//	} else if (_incZ < 0) {
//		if (_Z < 0) {
//			_Z = 0;
//			_pMover -> setZMoveVelocity(0);
//		}
//	}
//
//	//_TRACE_("Ceres("<<_X<<","<<_Y<<","<<_Z<<")"<<_incZ <<"/"<<(_pMover ->_iVelocity_ZMove));
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
