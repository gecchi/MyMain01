#include "stdafx.h"

StgMover::StgMover(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryMover(prm_pActor) {

	//XY���ʈړ����pX�����P�ʃx�N�g�� = 0
	_vX_XYMove = 0;

	//XY���ʈړ����pY�����P�ʃx�N�g�� = 0
	_vY_XYMove = 0;

	//XY���ʈړ����x�iXY���ʈړ����W�����j = 1 px/fream
	_iVelocity_XYMove = LEN_UNIT;  //1�t���[����LEN_UNIT(��1px)�i��

	//XY���ʈړ����x��� = 256 px/fream
	_iTopVelocity_XYMove = 256*LEN_UNIT;  //_iVelocity_XYMove �� 256000(=256px) ������ړ��ʂł����Ă��A�����I�ɍ��W������ 256px �ɗ}������B

	//XY���ʈړ����x���� = 0   px/fream
	_iBottomVelocity_XYMove = -256*LEN_UNIT; //_iVelocity_XYMove �� -256000(-256px) �������ړ��ʂ������Ă��A�����I�ɍ��W������ -256000px �ɗ}������B

	//XY���ʈړ������x�iXY���ʈړ����x�̑����j = 0 px/fream^2
	_iAcceleration_XYMoveVelocity = 0; //_iVelocity_XYMove �̑����B�f�t�H���g�͉�������

	//XY���ʈړ����p = 0 angle
	_angXYMove = 0;	//0 angle �� �R���̕����Ɉړ�

	//XY���ʈړ����p�̊p���x = 0 angle/fream
	_angVelocity_XYMoveAngle = 0; //1�t���[���ɉ��Z�����ړ����p�̊p�����B�f�t�H���g�͈ړ����p�̊p���������A�܂蒼���ړ��B

	//XY���ʈړ����p�̊p���x��� = +360,000 angle/fream
	_angTopVelocity_XYMoveAngle = ANGLE360;  //_angVelocity_XYMoveAngle �̑����̏���B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//XY���ʈړ����p�̊p���x���� = -360,000 angle/fream
	_angBottomVelocity_XYMoveAngle = ANGLE360*-1; //_angVelocity_XYMoveAngle �̑����̉����B�f�t�H���g��1�t���[���ōD���Ȉړ������ɕύX���o���鎖���Ӗ�����

	//XY���ʈړ����p�̊p�����x = 0 angle/fream^2
	_angAcceleration_XYMoveAngleVelocity = 0;     //_angVelocity_XYMoveAngle �̑����B�f�t�H���g�͈ړ����p�̊p�����x����

	//�ڕWXY���ʈړ����p�ւ̎�������t���O = ����
	_auto_xymove_angle_target_Flg = false;
	//�ڕW��XY���ʈړ����p
	_angTarget_XYMove = 0;


	//XY���ʈړ����p�ɔ���Z����]���p�̓��������@�\�t���O �� ����
	_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg = false; //�L���̏ꍇ�́A�ړ����p��ݒ肷���Z����]���p�������ɂȂ�B

	_iVelocity_ZMove = 0;         //Z��XY���ʈړ����x�iZ�ړ����W�����j�� 0 px/fream
	_iTopVelocity_ZMove = 256*LEN_UNIT;  //Z��XY���ʈړ����x��� �� 256 px/fream
	_iBottomVelocity_ZMove = -256*LEN_UNIT; //Z��XY���ʈړ����x���� �� 256 px/fream
	_iAcceleration_ZMoveVelocity = 0;     //Z��XY���ʈړ����x�̉����x �� 0 px/fream^2  (��������)

}



void StgMover::behave() {

	GgafDx9GeometryMover::behave();

	//Z�������x�̏���
	_iVelocity_ZMove += _iAcceleration_ZMoveVelocity;
	setZMoveVelocity(_iVelocity_ZMove);


	//�����x�̏���
	_iVelocity_XYMove += _iAcceleration_XYMoveVelocity;

	setXYMoveVelocity(_iVelocity_XYMove);

	//�ڕWXY���ʈړ����p�A���O����������@�\�g�p���̏ꍇ
	if (_auto_xymove_angle_target_Flg) {

		_angVelocity_XYMoveAngle += _angAcceleration_XYMoveAngleVelocity;
		setXYMoveAngleVelocity(_angVelocity_XYMoveAngle);

		if (_angVelocity_XYMoveAngle > 0) { //�����v���̏ꍇ
			angle angDistance = getDistanceFromXYMoveAngleTo(_angTarget_XYMove, TURN_COUNTERCLOCKWISE);
			if (_angVelocity_XYMoveAngle > angDistance) { //�ڕW���s���߂��Ă��܂���������ȓ�
				addXYMoveAngle(angDistance);
				_auto_xymove_angle_target_Flg = false; //�t���O��߂��ďI��
			} else {
				addXYMoveAngle(_angVelocity_XYMoveAngle);
			}
		} else if (_angVelocity_XYMoveAngle < 0) { //���v���̏ꍇ

			angle angDistance = getDistanceFromXYMoveAngleTo(_angTarget_XYMove, TURN_CLOCKWISE);
			if (_angVelocity_XYMoveAngle < angDistance) {
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
			_angTopVelocity_XYMoveAngle = ANGLE360;       //XY���ʈړ����p�̊p���x��� �� 360,000 angle/fream
			_angBottomVelocity_XYMoveAngle = ANGLE360*-1;  //XY���ʈړ����p�̊p���x���� �� -360,000 angle/fream
			_angAcceleration_XYMoveAngleVelocity = 0;  //XY���ʈړ������p�A�p�����x���O��
			setXYMoveAngleVelocity(0);               //XY���ʈړ������p�A�p���x���O��
		}

	} else {
		//�t���[������XY���ʈړ����p����̏���
		_angVelocity_XYMoveAngle += _angAcceleration_XYMoveAngleVelocity;
		addXYMoveAngle(_angVelocity_XYMoveAngle);
	}



	//Actor�ɔ��f
	_pActor->_X += _vX_XYMove*_iVelocity_XYMove/LEN_UNIT;
	_pActor->_Y += _vY_XYMove*_iVelocity_XYMove/LEN_UNIT;
	_pActor->_Z += _iVelocity_ZMove;
}



void StgMover::setXYMoveVelocityRenge(int prm_iVelocity01_XYMove, int prm_iVelocity02_XYMove) {
	if (prm_iVelocity01_XYMove < prm_iVelocity02_XYMove) {
		_iTopVelocity_XYMove = prm_iVelocity02_XYMove;
		_iBottomVelocity_XYMove = prm_iVelocity01_XYMove;
	} else {
		_iTopVelocity_XYMove = prm_iVelocity01_XYMove;
		_iBottomVelocity_XYMove = prm_iVelocity02_XYMove;
	}
}



void StgMover::setXYMoveVelocity(int prm_iVelocity_XYMove) {
	if (prm_iVelocity_XYMove > _iTopVelocity_XYMove) {
		_iVelocity_XYMove = _iTopVelocity_XYMove;
	} else if (prm_iVelocity_XYMove < _iBottomVelocity_XYMove) {
		_iVelocity_XYMove = _iBottomVelocity_XYMove;
	} else {
		_iVelocity_XYMove = prm_iVelocity_XYMove;
	}
}

void StgMover::setXYMoveAcceleration(int prm_iAcceleration_XYMoveVelocity) {
	_iAcceleration_XYMoveVelocity = prm_iAcceleration_XYMoveVelocity;
}

void StgMover::setXYMoveAngle(int prm_tX, int prm_tY) {
	setXYMoveAngle(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

void StgMover::setXYMoveAngle(angle prm_angXYMove) {
	int angSimple = prm_angXYMove;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_angXYMove = angSimple;
	_vX_XYMove = GgafDx9Util::_aCos_UnitLen[angSimple];
	_vY_XYMove = GgafDx9Util::_aSin_UnitLen[angSimple];
	if (_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg) {
		setAxisRotAngle(AXIS_Z, angSimple);
	}
}

void StgMover::addXYMoveAngle(angle prm_angDistance_XYMoveAngle) {
	angle angOffset_XYMove = prm_angDistance_XYMoveAngle;
	if (_angBottomVelocity_XYMoveAngle > prm_angDistance_XYMoveAngle) {
		angOffset_XYMove = _angBottomVelocity_XYMoveAngle;
	} else if (prm_angDistance_XYMoveAngle > _angTopVelocity_XYMoveAngle) {
		angOffset_XYMove = _angTopVelocity_XYMoveAngle;
	}
	setXYMoveAngle(_angXYMove + angOffset_XYMove);
}

void StgMover::setXYMoveAngleVelocity(angle prm_angVelocity_XYMoveAngle) {
	if (prm_angVelocity_XYMoveAngle > _angTopVelocity_XYMoveAngle) {
		_angVelocity_XYMoveAngle = _angTopVelocity_XYMoveAngle;
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
		_angTopVelocity_XYMoveAngle = prm_angVelocity02_XYMoveAngle;
		_angBottomVelocity_XYMoveAngle = prm_angVelocity01_XYMoveAngle;
	} else {
		_angTopVelocity_XYMoveAngle = prm_angVelocity01_XYMoveAngle;
		_angBottomVelocity_XYMoveAngle = prm_angVelocity02_XYMoveAngle;
	}
}


void StgMover::setTargetXYMoveAngle(angle prm_angTarget_XYMove) {
	int angSimple = prm_angTarget_XYMove;
	while(angSimple >= ANGLE360) {
		angSimple -= ANGLE360;
	}
	while(angSimple < 0) {
		angSimple += ANGLE360;
	}
	_auto_xymove_angle_target_Flg = true;
	_angTarget_XYMove = angSimple;
}

void StgMover::setTargetXYMoveAngle(int prm_tX, int prm_tY) {
	setTargetXYMoveAngle(GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)));
}

angle StgMover::getDistanceFromXYMoveAngleTo(int prm_tX, int prm_tY, int prm_iWay) {
	return getDistanceFromXYMoveAngleTo(
	           GgafDx9Util::getAngle(prm_tX - (_pActor->_X), prm_tY - (_pActor->_Y)),
	           prm_iWay
	       );
}


angle StgMover::getDistanceFromXYMoveAngleTo(angle prm_angTarget_XYMove, int prm_iWay) {
	if (prm_iWay ==  TURN_CLOSE_TO) { //�߂��ق���]
		if (0 <= _angXYMove && _angXYMove < ANGLE180) {
			if (0 <= prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove) {
				return -1*(_angXYMove - prm_angTarget_XYMove);
			} else if (prm_angTarget_XYMove == _angXYMove) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angXYMove < prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove+ANGLE180) {
				return prm_angTarget_XYMove - _angXYMove;
			} else if (prm_angTarget_XYMove == _angXYMove+ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angXYMove+ANGLE180 < prm_angTarget_XYMove && prm_angTarget_XYMove <= ANGLE360) {
				return -1*(_angXYMove+(ANGLE360 - prm_angTarget_XYMove));
			} else {
				//��������
				_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
				throw_GgafCriticalException("StgMover::behave() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(1)�B");
			}
		} else if(ANGLE180 <= _angXYMove && _angXYMove <= ANGLE360) {
			if (0 <= prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove-ANGLE180) {
				return ANGLE360 - _angXYMove + prm_angTarget_XYMove;
			} else if (prm_angTarget_XYMove == _angXYMove-ANGLE180) {
				//�����΂������Ă���i�������͓������j
				//�d���Ȃ��̂Ő��̒l�Ƃ���B
				return ANGLE180;
			} else if (_angXYMove-ANGLE180 < prm_angTarget_XYMove && prm_angTarget_XYMove < _angXYMove) {
				return -1*(_angXYMove - prm_angTarget_XYMove);
			} else if (_angXYMove == prm_angTarget_XYMove) {
				//�d�Ȃ��Ă�ꍇ
				return 0;
			} else if (_angXYMove < prm_angTarget_XYMove && prm_angTarget_XYMove <= ANGLE360) {
				return prm_angTarget_XYMove - _angXYMove;
			} else {
				//��������
				_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
				throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(2)�B");
			}
		}
	} else if (prm_iWay == TURN_COUNTERCLOCKWISE) { //�����v���̏ꍇ
		if (0 <= _angXYMove && _angXYMove < prm_angTarget_XYMove) {
			return (prm_angTarget_XYMove - _angXYMove);
		} else if (prm_angTarget_XYMove < _angXYMove && _angXYMove < ANGLE360) {
			return ANGLE360 - _angXYMove + prm_angTarget_XYMove;
		} else if (_angXYMove == prm_angTarget_XYMove) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
			throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(3)�B");
		}
	} else if (prm_iWay == TURN_CLOCKWISE) { //���v���̏ꍇ
		if (0 <= _angXYMove && _angXYMove < prm_angTarget_XYMove) {
			return -1*( _angXYMove + ANGLE360 - prm_angTarget_XYMove);
		} else if (prm_angTarget_XYMove < _angXYMove && _angXYMove < ANGLE360) {
			return -1*(_angXYMove - prm_angTarget_XYMove);
		} else if (_angXYMove == prm_angTarget_XYMove) {
			//�d�Ȃ��Ă�ꍇ
			return 0;
		}else {
			//��������
			_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
			throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() XY���ʈړ����p�A���O���l���A�^�[�Q�b�g�A���O���l���͈͊O�ł�(4)�B");
		}
	}

	_TRACE_("_angXYMove=" << _angXYMove << "/prm_angTarget_XYMove=" << prm_angTarget_XYMove);
	throw_GgafCriticalException("StgMover::getDistanceFromXYMoveAngleTo() ���̂�����p�̋��������߂�܂���B(1)");

}

void StgMover::setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove) {
	if (prm_iVelocity01_ZMove < prm_iVelocity02_ZMove) {
		_iTopVelocity_ZMove = prm_iVelocity02_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity01_ZMove;
	} else {
		_iTopVelocity_ZMove = prm_iVelocity01_ZMove;
		_iBottomVelocity_ZMove = prm_iVelocity02_ZMove;
	}
}



void StgMover::setZMoveVelocity(int prm_iVelocity_ZMove) {
	if (prm_iVelocity_ZMove > _iTopVelocity_ZMove) {
		_iVelocity_ZMove = _iTopVelocity_ZMove;
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
