#include "stdafx.h"

StgMover::StgMover(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryMover(prm_pActor) {

	//�L�����̈ړ����p�P�ʃx�N�g��
	_vX = _vY = _vZ = 0.0;

	//�ړ����p��Z����]
	_angRz_Move = 0;
	//�ړ����p��Y����]
	_angRy_Move = 0;

	//�ړ����x
	_iVelocity_Move = 0;

	//�ړ����x��� = 256 px/fream
	_iTopAngVelocity_Move = 256*LEN_UNIT;  //_iVelocity_Move �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B

	//�ړ����x���� = 0   px/fream
	_iBottomVelocity_Move = -256*LEN_UNIT; //_iVelocity_Move �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B

	//�ړ������x�i�ړ����x�̑����j = 0 px/fream^2
	_iAcceleration_MoveVelocity = 0; //_iVelocity_Move �̑����B�f�t�H���g�͉�������

/////�R�s�[��begin

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
////�R�s�[��end

/////�R�s�[��begin

	//Ry���ʈړ����p�̊p���x = 0 angle/fream
	_angVelocity_MoveAngleRy = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B

	//Ry���ʈړ����p�̊p���x��� = +360,000 angle/fream
	_angTopAngVelocity_MoveAngleRy = ANGLE360;  //_angVelocity_MoveAngleRy �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//Ry���ʈړ����p�̊p���x���� = -360,000 angle/fream
	_angBottomVelocity_MoveAngleRy = ANGLE360*-1; //_angVelocity_MoveAngleRy �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//Ry���ʈړ����p�̊p�����x = 0 angle/fream^2
	_angAcceleration_MoveAngleRyVelocity = 0;     //_angVelocity_MoveAngleRy �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

	//�ڕWRy���ʈړ����p�ւ̎�������t���O = ����
	_auto_move_angle_ry_target_Flg = false;
	//�ڕW��Ry���ʈړ����p
	_angRyTarget_Move = 0;
	//�ڕW��Ry���ʈړ����p������~�@�\���L���ɂȂ��]����
	_auto_move_angle_ry_target_allow_way = TURN_BOTH;
	//�ڕW��Ry���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x(�p���x��������)
	_auto_move_angle_ry_target_allow_velocity = ANGLE180;

	//Ry���ʈړ����p�ɔ���Z����]���p�̓��������@�\�t���O �� ����
	_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B
////�R�s�[��end

	_iVelocity_XMove = 0;         //X�������ړ����x�iX�ړ����W�����j�� 0 px/fream
	_iTopAngVelocity_XMove = 256*LEN_UNIT;  //X�������ړ����x��� �� 256 px/fream
	_iBottomVelocity_XMove = -256*LEN_UNIT; //X�������ړ����x���� �� 256 px/fream
	_iAcceleration_XMoveVelocity = 0;     //X�������ړ����x�̉����x �� 0 px/fream^2  (��������)

	_iVelocity_YMove = 0;         //Y�������ړ����x�iY�ړ����W�����j�� 0 px/fream
	_iTopAngVelocity_YMove = 256*LEN_UNIT;  //Y�������ړ����x��� �� 256 px/fream
	_iBottomVelocity_YMove = -256*LEN_UNIT; //Y�������ړ����x���� �� 256 px/fream
	_iAcceleration_YMoveVelocity = 0;     //Y�������ړ����x�̉����x �� 0 px/fream^2  (��������)

	_iVelocity_ZMove = 0;         //Z�������ړ����x�iZ�ړ����W�����j�� 0 px/fream
	_iTopAngVelocity_ZMove = 256*LEN_UNIT;  //Z�������ړ����x��� �� 256 px/fream
	_iBottomVelocity_ZMove = -256*LEN_UNIT; //Z�������ړ����x���� �� 256 px/fream
	_iAcceleration_ZMoveVelocity = 0;     //Z�������ړ����x�̉����x �� 0 px/fream^2  (��������)

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


////�R�s�[��begin

void StgMover::setMoveAngleRz(int prm_tX, int prm_tY) {
	setMoveAngleRz(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setMoveAngleRz(angle prm_angle) {
	_angRz_Move = simplifyAngle(prm_angle);
	GgafDx9Util::getNormalizeVectorZY(_angRz_Move, _angRy_Move, _vX, _vY, _vZ);
	if (_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg) {
		setAxisRotAngle(AXIS_Z, _angRz_Move);
	}
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

////�R�s�[��end

////�R�s�[��begin

void StgMover::setMoveAngleRy(int prm_tX, int prm_tY) {
	setMoveAngleRy(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setMoveAngleRy(angle prm_angle) {
	_angRy_Move = simplifyAngle(prm_angle);
	GgafDx9Util::getNormalizeVectorZY(_angRz_Move, _angRy_Move, _vX, _vY, _vZ);
	if (_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg) {
		setAxisRotAngle(AXIS_Y, _angRy_Move);
	}
}

void StgMover::addMoveAngleRy(angle prm_angDistance_MoveAngleRy) {
	angle angOffset_Move = prm_angDistance_MoveAngleRy;
	if (_angBottomVelocity_MoveAngleRy > prm_angDistance_MoveAngleRy) {
		angOffset_Move = _angBottomVelocity_MoveAngleRy;
	} else if (prm_angDistance_MoveAngleRy > _angTopAngVelocity_MoveAngleRy) {
		angOffset_Move = _angTopAngVelocity_MoveAngleRy;
	}
	setMoveAngleRy(_angRy_Move + angOffset_Move);
}

void StgMover::setMoveAngleRyVelocity(angle prm_angVelocity_MoveAngleRy) {
	if (prm_angVelocity_MoveAngleRy > _angTopAngVelocity_MoveAngleRy) {
		_angVelocity_MoveAngleRy = _angTopAngVelocity_MoveAngleRy;
	} else if (prm_angVelocity_MoveAngleRy < _angBottomVelocity_MoveAngleRy) {
		_angVelocity_MoveAngleRy = _angBottomVelocity_MoveAngleRy;
	} else {
		_angVelocity_MoveAngleRy = prm_angVelocity_MoveAngleRy;
	}
}

void StgMover::setMoveAngleRyAcceleration(angle prm_angAcceleration_MoveAngleRyVelocity) {
	_angAcceleration_MoveAngleRyVelocity = prm_angAcceleration_MoveAngleRyVelocity;
}

void StgMover::setMoveAngleRyVelocityRenge(angle prm_angVelocity01_MoveAngleRy, angle prm_angVelocity02_MoveAngleRy) {
	if (prm_angVelocity01_MoveAngleRy < prm_angVelocity02_MoveAngleRy) {
		_angTopAngVelocity_MoveAngleRy = prm_angVelocity02_MoveAngleRy;
		_angBottomVelocity_MoveAngleRy = prm_angVelocity01_MoveAngleRy;
	} else {
		_angTopAngVelocity_MoveAngleRy = prm_angVelocity01_MoveAngleRy;
		_angBottomVelocity_MoveAngleRy = prm_angVelocity02_MoveAngleRy;
	}
	setMoveAngleRyVelocity(_angVelocity_MoveAngleRy); //�Đݒ肵�Ĕ͈͓��ɕ␳
}


void StgMover::setTargetMoveAngleRy(angle prm_angRyTarget_Move, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	_auto_move_angle_ry_target_Flg = true;
	_angRyTarget_Move = simplifyAngle(prm_angRyTarget_Move);
	_auto_move_angle_ry_target_allow_way = prm_iAllowRotWay;
	_auto_move_angle_ry_target_allow_velocity = prm_angAllowVelocity;
}

void StgMover::setTargetMoveAngleRyV(int prm_tX, int prm_tY, int prm_iAllowRotWay, angle prm_angAllowVelocity) {
	setTargetMoveAngleRy(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)), prm_iAllowRotWay);
}

angle StgMover::getDistanceFromMoveAngleRyTo(int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromMoveAngleRyTo(
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}

angle StgMover::getDistanceFromMoveAngleRyTo(angle prm_angRyTarget_Move, int prm_iWay) {
	angle angTarget_Move = simplifyAngle(prm_angRyTarget_Move);
	if (prm_iWay ==  TURN_CLOSE_TO) { //�߂��ق���]
		if (0 <= _angRy_Move && _angRy_Move < ANGLE180) {
			if (0 <= angTarget_Move && angTarget_Move < _angRy_Move) {
				return -1*(_angRy_Move - angTarget_Move);
			} else if (angTarget_Move == _angRy_Move) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angRy_Move < angTarget_Move && angTarget_Move < _angRy_Move+ANGLE180) {
				return angTarget_Move - _angRy_Move;
			} else if (angTarget_Move == _angRy_Move+ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angRy_Move+ANGLE180 < angTarget_Move && angTarget_Move <= ANGLE360) {
				return -1*(_angRy_Move+(ANGLE360 - angTarget_Move));
			} else {
				//��������
				_TRACE_("_angRy_Move=" << _angRy_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::behave() Ry���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
			}
		} else if(ANGLE180 <= _angRy_Move && _angRy_Move <= ANGLE360) {
			if (0 <= angTarget_Move && angTarget_Move < _angRy_Move-ANGLE180) {
				return ANGLE360 - _angRy_Move + angTarget_Move;
			} else if (angTarget_Move == _angRy_Move-ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angRy_Move-ANGLE180 < angTarget_Move && angTarget_Move < _angRy_Move) {
				return -1*(_angRy_Move - angTarget_Move);
			} else if (_angRy_Move == angTarget_Move) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angRy_Move < angTarget_Move && angTarget_Move <= ANGLE360) {
				return angTarget_Move - _angRy_Move;
			} else {
				//��������
				_TRACE_("_angRy_Move=" << _angRy_Move << "/angTarget_Move=" << angTarget_Move);
				throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRyTo() Ry���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
		if (0 <= _angRy_Move && _angRy_Move < angTarget_Move) {
			return (angTarget_Move - _angRy_Move);
		} else if (angTarget_Move < _angRy_Move && _angRy_Move < ANGLE360) {
			return ANGLE360 - _angRy_Move + angTarget_Move;
		} else if (_angRy_Move == angTarget_Move) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angRy_Move=" << _angRy_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRyTo() Ry���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //���v���̏ꍇ
		if (0 <= _angRy_Move && _angRy_Move < angTarget_Move) {
			return -1*( _angRy_Move + ANGLE360 - angTarget_Move);
		} else if (angTarget_Move < _angRy_Move && _angRy_Move < ANGLE360) {
			return -1*(_angRy_Move - angTarget_Move);
		} else if (_angRy_Move == angTarget_Move) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angRy_Move=" << _angRy_Move << "/angTarget_Move=" << angTarget_Move);
			throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRyTo() Ry���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
		}
	}

	_TRACE_("_angRy_Move=" << _angRy_Move << "/angTarget_Move=" << angTarget_Move);
	throw_GgafCriticalException("StgMover::getDistanceFromMoveAngleRyTo() ���̂�����p�̋��������߂�܂���B(1)");

}

////�R�s�[��end




void StgMover::setMoveAngle(int prm_tX, int prm_tY, int prm_tZ) {
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


void StgMover::setXMoveVelocityRenge(int prm_iVelocity01_XMove, int prm_iVelocity02_XMove) {
	if (prm_iVelocity01_XMove < prm_iVelocity02_XMove) {
		_iTopAngVelocity_XMove = prm_iVelocity02_XMove;
		_iBottomVelocity_XMove = prm_iVelocity01_XMove;
	} else {
		_iTopAngVelocity_XMove = prm_iVelocity01_XMove;
		_iBottomVelocity_XMove = prm_iVelocity02_XMove;
	}
	setXMoveVelocity(_iVelocity_XMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void StgMover::setXMoveVelocity(int prm_iVelocity_XMove) {
	if (prm_iVelocity_XMove > _iTopAngVelocity_XMove) {
		_iVelocity_XMove = _iTopAngVelocity_XMove;
	} else if (prm_iVelocity_XMove < _iBottomVelocity_XMove) {
		_iVelocity_XMove = _iBottomVelocity_XMove;
	} else {
		_iVelocity_XMove = prm_iVelocity_XMove;
	}
}

void StgMover::setXMoveAcceleration(int prm_iAcceleration_XMoveVelocity) {
	_iAcceleration_XMoveVelocity = prm_iAcceleration_XMoveVelocity;
}

void StgMover::setYMoveVelocityRenge(int prm_iVelocity01_YMove, int prm_iVelocity02_YMove) {
	if (prm_iVelocity01_YMove < prm_iVelocity02_YMove) {
		_iTopAngVelocity_YMove = prm_iVelocity02_YMove;
		_iBottomVelocity_YMove = prm_iVelocity01_YMove;
	} else {
		_iTopAngVelocity_YMove = prm_iVelocity01_YMove;
		_iBottomVelocity_YMove = prm_iVelocity02_YMove;
	}
	setYMoveVelocity(_iVelocity_YMove); //�Đݒ肵�Ĕ͈͓��ɕ␳
}

void StgMover::setYMoveVelocity(int prm_iVelocity_YMove) {
	if (prm_iVelocity_YMove > _iTopAngVelocity_YMove) {
		_iVelocity_YMove = _iTopAngVelocity_YMove;
	} else if (prm_iVelocity_YMove < _iBottomVelocity_YMove) {
		_iVelocity_YMove = _iBottomVelocity_YMove;
	} else {
		_iVelocity_YMove = prm_iVelocity_YMove;
	}
}

void StgMover::setYMoveAcceleration(int prm_iAcceleration_YMoveVelocity) {
	_iAcceleration_YMoveVelocity = prm_iAcceleration_YMoveVelocity;
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



void StgMover::behave() {

	GgafDx9GeometryMover::behave();

	//X�������ړ������x�̏���
	_iVelocity_XMove += _iAcceleration_XMoveVelocity;
	setXMoveVelocity(_iVelocity_XMove);
	//Y�������ړ������x�̏���
	_iVelocity_YMove += _iAcceleration_YMoveVelocity;
	setYMoveVelocity(_iVelocity_YMove);
	//Z�������ړ������x�̏���
	_iVelocity_ZMove += _iAcceleration_ZMoveVelocity;
	setZMoveVelocity(_iVelocity_ZMove);

	//�ړ������x�̏���
	_iVelocity_Move += _iAcceleration_MoveVelocity;
	setMoveVelocity(_iVelocity_Move);
///////////
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
////////////////
	//�ڕWRy���ʈړ����p�A���O��������~�@�\�g�p���̏ꍇ
	if (_auto_move_angle_ry_target_Flg) {

		_angVelocity_MoveAngleRy += _angAcceleration_MoveAngleRyVelocity;
		setMoveAngleRyVelocity(_angVelocity_MoveAngleRy);

		if (_angVelocity_MoveAngleRy > 0) { //�����v���̏ꍇ
			angle angDistance = getDistanceFromMoveAngleRyTo(_angRyTarget_Move, TURN_COUNTERCLOCKWISE);
			if (_angVelocity_MoveAngleRy > angDistance &&
				_auto_move_angle_ry_target_allow_way != TURN_CLOCKWISE &&
				_auto_move_angle_ry_target_allow_velocity >= _angVelocity_MoveAngleRy)
			{ //�ڕW���s���߂��Ă��܂���������ȓ�
				addMoveAngleRy(angDistance);
				_auto_move_angle_ry_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addMoveAngleRy(_angVelocity_MoveAngleRy);
			}
		} else if (_angVelocity_MoveAngleRy < 0) { //���v���̏ꍇ

			angle angDistance = getDistanceFromMoveAngleRyTo(_angRyTarget_Move, TURN_CLOCKWISE);
			if (_angVelocity_MoveAngleRy < angDistance &&
				_auto_move_angle_ry_target_allow_way != TURN_COUNTERCLOCKWISE &&
				-1*_auto_move_angle_ry_target_allow_velocity <= _angVelocity_MoveAngleRy)
			{
				addMoveAngleRy(angDistance);
				_auto_move_angle_ry_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addMoveAngleRy(_angVelocity_MoveAngleRy);
			}
		} else {
			//_angVelocity_MoveAngleRy==0
			addMoveAngleRy(0);
		}
		if (_auto_move_angle_ry_target_Flg == false) {
			_angTopAngVelocity_MoveAngleRy = ANGLE360;       //Ry���ʈړ����p�̊p���x��� �� 360,000 angle/fream
			_angBottomVelocity_MoveAngleRy = ANGLE360*-1;  //Ry���ʈړ����p�̊p���x���� �� -360,000 angle/fream
			_angAcceleration_MoveAngleRyVelocity = 0;  //Ry���ʈړ������p�A�p�����x���O��
			setMoveAngleRyVelocity(0);               //Ry���ʈړ������p�A�p���x���O��
		}

	} else {
		//if (_angAcceleration_MoveAngleRyVelocity != 0) {
			//�t���[������Ry���ʈړ����p����̏���
			_angVelocity_MoveAngleRy += _angAcceleration_MoveAngleRyVelocity;
			addMoveAngleRy(_angVelocity_MoveAngleRy);
		//}
	}
///////////////

	//Actor�ɔ��f
	_pActor->_X += (_vX*_iVelocity_Move + _iVelocity_XMove);
	_pActor->_Y += (_vY*_iVelocity_Move + _iVelocity_YMove);
	_pActor->_Z += (_vZ*_iVelocity_Move + _iVelocity_ZMove);
}



StgMover::~StgMover() {
}
