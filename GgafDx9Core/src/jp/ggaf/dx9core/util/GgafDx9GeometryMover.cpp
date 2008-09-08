#include "stdafx.h"

GgafDx9GeometryMover::GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor) {
	_pActor = prm_pActor;

	for (int i = 0; i < 3; i++) { // i=0:X���A1:Y���A2:Z�� ��\��

		//����]���p
		_angAxisRot[i] = 0; //0 angle �� �R���̕��p�������Ă���

		//����]���p�̊p���x�i����]���p�l�̑����j= 0 angle/fream
		_angVelocity_AxisRotAngle[i]  = 0; //1�t���[���ɉ��Z����鎲��]���p�̊p�����B�f�t�H���g�͎���]���p�̊p���������A�܂�U����������B

		//����]���p�̊p���x��� �� 360,000 angle/fream
		_angTopVelocity_AxisRotAngle[i]  = ANGLE360; //_angVelocity_AxisRotAngle[n] �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����

		//����]���p�̊p���x���� �� -360,000 angle/fream
		_angBottomVelocity_AxisRotAngle[i]  = ANGLE360*-1;  //_angVelocity_AxisRotAngle[n] �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȏ���]���p�ɐU����������o���鎖���Ӗ�����

		//����]���p�̊p�����x�i�p���x�̑����j �� 0 angle/fream^2
		_angAcceleration_AxisRotAngleVelocity[i]  = 0; //_angVelocity_AxisRotAngle[n] �̑����B�f�t�H���g�͎���]���p�̊p�����x����

		//�ڕW����]���p�ւ̎�������t���O = ����
		_auto_rot_angle_target_Flg[i] = false;

		//�ڕW�̎���]���p
		_angTarget_AxisRot[i] = 0; //�ڕW����]���p�ւ̎�������t���O = �����A�̏ꍇ�͖��Ӗ�
	}

}

void GgafDx9GeometryMover::behave() {
	static angle angDistance;
	for (int i = 0; i < 3; i++) {
		if (_auto_rot_angle_target_Flg[i]) {
			_angVelocity_AxisRotAngle[i] += _angAcceleration_AxisRotAngleVelocity[i];
			setAxisRotAngleVelocity(i, _angVelocity_AxisRotAngle[i]);

			if (_angVelocity_AxisRotAngle[i] > 0) { //�����v���̏ꍇ
				angDistance = getDistanceFromAxisRotAngleTo(i, _angTarget_AxisRot[i], TURN_COUNTERCLOCKWISE);
				if (_angVelocity_AxisRotAngle[i] > angDistance) { //�ڕW���s���߂��Ă��܂���������ȓ�
					addAxisRotAngle(i, angDistance);
					_auto_rot_angle_target_Flg[i] = false; //�t���O��߂��ďI��
				} else {
					addAxisRotAngle(i, _angVelocity_AxisRotAngle[i]);
				}
			} else if (_angVelocity_AxisRotAngle[i] < 0) { //���v���̏ꍇ
				angDistance = getDistanceFromAxisRotAngleTo(i, _angTarget_AxisRot[i], TURN_CLOCKWISE);
				if (_angVelocity_AxisRotAngle[i] < angDistance) { //�ڕW���s���߂��Ă��܂���������ȓ�
					addAxisRotAngle(i, angDistance);
					_auto_rot_angle_target_Flg[i] = false; //�t���O��߂��ďI��
				} else {
					addAxisRotAngle(i, _angVelocity_AxisRotAngle[i]);
				}
			} else {
				//_angVelocity_AxisRotAngle[i] == 0
				addAxisRotAngle(i, 0);
			}
			if (_auto_rot_angle_target_Flg[i] == false) {
				//�ڕW�����ɓ��B�������̏���
				_angTopVelocity_AxisRotAngle[i]  = ANGLE360;  //����]���p�̊p���x��� �� 360,000 angle/fream
				_angBottomVelocity_AxisRotAngle[i]  = ANGLE360*-1;  //����]���p�̊p���x���� �� -360,000 angle/fream
				_angAcceleration_AxisRotAngleVelocity[i] = 0;    //����]�����p�A�p���x���O��
				setAxisRotAngleVelocity(i, 0);                //����]�����p�A�p�����x���O��
			}

		} else {
			//�t���[������XY���ʈړ����p����̏���
			_angVelocity_AxisRotAngle[i] += _angAcceleration_AxisRotAngleVelocity[i];
			addAxisRotAngle(i, _angVelocity_AxisRotAngle[i]);
		}
	}

	//Actor�ɔ��f
	_pActor->_RX = _angAxisRot[AXIS_X];
	_pActor->_RY = _angAxisRot[AXIS_Y];
	_pActor->_RZ = _angAxisRot[AXIS_Z];

}




void GgafDx9GeometryMover::setAxisRotAngle(int prm_iAxis, angle prm_angAxisRot) {
	angle angSimple = prm_angAxisRot;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_angAxisRot[prm_iAxis] = angSimple;
}

void GgafDx9GeometryMover::addAxisRotAngle(int prm_iAxis, angle prm_angDistance_AxisRotAngle) {
	angle angOffsetrot_AxisRotAngle = prm_angDistance_AxisRotAngle;
	if (_angBottomVelocity_AxisRotAngle[prm_iAxis] > prm_angDistance_AxisRotAngle) {
		angOffsetrot_AxisRotAngle = _angBottomVelocity_AxisRotAngle[prm_iAxis];
	} else if (prm_angDistance_AxisRotAngle > _angTopVelocity_AxisRotAngle[prm_iAxis]) {
		angOffsetrot_AxisRotAngle = _angTopVelocity_AxisRotAngle[prm_iAxis];
	}
	setAxisRotAngle(prm_iAxis, _angAxisRot[prm_iAxis] + angOffsetrot_AxisRotAngle);
}

void GgafDx9GeometryMover::setAxisRotAngleVelocity(int prm_iAxis, angle prm_angVelocity_AxisRotAngle) {
	if (prm_angVelocity_AxisRotAngle > _angTopVelocity_AxisRotAngle[prm_iAxis]) {
		_angVelocity_AxisRotAngle[prm_iAxis] = _angTopVelocity_AxisRotAngle[prm_iAxis];
	} else if (prm_angVelocity_AxisRotAngle < _angBottomVelocity_AxisRotAngle[prm_iAxis]) {
		_angVelocity_AxisRotAngle[prm_iAxis] = _angBottomVelocity_AxisRotAngle[prm_iAxis];
	} else {
		_angVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity_AxisRotAngle;
	}
}

void GgafDx9GeometryMover::setAxisRotAngleVelocityRenge(int prm_iAxis, angle prm_angVelocity01_AxisRotAngle, angle prm_angVelocity02_AxisRotAngle) {
	if (prm_angVelocity01_AxisRotAngle < prm_angVelocity02_AxisRotAngle) {
		_angTopVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity02_AxisRotAngle;
		_angBottomVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity01_AxisRotAngle;
	} else {
		_angTopVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity01_AxisRotAngle;
		_angBottomVelocity_AxisRotAngle[prm_iAxis] = prm_angVelocity02_AxisRotAngle;
	}
}

void GgafDx9GeometryMover::setAxisRotAngleAcceleration(int prm_iAxis, angle prm_angAcceleration_AxisRotAngleVelocity) {
	_angAcceleration_AxisRotAngleVelocity[prm_iAxis] = prm_angAcceleration_AxisRotAngleVelocity;
}

void GgafDx9GeometryMover::setTargetAxisRotAngle(int prm_iAxis, int prm_tX, int prm_tY) {
	setTargetAxisRotAngle(prm_iAxis, _angTarget_AxisRot[prm_iAxis] = GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}








void GgafDx9GeometryMover::setTargetAxisRotAngle(int prm_iAxis, angle prm_angTarget_AxisRot) {
	angle angSimple = prm_angTarget_AxisRot;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_auto_rot_angle_target_Flg[prm_iAxis] = true;
	//_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg = false;
	_angTarget_AxisRot[prm_iAxis] = angSimple;
}


angle GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo(int prm_iAxis, int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromAxisRotAngleTo(
			   prm_iAxis,
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}

angle GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo(int prm_iAxis, angle prm_angTarget_AxisRot, int prm_iWay) {
	if (prm_iWay == TURN_CLOSE_TO) { //�߂��ق���]
		if (0 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < ANGLE180) {
			if (0 <= prm_angTarget_AxisRot && prm_angTarget_AxisRot < _angAxisRot[prm_iAxis]) {
				return -1*(_angAxisRot[prm_iAxis] - prm_angTarget_AxisRot);
			} else if (prm_angTarget_AxisRot == _angAxisRot[prm_iAxis]) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angAxisRot[prm_iAxis] < prm_angTarget_AxisRot && prm_angTarget_AxisRot < _angAxisRot[prm_iAxis]+ANGLE180) {
				return prm_angTarget_AxisRot - _angAxisRot[prm_iAxis];
			} else if (prm_angTarget_AxisRot == _angAxisRot[prm_iAxis]+ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angAxisRot[prm_iAxis]+ANGLE180 < prm_angTarget_AxisRot && prm_angTarget_AxisRot <= ANGLE360) {
				return -1*(_angAxisRot[prm_iAxis]+(ANGLE360 - prm_angTarget_AxisRot));
			} else {
				//��������
				_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/prm_angTarget_AxisRot=" << prm_angTarget_AxisRot);
				throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
			}
		} else if(ANGLE180 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] <= ANGLE360) {
			if (0 <= prm_angTarget_AxisRot && prm_angTarget_AxisRot < _angAxisRot[prm_iAxis]-ANGLE180) {
				return ANGLE360 - _angAxisRot[prm_iAxis] + prm_angTarget_AxisRot;
			} else if (prm_angTarget_AxisRot == _angAxisRot[prm_iAxis]-ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angAxisRot[prm_iAxis]-ANGLE180 < prm_angTarget_AxisRot && prm_angTarget_AxisRot < _angAxisRot[prm_iAxis]) {
				return -1*(_angAxisRot[prm_iAxis] - prm_angTarget_AxisRot);
			} else if (_angAxisRot[prm_iAxis] == prm_angTarget_AxisRot) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angAxisRot[prm_iAxis] < prm_angTarget_AxisRot && prm_angTarget_AxisRot <= ANGLE360) {
				return prm_angTarget_AxisRot - _angAxisRot[prm_iAxis];
			} else {
				//��������
				_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/prm_angTarget_AxisRot=" << prm_angTarget_AxisRot);
				throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
		if (0 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < prm_angTarget_AxisRot) {
			return (prm_angTarget_AxisRot - _angAxisRot[prm_iAxis]);
		} else if (prm_angTarget_AxisRot < _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < ANGLE360) {
			return ANGLE360 - _angAxisRot[prm_iAxis] + prm_angTarget_AxisRot;
		} else if (_angAxisRot[prm_iAxis] == prm_angTarget_AxisRot) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/prm_angTarget_AxisRot=" << prm_angTarget_AxisRot);
			throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //���v���̏ꍇ
		if (0 <= _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < prm_angTarget_AxisRot) {
			return -1*( _angAxisRot[prm_iAxis] + ANGLE360 - prm_angTarget_AxisRot);
		} else if (prm_angTarget_AxisRot < _angAxisRot[prm_iAxis] && _angAxisRot[prm_iAxis] < ANGLE360) {
			return -1*(_angAxisRot[prm_iAxis] - prm_angTarget_AxisRot);
		} else if (_angAxisRot[prm_iAxis] == prm_angTarget_AxisRot) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/prm_angTarget_AxisRot=" << prm_angTarget_AxisRot);
			throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
		}
	}
	_TRACE_("_angAxisRot["<<prm_iAxis<<"]=" << _angAxisRot[prm_iAxis] << "/prm_angTarget_AxisRot=" << prm_angTarget_AxisRot);
	throw_GgafCriticalException("GgafDx9GeometryMover::getDistanceFromAxisRotAngleTo() ���̂�����p�̋��������߂�܂���B(2)");
}

GgafDx9GeometryMover::~GgafDx9GeometryMover() {
}
