#include "stdafx.h"

StgMover::StgMover(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryMover(prm_pActor) {

	//�L�����̈ړ����p�P�ʃx�N�g��
	_vX = _vY = _vZ = 0.0;

	//�ړ����p��Z����]
	_angRZ_Move = 0;
	//�ړ����p��Y����]
	_angRY_Move = 0;

	//XY���ʈړ����pX�����P�ʃx�N�g�� = 0
//	_vX_Move = 0;

	//XY���ʈړ����pY�����P�ʃx�N�g�� = 0
//	_vY_Move = 0;

	//�ړ����x
	_iVelocity_Move = 0;

	//�ړ����x��� = 256 px/fream
	_iTopAngVelocity_Move = 256*LEN_UNIT;  //_iVelocity_Move �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B

	//�ړ����x���� = 0   px/fream
	_iBottomVelocity_Move = -256*LEN_UNIT; //_iVelocity_Move �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B

	//�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
	_iAcceleration_MoveVelocity = 0; //_iVelocity_Move �̑����B�f�t�H���g�͉�������

	//XY���ʈړ����p = 0 angle
	//_angRZ_Move = 0;	//0 angle �� �R���̕����Ɉړ�

	//XY���ʈړ����p�̊p���x = 0 angle/fream
	_angVelocity_XYMoveAngle = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B

	//XY���ʈړ����p�̊p���x��� = +360,000 angle/fream
	_angTopAngVelocity_XYMoveAngle = ANGLE360;  //_angVelocity_XYMoveAngle �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//XY���ʈړ����p�̊p���x���� = -360,000 angle/fream
	_angBottomVelocity_XYMoveAngle = ANGLE360*-1; //_angVelocity_XYMoveAngle �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//XY���ʈړ����p�̊p�����x = 0 angle/fream^2
	_angAcceleration_XYMoveAngleVelocity = 0;     //_angVelocity_XYMoveAngle �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

	//�ڕWXY���ʈړ����p�ւ̎�������t���O = ����
	_auto_xymove_angle_target_Flg = false;
	//�ڕW��XY���ʈړ����p
	_angTarget_Move = 0;
	//�ڕW��XY���ʈړ����p������~�@�\���L���ɂȂ��]����
	_auto_xymove_angle_target_allow_way = TURN_BOTH;
	//�ڕW��XY���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
	_auto_xymove_angle_target_allow_velocity = ANGLE180;

	//XY���ʈړ����p�ɔ���Z����]���p�̓��������@�\�t���O �� ����
	_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

	_iVelocity_ZMove = 0;         //Z��XY���ʈړ����x�iZ�ړ����W�����j�� 0 px/fream
	_iTopAngVelocity_ZMove = 256*LEN_UNIT;  //Z��XY���ʈړ����x��� �� 256 px/fream
	_iBottomVelocity_ZMove = -256*LEN_UNIT; //Z��XY���ʈړ����x���� �� 256 px/fream
	_iAcceleration_ZMoveVelocity = 0;     //Z��XY���ʈړ����x�̉����x �� 0 px/fream^2  (��������)

}



void StgMover::behave() {

	GgafDx9GeometryMover::behave();

	//Z�������x�̏���
	_iVelocity_ZMove += _iAcceleration_ZMoveVelocity;
	setZMoveVelocity(_iVelocity_ZMove);

	//�����x�̏���
	_iVelocity_Move += _iAcceleration_MoveVelocity;

	setMoveVelocity(_iVelocity_Move);

	//�ڕWXY���ʈړ����p�A���O��������~�@�\�g�p���̏ꍇ
	if (_auto_xymove_angle_target_Flg) {

		_angVelocity_XYMoveAngle += _angAcceleration_XYMoveAngleVelocity;
		setXYMoveAngleVelocity(_angVelocity_XYMoveAngle);

		if (_angVelocity_XYMoveAngle > 0) { //�����v���̏ꍇ
			angle angDistance = getDistanceFromXYMoveAngleTo(_angTarget_Move, TURN_COUNTERCLOCKWISE);
			if (_angVelocity_XYMoveAngle > angDistance &&
				_auto_xymove_angle_target_allow_way != TURN_CLOCKWISE &&
				_auto_xymove_angle_target_allow_velocity >= _angVelocity_XYMoveAngle)
			{ //�ڕW���s���߂��Ă��܂���������ȓ�
				addXYMoveAngle(angDistance);
				_auto_xymove_angle_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addXYMoveAngle(_angVelocity_XYMoveAngle);
			}
		} else if (_angVelocity_XYMoveAngle < 0) { //���v���̏ꍇ

			angle angDistance = getDistanceFromXYMoveAngleTo(_angTarget_Move, TURN_CLOCKWISE);
			if (_angVelocity_XYMoveAngle < angDistance &&
				_auto_xymove_angle_target_allow_way != TURN_COUNTERCLOCKWISE &&
				-1*_auto_xymove_angle_target_allow_velocity <= _angVelocity_XYMoveAngle)
			{
				addXYMoveAngle(angDistance);
				_auto_xymove_angle_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addXYMoveAngle(_angVelocity_XYMoveAngle);
			}
		} else {
			//_angVelocity_XYMoveAngle==0
			addXYMoveAngle(0);
		}
		if (_auto_xymove_angle_target_Flg == false) {
			_angTopAngVelocity_XYMoveAngle = ANGLE360;       //XY���ʈړ����p�̊p���x��� �� 360,000 angle/fream
			_angBottomVelocity_XYMoveAngle = ANGLE360*-1;  //XY���ʈړ����p�̊p���x���� �� -360,000 angle/fream
			_angAcceleration_XYMoveAngleVelocity = 0;  //XY���ʈړ������p�A�p�����x���O��
			setXYMoveAngleVelocity(0);               //XY���ʈړ������p�A�p���x���O��
		}

	} else {
		if (_angAcceleration_XYMoveAngleVelocity != 0) {
			//�t���[������XY���ʈړ����p����̏���
			_angVelocity_XYMoveAngle += _angAcceleration_XYMoveAngleVelocity;
			addXYMoveAngle(_angVelocity_XYMoveAngle);
		}
	}



	//Actor�ɔ��f
	_pActor->_X += _vX*_iVelocity_Move;
	_pActor->_Y += _vY*_iVelocity_Move;
	_pActor->_Z += (_vZ*_iVelocity_Move + _iVelocity_ZMove);
	//_TRACE_("www("<<_vX<<","<<_vY<<","<<_vZ<<")  _angRZ_Move/_angRY_Move="<<_angRZ_Move<<"/"<<_angRY_Move);

}



void StgMover::setMoveVelocityRenge(int prm_iVelocity01_Move, int prm_iVelocity02_Move) {
	if (prm_iVelocity01_Move < prm_iVelocity02_Move) {
		_iTopAngVelocity_Move = prm_iVelocity02_Move;
		_iBottomVelocity_Move = prm_iVelocity01_Move;
	} else {
		_iTopAngVelocity_Move = prm_iVelocity01_Move;
		_iBottomVelocity_Move = prm_iVelocity02_Move;
	}
	setMoveVelocity(_iVelocity_Move); //�Đݒ肵�Ĕ͈͓��ɕ␳
}



void StgMover::setMoveVelocity(int prm_iVelocity_Move) {
	if (prm_iVelocity_Move > _iTopAngVelocity_Move) {
		_iVelocity_Move = _iTopAngVelocity_Move;
	} else if (prm_iVelocity_Move < _iBottomVelocity_Move) {
		_iVelocity_Move = _iBottomVelocity_Move;
	} else {
		_iVelocity_Move = prm_iVelocity_Move;
	}
}

void StgMover::setMoveAcceleration(int prm_iAcceleration_MoveVelocity) {
	_iAcceleration_MoveVelocity = prm_iAcceleration_MoveVelocity;
}

void StgMover::setXYMoveAngle(int prm_tX, int prm_tY) {
	setXYMoveAngle(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setXYZMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {

	_TRACE_("_pActor("<<(_pActor->_X)<<","<<(_pActor->_Y)<<","<<(_pActor->_Z)<<")�@���@("<<prm_tX<<","<<prm_tY<<","<<prm_tZ<<")");
	_TRACE_("BRFOR: _v("<<_vX<<","<<_vY<<","<<_vZ<<")  _angRZ_Move/_angRY_Move="<<_angRZ_Move<<"/"<<_angRY_Move);
	GgafDx9Util::getRotAngleZY(
			prm_tX - _pActor->_X,
			prm_tY - _pActor->_Y,
			prm_tZ - _pActor->_Z,
			_vX,
			_vY,
			_vZ,
			_angRZ_Move,
			_angRY_Move
		);

	_TRACE_("BRFOR: _v("<<_vX<<","<<_vY<<","<<_vZ<<")  _angRZ_Move/_angRY_Move="<<_angRZ_Move<<"/"<<_angRY_Move);

}

void StgMover::setXYMoveAngle(angle prm_angXYMove) {
	_TRACE_("setXYMoveAngle("<<prm_angXYMove<<")");
	_TRACE_("setXYMoveAngle BRFOR: _v("<<_vX<<","<<_vY<<","<<_vZ<<")  _angRZ_Move/_angRY_Move="<<_angRZ_Move<<"/"<<_angRY_Move);


	int angSimple = prm_angXYMove;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_angRZ_Move = angSimple;
	//0�ł����̂��I�I�I���߂�
	GgafDx9Util::getNormalizeVectorZY(_angRZ_Move, _angRY_Move, _vX, _vY, _vZ);


	_TRACE_("setXYMoveAngle AFTER: _v("<<_vX<<","<<_vY<<","<<_vZ<<")  _angRZ_Move/_angRY_Move="<<_angRZ_Move<<"/"<<_angRY_Move);

//	_vX_Move = GgafDx9Util::COS_UNITLEN[angSimple/ANGLE_RATE];
//	_vY_Move = GgafDx9Util::SIN_UNITLEN[angSimple/ANGLE_RATE];
	if (_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg) {
		setAxisRotAngle(AXIS_Z, angSimple);
	}
}

void StgMover::setXZMoveAngle(angle prm_angXZMove) {
	int angSimple = prm_angXZMove;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_angRZ_Move = angSimple;
	//0�ł����̂��I�I�I���߂�
	GgafDx9Util::getNormalizeVectorZY(_angRZ_Move, _angRY_Move, _vX, _vY, _vZ);
}


void StgMover::addXYMoveAngle(angle prm_angDistance_XYMoveAngle) {
	angle angOffset_Move = prm_angDistance_XYMoveAngle;
	if (_angBottomVelocity_XYMoveAngle > prm_angDistance_XYMoveAngle) {
		angOffset_Move = _angBottomVelocity_XYMoveAngle;
	} else if (prm_angDistance_XYMoveAngle > _angTopAngVelocity_XYMoveAngle) {
		angOffset_Move = _angTopAngVelocity_XYMoveAngle;
	}
	setXYMoveAngle(_angRZ_Move + angOffset_Move);
}

void StgMover::setXYMoveAngleVelocity(angle prm_angVelocity_XYMoveAngle) {
	if (prm_angVelocity_XYMoveAngle > _angTopAngVelocity_XYMoveAngle) {
		_angVelocity_XYMoveAngle = _angTopAngVelocity_XYMoveAngle;
	} else if (prm_angVelocity_XYMoveAngle < _angBottomVelocity_XYMoveAngle) {
		_angVelocity_XYMoveAngle = _angBottomVelocity_XYMoveAngle;
	} else {
		_angVelocity_XYMoveAngle = prm_angVelocity_XYMoveAngle;
	}
}

void StgMover::setXYMoveAngleAcceleration(angle prm_angAcceleration_XYMoveAngleVelocity) {
	_angAcceleration_XYMoveAngleVelocity = prm_angAcceleration_XYMoveAngleVelocity;
}


void StgMover::setXYMoveAngleVelocityRenge(angle prm_angVelocity01_XYMoveAngle, angle prm_angVelocity02_XYMoveAngle) {
	if (prm_angVelocity01_XYMoveAngle < prm_angVelocity02_XYMoveAngle) {
		_angTopAngVelocity_XYMoveAngle = prm_angVelocity02_XYMoveAngle;
		_angBottomVelocity_XYMoveAngle = prm_angVelocity01_XYMoveAngle;
	} else {
		_angTopAngVelocity_XYMoveAngle = prm_angVelocity01_XYMoveAngle;
		_angBottomVelocity_XYMoveAngle = prm_angVelocity02_XYMoveAngle;
	}
	setXYMoveAngleVelocity(_angVelocity_XYMoveAngle); //�Đݒ肵�Ĕ͈͓��ɕ␳
}


void StgMover::setTargetXYMoveAngle(angle prm_angTarget_Move, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	_auto_xymove_angle_target_Flg = true;
	_angTarget_Move = simplifyAngle(prm_angTarget_Move);
	_auto_xymove_angle_target_allow_way = prm_iAllowRotWay;
	_auto_xymove_angle_target_allow_velocity = prm_angAllowVelocity;
}

void StgMover::setTargetXYMoveAngleV(int prm_tX, int prm_tY, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	setTargetXYMoveAngle(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_iAllowRotWay);
}

angle StgMover::getDistanceFromXYMoveAngleTo(int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromXYMoveAngleTo(
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}


angle StgMover::getDistanceFromXYMoveAngleTo(angle prm_angTarget_Move, int prm_iWay) {
	angle angTarget_Move = simplifyAngle(prm_angTarget_Move);
	if (prm_iWay ==  TURN_CLOSE_TO) { //�߂��ق���]
		if (0 <= _angRZ_Move && _angRZ_Move < ANGLE180) {
			if (0 <= angTarget_Move && angTarget_Move < _angRZ_Move) {
				return -1*(_angRZ_Move - angTarget_Move);
			} else if (angTarget_Move == _angRZ_Move) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angRZ_Move < angTarget_Move && angTarget_Move < _angRZ_Move+ANGLE180) {
				return angTarget_Move - _angRZ_Move;
			} else if (angTarget_Move == _angRZ_Move+ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angRZ_Move+ANGLE180 < angTarget_Move && angTarget_Move <= ANGLE360) {
				return -1*(_angRZ_Move+(ANGLE360 - angTarget_Move));
			} else {
				//��������
				_TRACE_("_angRZ_Move=" << _angRZ_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::behave() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
			}
		} else if(ANGLE180 <= _angRZ_Move && _angRZ_Move <= ANGLE360) {
			if (0 <= angTarget_Move && angTarget_Move < _angRZ_Move-ANGLE180) {
				return ANGLE360 - _angRZ_Move + angTarget_Move;
			} else if (angTarget_Move == _angRZ_Move-ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angRZ_Move-ANGLE180 < angTarget_Move && angTarget_Move < _angRZ_Move) {
				return -1*(_angRZ_Move - angTarget_Move);
			} else if (_angRZ_Move == angTarget_Move) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angRZ_Move < angTarget_Move && angTarget_Move <= ANGLE360) {
				return angTarget_Move - _angRZ_Move;
			} else {
				//��������
				_TRACE_("_angRZ_Move=" << _angRZ_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
		if (0 <= _angRZ_Move && _angRZ_Move < angTarget_Move) {
			return (angTarget_Move - _angRZ_Move);
		} else if (angTarget_Move < _angRZ_Move && _angRZ_Move < ANGLE360) {
			return ANGLE360 - _angRZ_Move + angTarget_Move;
		} else if (_angRZ_Move == angTarget_Move) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angRZ_Move=" << _angRZ_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //���v���̏ꍇ
		if (0 <= _angRZ_Move && _angRZ_Move < angTarget_Move) {
			return -1*( _angRZ_Move + ANGLE360 - angTarget_Move);
		} else if (angTarget_Move < _angRZ_Move && _angRZ_Move < ANGLE360) {
			return -1*(_angRZ_Move - angTarget_Move);
		} else if (_angRZ_Move == angTarget_Move) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angRZ_Move=" << _angRZ_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
		}
	}

	_TRACE_("_angRZ_Move=" << _angRZ_Move << "/angTarget_Move=" << angTarget_Move);
	throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() ���̂�����p�̋��������߂�܂���B(1)");

}

void StgMover::setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove) {
	if (prm_iVelocity01_ZMove < prm_iVelocity02_ZMove) {
		_iTopAngVelocity_ZMove = prm_iVelocity02_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity01_ZMove;
	} else {
		_iTopAngVelocity_ZMove = prm_iVelocity01_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity02_ZMove;
	}
	setZMoveVelocity(_iVelocity_ZMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}



void StgMover::setZMoveVelocity(int prm_iVelocity_ZMove) {
	if (prm_iVelocity_ZMove > _iTopAngVelocity_ZMove) {
		_iVelocity_ZMove = _iTopAngVelocity_ZMove;
	} else if (prm_iVelocity_ZMove < _iBottomVelocity_ZMove) {
		_iVelocity_ZMove = _iBottomVelocity_ZMove;
	} else {
		_iVelocity_ZMove = prm_iVelocity_ZMove;
	}
}

void StgMover::setZMoveAcceleration(int prm_iAcceleration_ZMoveVelocity) {
	_iAcceleration_ZMoveVelocity = prm_iAcceleration_ZMoveVelocity;
}

void StgMover::setXYZMove(int prm_iVelocity, int tx, int ty, int tz) {
	_TRACE_("setXYZMove (tx,ty,tx)=("<<tx<<","<<ty<<","<<tz<<")");
	_TRACE_("setXYZMove _pActor-> "<<_pActor->getName()<< " (_X,_Y,_Z)=("<<(_pActor->_X)<<","<<(_pActor->_Y)<<","<<(_pActor->_Z)<<")");
	double nvx, nvy, nvz;
	angle rZ, rY;
	GgafDx9Util::getRotAngleZY(
			tx - _pActor->_X,
			ty - _pActor->_Y,
			tz - _pActor->_Z,
			nvx,
			nvy,
			nvz,
			rZ,
			rY
		);

	setMoveVelocity(0);
	setZMoveVelocity(0);
	setMoveAcceleration(0);
	setZMoveAcceleration(0);
	_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg = false;
//	_vX_Move = nvx * LEN_UNIT;
//	_vY_Move = nvy * LEN_UNIT;
	//_iVelocity_Move = prm_iVelocity;
	_iVelocity_ZMove = 	prm_iVelocity * nvz;
	setAxisRotAngle(AXIS_Z, rZ);
	setAxisRotAngle(AXIS_Y, rY);

}
//	setXYMoveAngle(tx, ty);
//	double dz = abs(tz - _pActor->_Z);
//	double dxy = sqrt( ((tx - _pActor->_X)*(tx - _pActor->_X)) +
//			           ((ty - _pActor->_Y)*(ty - _pActor->_Y))
//			         );
//	_TRACE_("("<<(_pActor->_X)<<","<<(_pActor->_Y)<<","<<(_pActor->_Z)<<")�@���@("<<tx<<","<<ty<<","<<tz<<")  dz="<<dz<<" dxy="<<dxy);
//	if (dz > dxy) {
//		//z���
//		setZMoveVelocity(sgn(tz - _pActor->_Z) * prm_iVelocity);
//		if (dz != 0) {
//			setMoveVelocity((dxy/dz) * prm_iVelocity);
//		} else {
//			setMoveVelocity(0);
//		}
//	} else {
//		if (dxy != 0) {
//			setZMoveVelocity(sgn(tz - _pActor->_Z) * (dz/dxy) * prm_iVelocity);
//		} else {
//			setZMoveVelocity(0);
//		}
//		setMoveVelocity(prm_iVelocity);
//	}
//
//}



StgMover::~StgMover() {
}
