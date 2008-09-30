#include "stdafx.h"


//initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^
//_X,_Y,_Z �����ʒu�A�A�� _Z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j
//_X_turn,_Y_turn �܂�Ԃ�XY���W
//_iBeginVelocity �܂�Ԃ��n�_�ɍs���܂ł̉����x
//
EnemyCeres::EnemyCeres(string prm_name, string prm_xname) : DefaultMeshEnemyActor(prm_name, prm_xname) {
	_iMovePatternNo = 0;


	_X = -556000; //�J�n���W
	_Y = -100000;
	_Z = -480000;
	_X_turn = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2 - 50000;
	_Y_turn = -10000;
	_iBeginVelocity = 5000;

}

void EnemyCeres::initialize() {
	setBumpable(true);

	_incZ =  (1.0*abs(_Z) / (GgafDx9Util::getDistance(_X, _Y, _X_turn, _Y_turn) / (_iBeginVelocity * sgn(_Z) * -1)) );//_incZ����������?

	_pMover -> setAxisRotAngle(AXIS_X, 0);
	_pMover -> setAxisRotAngle(AXIS_Y, sgn(_Z) * GgafDx9Util::getAngle(abs(_Z), abs(_X_turn-_X)));
	_pMover -> setAxisRotAngle(AXIS_Z, 0);

	_pMover -> setXYMoveAngle(_X_turn, _Y_turn);
	_pMover -> setXYMoveVelocity(_iBeginVelocity);
	_pMover -> setZMoveVelocity(_incZ);
	_pMover -> setAxisRotAngleVelocity(AXIS_X, 6000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pChecker -> setStatus(100, 1, 1, 1);


//	_TRACE_("_incZ="<<_incZ);
//	_TRACE_("AXIS_Y="<<(sgn(_Z) * GgafDx9Util::getAngle(abs(_Z), abs(_X_turn-_X))) );
}

void EnemyCeres::processBehavior() {



	if (_iMovePatternNo == 0 && _X > _X_turn) {
		_pMover -> setXYMoveAngle(sgn(_incZ)*-1*90000);
		_pMover -> setXYMoveAngleVelocity(sgn(_incZ)*-1*3000);
		_pMover -> setTargetXYMoveAngle(ANGLE180);
		_pMover -> setXYMoveVelocity(1000);

		_pMover -> setAxisRotAngleVelocity(AXIS_Y, sgn(_incZ)*-1*4000);
		_pMover -> setTargetAxisRotAngle(AXIS_Y, ANGLE180);

		//�e�������Ă݂�

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

	//���W�ɔ��f
	_pMover -> behave();

	if (_incZ > 0) {
		if (_Z > 0) {
			_Z = 0;
			_pMover -> setZMoveVelocity(0);
		}
	} else if (_incZ < 0) {
		if (_Z < 0) {
			_Z = 0;
			_pMover -> setZMoveVelocity(0);
		}
	}

	_TRACE_("Ceres("<<_X<<","<<_Y<<","<<_Z<<")"<<_incZ <<"/"<<(_pMover ->_iVelocity_ZMove));
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
	if (_X < _X_OffScreenLeft-800000) {
		return true;
	} else {
		return false;
	}
}

EnemyCeres::~EnemyCeres() {
}
