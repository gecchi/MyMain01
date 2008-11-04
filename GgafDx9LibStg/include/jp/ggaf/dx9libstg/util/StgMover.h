#ifndef STGMOVER_H_
#define STGMOVER_H_


class StgMover : public GgafDx9GeometryMover {

public:
	/** �L�����̈ړ����p�P�ʃx�N�g�� */
	double _vX, _vY, _vZ;
	/** �ړ����p��Z����] */
	angle _angRz_Move;
	/** �ړ����p��Y����] */
	angle _angRy_Move;

	/** Rz���ʈړ����p�̊p���x�iRz���ʈړ����p�l�ɖ��t���[�����Z������p�l�j */
	angle _angVelocity_MoveAngleRz;

	/** Rz���ʈړ����p�l�̊p���x���(�ō��l��360,000) */
	angle _angTopAngVelocity_MoveAngleRz;

	/** Rz���ʈړ����p�l�̊p���x����(�ō��l��-360,000) */
	angle _angBottomVelocity_MoveAngleRz;

	/** Rz���ʈړ����p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
	angle _angAcceleration_MoveAngleRzVelocity;

	/** �ڕW��Rz���ʈړ����p������~�@�\�L���t���O */
	bool _auto_move_angle_rz_target_Flg;
	/** �ڕW�Ƃ���L������Rz���ʈړ����p�̕��p�l(0�`360,000) */
	int _angRzTarget_Move;
	/** �ڕW��Rz���ʈړ����p������~�@�\���L���ɂȂ��]���� */
	int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
	/** �ڕW��Rz���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x */
	int _auto_move_angle_rz_target_allow_velocity;

///////////////////////////

	/** �ړ����x */
	int _iVelocity_Move;

	/** �ړ����x��� */
	int _iTopAngVelocity_Move;

	/** �ړ����x���� */
	int _iBottomVelocity_Move;

	/** �ړ������x */
	int _iAcceleration_MoveVelocity;


	/** Z���ړ����x */
	int _iVelocity_ZMove;

	/** Z���ړ����x��� */
	int _iTopAngVelocity_ZMove;

	/** Z���ړ����x���� */
	int _iBottomVelocity_ZMove;

	/** Z���ړ������x */
	int _iAcceleration_ZMoveVelocity;
//

	/** �����O�������@�\�L���t���O */
	bool _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg;
	//true  : Rz���ʈړ����p��ύX����ƁA����ɔ����������p�l��Z������]���p�ɂ��ݒ肳���
	//false : Rz���ʈړ����p��Z������]���p�͓Ɨ�




	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_pActor	�K�pActor
	 */
	StgMover(GgafDx9UntransformedActor* prm_pActor);

	/**
	 * Actor��Rz���ʈړ����p�l��ݒ�B<BR>
	 * ���Z���Rz���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
	 * �����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)�̏ꍇ�A<BR>
	 * Actor�̌�����Rz���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_angXYMove	Rz���ʈړ����p�l(0�`360,000)
	 */
	void setMoveAngleRz(angle prm_angle);



	/**
	 * Actor��Rz���ʈړ����p�l������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
	 * �����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)�̏ꍇ�A<BR>
	 * Actor��Z�����p�l�i�����j��Rz���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_tX	�Ώ�xXY���W
	 * @param	prm_tY	�Ώ�yXY���W
	 */
	void setMoveAngleRz(int prm_tX, int prm_tY);

	/**
	 * ���݂� Actor ��Rz���ʈړ����p�l�։��Z�i���Ō��Z�j�B<BR>
	 *
	 * �����ɓn���̂́ARz���ʈړ����p�l�̑����ł��BActor��Rz���ʈړ����p�l�i_angXYMove�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
	 * ���Z���Rz���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setMoveAngleRz(int) ���Ăяo���܂��̂�<BR>
	 * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
	 * �����ł�����Z�i���Z�j����Rz���ʈړ����p�l�́ARz���ʈړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
	 * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
	 *
	 *   _angBottomVelocity_MoveAngleRz �� �����̓����p�l���� �� _angTopAngVelocity_MoveAngleRz  �ł��B<BR>
	 *
	 * �����͈͊O�̈�����Rz���ʈړ����p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
	 * �܂��A�����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)�̏ꍇ�A<BR>
	 * ���Z���Rz���ʈړ����p�l�̒l���AZ���̖ڕW�̎���]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
	 *
	 * �y�⑫�F�z<BR>
	 * ������Rz���ʈړ����p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
	 * �t�ɁA������Rz���ʈړ����p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
	 * �f�t�H���g��Rz���ʈړ������x�̏���Ɖ����i_angBottomVelocity_MoveAngleRz�A_angTopAngVelocity_MoveAngleRz) ��<BR>
	 *
	 *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
	 *
	 * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ��Rz���ʈړ����p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
	 *
	 * @param	prm_iDistance_MoveAngleRz	Rz���ʈړ����p�l����(�͈́F_angBottomVelocity_MoveAngleRz �` _angTopAngVelocity_MoveAngleRz)
	 */
	void addMoveAngleRz(angle prm_iDistance_MoveAngleRz);




	/**
	 * Actor�̖ڕW��Rz���ʈړ����p������~�@�\��L��(�ڕW��Rz���ʈړ����p�l�ݒ�)<BR>
	 * �����ɐݒ肳�ꂽRz���ʈړ����p�l�ɂȂ�܂ŁARz���ʈړ����p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
	 * ���Z�����Z���́ARz���ʈړ����p�̊p���x�i_angVelocity_MoveAngleRz�j�̐����Ō��肳��܂��B<BR>
	 * Rz���ʈړ����p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
	 * �����I�ɂ́AaddMoveAngleRz(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
	 * �ڕW��Rz���ʈړ����p�ɓ��B�����Ȃ�΁A���̖ڕW��Rz���ʈړ����p������~�@�\�͉�������܂��B<BR>
	 *
	 * @param	prm_angXYMove	���B�ڕW��Rz���ʈړ����p�l(-360,000�`360,000)
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ��]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetMoveAngleRz(angle prm_angXYMove, int _auto_move_angle_rz_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	/**
	 * Actor�̖ڕW��Rz���ʈړ����p������~�@�\��L��(�ڕW��Rz���ʈړ����p������XY���W����̑Ώ�XY���W�Őݒ�)<BR>
	 * �@�\��setTargetMoveAngleRz(int)�Ɠ���<BR>
	 *
	 * @param	prm_tX	xXY���W
	 * @param	prm_tY	yXY���W
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ��]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetMoveAngleRzV(int prm_tX, int prm_tY, int _auto_move_angle_rz_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);


	/**
	 * Actor��Rz���ʈړ��X�s�[�h��ݒ�<BR>
	 * @param	prm_iVelocity_Move	Rz���ʈړ��X�s�[�h
	 */
	void setMoveVelocity(int prm_iVelocity_Move);


	void setMoveVelocityRenge(int prm_iVelocity01_Move, int prm_iVelocity02_Move);

	void setMoveAcceleration(int prm_angAcceleration_MoveAngleRzVelocity);


	void setMoveAngleRzVelocity(int prm_angVelocity_MoveAngleRz);

	void setMoveAngleRzVelocityRenge(angle prm_angVelocity01_MoveAngleRz, angle prm_angVelocity02_MoveAngleRz);

	void setMoveAngleRzAcceleration(angle prm_angAcceleration_MoveAngleRzVelocity);



	angle getDistanceFromMoveAngleRzTo(int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromMoveAngleRzTo(angle prm_angRzTarget_Move, int prm_iWay);


	void setXYZMoveAngle(int prm_tX, int prm_tY, int prm_tZ);


	void setMoveAngleRy(angle prm_angle);


	/**
	 * ���t���[����Actor�̐U�镑���B<BR>
	 * �{�C���^�[�t�F�[�X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
	 * behave() �̋�̓I�Ȗ��t���[���̏����͈ȉ��̒ʂ�B<BR>
	 * �E�����x(_iAcceleration_MoveVelocity)��0�łȂ��ꍇ�A�����x�ɂ��X�s�[�h���������B<BR>
	 * �@�@�����Z��̃X�s�[�h�� setMoveVelocity(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW��Rz���ʈړ����p������~�@�\���g�p���̏ꍇ�ARz���ʈړ����p�ύX����<BR>
	 * �@�@���v�Z���ꂽRz���ʈړ����p�l�� addMoveAngleRz(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW��Rz���ʈړ����p������~�@�\�g�p���ł͂Ȃ��ꍇ�A����Rz���ʈړ����p�l���Z����<BR>
	 * �@�@��addMoveAngleRz(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW�̎���]���p������~�@�\�g�p���̏ꍇ�A����]���p�ύX����<BR>
	 * �@�@���v�Z���ꂽ����]���p�l�� addAxisRotAngle(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW�̎���]���p������~�@�\���g�p���ł͂Ȃ��ꍇ�A���ʎ���]���p�l���Z����<BR>
	 * �@�@��addAxisRotAngle(int) �����t���[�����s����܂��B<BR>
	 * �ȏ�̏������s������AActor�̈ȉ��̃����o�ցA���W�������AZ����]����ݒ肵�܂��B<BR>
	 *  _X ��� Rz���ʈړ����p�l��Rz���ʈړ��X�s�[�h����X���W�����v�Z�����Z<BR>
	 *  _Y ��� Rz���ʈړ����p�l��Rz���ʈړ��X�s�[�h����Y���W�����v�Z�����Z<BR>
	 *  _Z ���_iVelocity_ZMove �����Z
	 *  _RX   ��� ����]���p�l����<BR>
	 *  _RY   ��� ����]���p�l����<BR>
	 *  _RZ   ��� ����]���p�l����<BR>
	 * �y�K���l���ݒ肳��郁���o�[�z<BR>
	 * _iVelocity_Move,<BR>
	 * _pActor->_X += _vX_Move*_iVelocity_Move/LEN_UNIT;<BR>
	 * _pActor->_Y += _vY_Move*_iVelocity_Move/LEN_UNIT;<BR>
	 * _pActor->_Z += _iVelocity_ZMove
	 */
	virtual void behave();


	void setZMoveVelocity(int prm_iVelocity_ZMove);

	void setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove);

	void setZMoveAcceleration(int prm_iAcceleration_ZMoveVelocity);


	virtual ~StgMover();
};


#endif /*STGMOVER_H_*/

