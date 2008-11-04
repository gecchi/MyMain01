#include "stdafx.h"

StgMover::StgMover(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryMover(prm_pActor) {

	//�L�����̈ړ����p�P�ʃx�N�g��
	_vX = _vY = _vZ = 0.0;

	//�ړ����p��Z����]
	_angRz_Move = 0;
	//�ړ����p��Y����]
	_angRy_Move = 0;

	//Rz���ʈړ����pX�����P�ʃx�N�g�� = 0
//	_vX_Move = 0;

	//Rz���ʈړ����pY�����P�ʃx�N�g�� = 0
//	_vY_Move = 0;

	//�ړ����x
	_iVelocity_Move = 0;

	//�ړ����x��� = 256 px/fream
	_iTopAngVelocity_Move = 256*LEN_UNIT;  //_iVelocity_Move �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B

	//�ړ����x���� = 0   px/fream
	_iBottomVelocity_Move = -256*LEN_UNIT; //_iVelocity_Move �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B

	//�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
	_iAcceleration_MoveVelocity = 0; //_iVelocity_Move �̑����B�f�t�H���g�͉�������

	//Rz���ʈړ����p = 0 angle
	//_angRz_Move = 0;	//0 angle �� �R���̕����Ɉړ�

	//Rz���ʈړ����p�̊p���x = 0 angle/fream
	_angVelocity_MoveAngleRz = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B

	//Rz���ʈړ����p�̊p���x��� = +360,000 angle/fream
	_angTopAngVelocity_MoveAngleRz = ANGLE360;  //_angVelocity_MoveAngleRz �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//Rz���ʈړ����p�̊p���x���� = -360,000 angle/fream
	_angBottomVelocity_MoveAngleRz = ANGLE360*-1; //_angVelocity_MoveAngleRz �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//Rz���ʈړ����p�̊p�����x = 0 angle/fream^2
	_angAcceleration_MoveAngleRzVelocity = 0;     //_angVelocity_MoveAngleRz �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

	//�ڕWRz���ʈړ����p�ւ̎�������t���O = ����
	_auto_move_angle_rz_target_Flg = false;
	//�ڕW��Rz���ʈړ����p
	_angRzTarget_Move = 0;
	//�ڕW��Rz���ʈړ����p������~�@�\���L���ɂȂ��]����
	_auto_move_angle_rz_target_allow_way = TURN_BOTH;
	//�ڕW��Rz���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
	_auto_move_angle_rz_target_allow_velocity = ANGLE180;

	//Rz���ʈړ����p�ɔ���Z����]���p�̓��������@�\�t���O �� ����
	_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

	_iVelocity_ZMove = 0;         //Z��Rz���ʈړ����x�iZ�ړ����W�����j�� 0 px/fream
	_iTopAngVelocity_ZMove = 256*LEN_UNIT;  //Z��Rz���ʈړ����x��� �� 256 px/fream
	_iBottomVelocity_ZMove = -256*LEN_UNIT; //Z��Rz���ʈړ����x���� �� 256 px/fream
	_iAcceleration_ZMoveVelocity = 0;     //Z��Rz���ʈړ����x�̉����x �� 0 px/fream^2  (��������)

}



void StgMover::behave() {

	GgafDx9GeometryMover::behave();

	//Z�������x�̏���
	_iVelocity_ZMove += _iAcceleration_ZMoveVelocity;
	setZMoveVelocity(_iVelocity_ZMove);

	//�����x�̏���
	_iVelocity_Move += _iAcceleration_MoveVelocity;

	setMoveVelocity(_iVelocity_Move);

	//�ڕWRz���ʈړ����p�A���O��������~�@�\�g�p���̏ꍇ
	if (_auto_move_angle_rz_target_Flg) {

		_angVelocity_MoveAngleRz += _angAcceleration_MoveAngleRzVelocity;
		setMoveAngleRzVelocity(_angVelocity_MoveAngleRz);

		if (_angVelocity_MoveAngleRz > 0) { //�����v���̏ꍇ
			angle angDistance = getDistanceFromMoveAngleRzTo(_angRzTarget_Move, TURN_COUNTERCLOCKWISE);
			if (_angVelocity_MoveAngleRz > angDistance &&
				_auto_move_angle_rz_target_allow_way != TURN_CLOCKWISE &&
				_auto_move_angle_rz_target_allow_velocity >= _angVelocity_MoveAngleRz)
			{ //�ڕW���s���߂��Ă��܂���������ȓ�
				addMoveAngleRz(angDistance);
				_auto_move_angle_rz_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addMoveAngleRz(_angVelocity_MoveAngleRz);
			}
		} else if (_angVelocity_MoveAngleRz < 0) { //���v���̏ꍇ

			angle angDistance = getDistanceFromMoveAngleRzTo(_angRzTarget_Move, TURN_CLOCKWISE);
			if (_angVelocity_MoveAngleRz < angDistance &&
				_auto_move_angle_rz_target_allow_way != TURN_COUNTERCLOCKWISE &&
				-1*_auto_move_angle_rz_target_allow_velocity <= _angVelocity_MoveAngleRz)
			{
				addMoveAngleRz(angDistance);
				_auto_move_angle_rz_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addMoveAngleRz(_angVelocity_MoveAngleRz);
			}
		} else {
			//_angVelocity_MoveAngleRz==0
			addMoveAngleRz(0);
		}
		if (_auto_move_angle_rz_target_Flg == false) {
			_angTopAngVelocity_MoveAngleRz = ANGLE360;       //Rz���ʈړ����p�̊p���x��� �� 360,000 angle/fream
			_angBottomVelocity_MoveAngleRz = ANGLE360*-1;  //Rz���ʈړ����p�̊p���x���� �� -360,000 angle/fream
			_angAcceleration_MoveAngleRzVelocity = 0;  //Rz���ʈړ������p�A�p�����x���O��
			setMoveAngleRzVelocity(0);               //Rz���ʈړ������p�A�p���x���O��
		}

	} else {
		//if (_angAcceleration_MoveAngleRzVelocity != 0) {
			//�t���[������Rz���ʈړ����p����̏���
			_angVelocity_MoveAngleRz += _angAcceleration_MoveAngleRzVelocity;
			addMoveAngleRz(_angVelocity_MoveAngleRz);
		//}
	}



	//Actor�ɔ��f
	_pActor->_X += _vX*_iVelocity_Move;
	_pActor->_Y += _vY*_iVelocity_Move;
	_pActor->_Z += (_vZ*_iVelocity_Move + _iVelocity_ZMove);
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

void StgMover::setMoveAngleRz(int prm_tX, int prm_tY) {
	setMoveAngleRz(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setXYZMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
	GgafDx9Util::getRotAngleZY(
			prm_tX - _pActor->_X,
			prm_tY - _pActor->_Y,
			prm_tZ - _pActor->_Z,
			_vX,
			_vY,
			_vZ,
			_angRz_Move,
			_angRy_Move
		);
}

void StgMover::setMoveAngleRz(angle prm_angle) {
	_angRz_Move = simplifyAngle(prm_angle);
	//0�ł����̂��I�I�I���߂�
	GgafDx9Util::getNormalizeVectorZY(_angRz_Move, _angRy_Move, _vX, _vY, _vZ);

	if (_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg) {
		setAxisRotAngle(AXIS_Z, _angRz_Move);
	}
}

void StgMover::setMoveAngleRy(angle prm_angle) {
	_angRy_Move = simplifyAngle(prm_angle);
	//0�ł����̂��I�I�I���߂�
	GgafDx9Util::getNormalizeVectorZY(_angRz_Move, _angRy_Move, _vX, _vY, _vZ);
}


void StgMover::addMoveAngleRz(angle prm_angDistance_MoveAngleRz) {
	angle angOffset_Move = prm_angDistance_MoveAngleRz;
	if (_angBottomVelocity_MoveAngleRz > prm_angDistance_MoveAngleRz) {
		angOffset_Move = _angBottomVelocity_MoveAngleRz;
	} else if (prm_angDistance_MoveAngleRz > _angTopAngVelocity_MoveAngleRz) {
		angOffset_Move = _angTopAngVelocity_MoveAngleRz;
	}
	setMoveAngleRz(_angRz_Move + angOffset_Move);
}

void StgMover::setMoveAngleRzVelocity(angle prm_angVelocity_MoveAngleRz) {
	if (prm_angVelocity_MoveAngleRz > _angTopAngVelocity_MoveAngleRz) {
		_angVelocity_MoveAngleRz = _angTopAngVelocity_MoveAngleRz;
	} else if (prm_angVelocity_MoveAngleRz < _angBottomVelocity_MoveAngleRz) {
		_angVelocity_MoveAngleRz = _angBottomVelocity_MoveAngleRz;
	} else {
		_angVelocity_MoveAngleRz = prm_angVelocity_MoveAngleRz;
	}
}

void StgMover::setMoveAngleRzAcceleration(angle prm_angAcceleration_MoveAngleRzVelocity) {
	_angAcceleration_MoveAngleRzVelocity = prm_angAcceleration_MoveAngleRzVelocity;
}


void StgMover::setMoveAngleRzVelocityRenge(angle prm_angVelocity01_MoveAngleRz, angle prm_angVelocity02_MoveAngleRz) {
	if (prm_angVelocity01_MoveAngleRz < prm_angVelocity02_MoveAngleRz) {
		_angTopAngVelocity_MoveAngleRz = prm_angVelocity02_MoveAngleRz;
		_angBottomVelocity_MoveAngleRz = prm_angVelocity01_MoveAngleRz;
	} else {
		_angTopAngVelocity_MoveAngleRz = prm_angVelocity01_MoveAngleRz;
		_angBottomVelocity_MoveAngleRz = prm_angVelocity02_MoveAngleRz;
	}
	setMoveAngleRzVelocity(_angVelocity_MoveAngleRz); //�Đݒ肵�Ĕ͈͓��ɕ␳
}


void StgMover::setTargetMoveAngleRz(angle prm_angRzTarget_Move, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	_auto_move_angle_rz_target_Flg = true;
	_angRzTarget_Move = simplifyAngle(prm_angRzTarget_Move);
	_auto_move_angle_rz_target_allow_way = prm_iAllowRotWay;
	_auto_move_angle_rz_target_allow_velocity = prm_angAllowVelocity;
}

void StgMover::setTargetMoveAngleRzV(int prm_tX, int prm_tY, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	setTargetMoveAngleRz(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_iAllowRotWay);
}

angle StgMover::getDistanceFromMoveAngleRzTo(int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromMoveAngleRzTo(
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}


angle StgMover::getDistanceFromMoveAngleRzTo(angle prm_angRzTarget_Move, int prm_iWay) {
	angle angTarget_Move = simplifyAngle(prm_angRzTarget_Move);
	if (prm_iWay ==  TURN_CLOSE_TO) { //�߂��ق���]
		if (0 <= _angRz_Move && _angRz_Move < ANGLE180) {
			if (0 <= angTarget_Move && angTarget_Move < _angRz_Move) {
				return -1*(_angRz_Move - angTarget_Move);
			} else if (angTarget_Move == _angRz_Move) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angRz_Move < angTarget_Move && angTarget_Move < _angRz_Move+ANGLE180) {
				return angTarget_Move - _angRz_Move;
			} else if (angTarget_Move == _angRz_Move+ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angRz_Move+ANGLE180 < angTarget_Move && angTarget_Move <= ANGLE360) {
				return -1*(_angRz_Move+(ANGLE360 - angTarget_Move));
			} else {
				//��������
				_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::behave() Rz���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
			}
		} else if(ANGLE180 <= _angRz_Move && _angRz_Move <= ANGLE360) {
			if (0 <= angTarget_Move && angTarget_Move < _angRz_Move-ANGLE180) {
				return ANGLE360 - _angRz_Move + angTarget_Move;
			} else if (angTarget_Move == _angRz_Move-ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angRz_Move-ANGLE180 < angTarget_Move && angTarget_Move < _angRz_Move) {
				return -1*(_angRz_Move - angTarget_Move);
			} else if (_angRz_Move == angTarget_Move) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angRz_Move < angTarget_Move && angTarget_Move <= ANGLE360) {
				return angTarget_Move - _angRz_Move;
			} else {
				//��������
				_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() Rz���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
		if (0 <= _angRz_Move && _angRz_Move < angTarget_Move) {
			return (angTarget_Move - _angRz_Move);
		} else if (angTarget_Move < _angRz_Move && _angRz_Move < ANGLE360) {
			return ANGLE360 - _angRz_Move + angTarget_Move;
		} else if (_angRz_Move == angTarget_Move) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() Rz���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //���v���̏ꍇ
		if (0 <= _angRz_Move && _angRz_Move < angTarget_Move) {
			return -1*( _angRz_Move + ANGLE360 - angTarget_Move);
		} else if (angTarget_Move < _angRz_Move && _angRz_Move < ANGLE360) {
			return -1*(_angRz_Move - angTarget_Move);
		} else if (_angRz_Move == angTarget_Move) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() Rz���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
		}
	}

	_TRACE_("_angRz_Move=" << _angRz_Move << "/angTarget_Move=" << angTarget_Move);
	throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRzTo() ���̂�����p�̋��������߂�܂���B(1)");

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


StgMover::~StgMover() {
}
