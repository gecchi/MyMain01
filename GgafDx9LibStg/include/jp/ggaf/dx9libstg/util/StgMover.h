#ifndef STGMOVER_H_
#define STGMOVER_H_


class StgMover : public GgafDx9GeometryMover {

public:
	/** �L������XY���ʈړ����pX�����P�ʃx�N�g�� */
	int _vX_XYMove;

	/** �L������XY���ʈړ����pY�����P�ʃx�N�g�� */
	int _vY_XYMove;

	/** �L������XY���ʈړ����p�̕��p�l(0�`360,000) */
	int _angXYMove;

	/** XY���ʈړ����p�̊p���x�iXY���ʈړ����p�l�ɖ��t���[�����Z������p�l�j */
	angle _angVelocity_XYMoveAngle;

	/** XY���ʈړ����p�l�̊p���x���(�ō��l��360,000) */
	angle _angTopAngVelocity_XYMoveAngle;

	/** XY���ʈړ����p�l�̊p���x����(�ō��l��-360,000) */
	angle _angBottomVelocity_XYMoveAngle;

	/** XY���ʈړ����p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
	angle _angAcceleration_XYMoveAngleVelocity;

	/** �ڕW��XY���ʈړ����p������~�@�\�L���t���O */
	bool _auto_xymove_angle_target_Flg;
	/** �ڕW�Ƃ���L������XY���ʈړ����p�̕��p�l(0�`360,000) */
	int _angTarget_XYMove;
	/** �ڕW��XY���ʈړ����p������~�@�\���L���ɂȂ��]���� */
	int _auto_xymove_angle_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
	/** �ڕW��XY���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x */
	int _auto_xymove_angle_target_allow_velocity;

///////////////////////////

	/** XY���ʈړ����x�iXY���ʈړ�XY���W/frame�j*/
	int _iVelocity_XYMove;

	/** XY���ʈړ����x��� */
	int _iTopAngVelocity_XYMove;

	/** XY���ʈړ����x���� */
	int _iBottomVelocity_XYMove;

	/** XY���ʈړ������x */
	int _iAcceleration_XYMoveVelocity;


	/** Z���ړ����x */
	int _iVelocity_ZMove;

	/** Z���ړ����x��� */
	int _iTopAngVelocity_ZMove;

	/** Z���ړ����x���� */
	int _iBottomVelocity_ZMove;

	/** Z���ړ������x */
	int _iAcceleration_ZMoveVelocity;


	/** �����O�������@�\�L���t���O */
	bool _synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg;
	//true  : XY���ʈړ����p��ύX����ƁA����ɔ����������p�l��Z������]���p�ɂ��ݒ肳���
	//false : XY���ʈړ����p��Z������]���p�͓Ɨ�




	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_pActor	�K�pActor
	 */
	StgMover(GgafDx9UntransformedActor* prm_pActor);

	/**
	 * Actor��XY���ʈړ����p�l��ݒ�B<BR>
	 * ���Z���XY���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
	 * �����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg)�̏ꍇ�A<BR>
	 * Actor�̌�����XY���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_angXYMove	XY���ʈړ����p�l(0�`360,000)
	 */
	void setXYMoveAngle(angle prm_angXYMove);

	/**
	 * Actor��XY���ʈړ����p�l������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
	 * �����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg)�̏ꍇ�A<BR>
	 * Actor��Z�����p�l�i�����j��XY���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_tX	�Ώ�xXY���W
	 * @param	prm_tY	�Ώ�yXY���W
	 */
	void setXYMoveAngle(int prm_tX, int prm_tY);

	/**
	 * ���݂� Actor ��XY���ʈړ����p�l�։��Z�i���Ō��Z�j�B<BR>
	 *
	 * �����ɓn���̂́AXY���ʈړ����p�l�̑����ł��BActor��XY���ʈړ����p�l�i_angXYMove�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
	 * ���Z���XY���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setXYMoveAngle(int) ���Ăяo���܂��̂�<BR>
	 * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
	 * �����ł�����Z�i���Z�j����XY���ʈړ����p�l�́AXY���ʈړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
	 * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
	 *
	 *   _angBottomVelocity_XYMoveAngle �� �����̓����p�l���� �� _angTopAngVelocity_XYMoveAngle  �ł��B<BR>
	 *
	 * �����͈͊O�̈�����XY���ʈړ����p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
	 * �܂��A�����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg)�̏ꍇ�A<BR>
	 * ���Z���XY���ʈړ����p�l�̒l���AZ���̖ڕW�̎���]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
	 *
	 * �y�⑫�F�z<BR>
	 * ������XY���ʈړ����p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
	 * �t�ɁA������XY���ʈړ����p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
	 * �f�t�H���g��XY���ʈړ������x�̏���Ɖ����i_angBottomVelocity_XYMoveAngle�A_angTopAngVelocity_XYMoveAngle) ��<BR>
	 *
	 *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
	 *
	 * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ��XY���ʈړ����p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
	 *
	 * @param	prm_iDistance_XYMoveAngle	XY���ʈړ����p�l����(�͈́F_angBottomVelocity_XYMoveAngle �` _angTopAngVelocity_XYMoveAngle)
	 */
	void addXYMoveAngle(angle prm_iDistance_XYMoveAngle);




	/**
	 * Actor�̖ڕW��XY���ʈړ����p������~�@�\��L��(�ڕW��XY���ʈړ����p�l�ݒ�)<BR>
	 * �����ɐݒ肳�ꂽXY���ʈړ����p�l�ɂȂ�܂ŁAXY���ʈړ����p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
	 * ���Z�����Z���́AXY���ʈړ����p�̊p���x�i_angVelocity_XYMoveAngle�j�̐����Ō��肳��܂��B<BR>
	 * XY���ʈړ����p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
	 * �����I�ɂ́AaddXYMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
	 * �ڕW��XY���ʈړ����p�ɓ��B�����Ȃ�΁A���̖ڕW��XY���ʈړ����p������~�@�\�͉�������܂��B<BR>
	 *
	 * @param	prm_angXYMove	���B�ڕW��XY���ʈړ����p�l(-360,000�`360,000)
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ��]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetXYMoveAngle(angle prm_angXYMove, int _auto_xymove_angle_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	/**
	 * Actor�̖ڕW��XY���ʈړ����p������~�@�\��L��(�ڕW��XY���ʈړ����p������XY���W����̑Ώ�XY���W�Őݒ�)<BR>
	 * �@�\��setTargetXYMoveAngle(int)�Ɠ���<BR>
	 *
	 * @param	prm_tX	xXY���W
	 * @param	prm_tY	yXY���W
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ��]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetXYMoveAngleV(int prm_tX, int prm_tY, int _auto_xymove_angle_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);


	/**
	 * Actor��XY���ʈړ��X�s�[�h��ݒ�<BR>
	 * @param	prm_iVelocity_XYMove	XY���ʈړ��X�s�[�h
	 */
	void setXYMoveVelocity(int prm_iVelocity_XYMove);


	void setXYMoveVelocityRenge(int prm_iVelocity01_XYMove, int prm_iVelocity02_XYMove);

	void setXYMoveAcceleration(int prm_angAcceleration_XYMoveAngleVelocity);


	void setXYMoveAngleVelocity(int prm_angVelocity_XYMoveAngle);

	void setXYMoveAngleVelocityRenge(angle prm_angVelocity01_XYMoveAngle, angle prm_angVelocity02_XYMoveAngle);

	void setXYMoveAngleAcceleration(angle prm_angAcceleration_XYMoveAngleVelocity);



	angle getDistanceFromXYMoveAngleTo(int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromXYMoveAngleTo(angle prm_angTarget_XYMove, int prm_iWay);


	/**
	 * ���t���[����Actor�̐U�镑���B<BR>
	 * �{�C���^�[�t�F�[�X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
	 * behave() �̋�̓I�Ȗ��t���[���̏����͈ȉ��̒ʂ�B<BR>
	 * �E�����x(_iAcceleration_XYMoveVelocity)��0�łȂ��ꍇ�A�����x�ɂ��X�s�[�h���������B<BR>
	 * �@�@�����Z��̃X�s�[�h�� setXYMoveVelocity(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW��XY���ʈړ����p������~�@�\���g�p���̏ꍇ�AXY���ʈړ����p�ύX����<BR>
	 * �@�@���v�Z���ꂽXY���ʈړ����p�l�� addXYMoveAngle(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW��XY���ʈړ����p������~�@�\�g�p���ł͂Ȃ��ꍇ�A����XY���ʈړ����p�l���Z����<BR>
	 * �@�@��addXYMoveAngle(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW�̎���]���p������~�@�\�g�p���̏ꍇ�A����]���p�ύX����<BR>
	 * �@�@���v�Z���ꂽ����]���p�l�� addAxisRotAngle(int) �����t���[�����s����܂��B<BR>
	 * �E�ڕW�̎���]���p������~�@�\���g�p���ł͂Ȃ��ꍇ�A���ʎ���]���p�l���Z����<BR>
	 * �@�@��addAxisRotAngle(int) �����t���[�����s����܂��B<BR>
	 * �ȏ�̏������s������AActor�̈ȉ��̃����o�ցA���W�������AZ����]����ݒ肵�܂��B<BR>
	 *  _X ��� XY���ʈړ����p�l��XY���ʈړ��X�s�[�h����X���W�����v�Z�����Z<BR>
	 *  _Y ��� XY���ʈړ����p�l��XY���ʈړ��X�s�[�h����Y���W�����v�Z�����Z<BR>
	 *  _Z ���_iVelocity_ZMove �����Z
	 *  _RX   ��� ����]���p�l����<BR>
	 *  _RY   ��� ����]���p�l����<BR>
	 *  _RZ   ��� ����]���p�l����<BR>
	 * �y�K���l���ݒ肳��郁���o�[�z<BR>
	 * _iVelocity_XYMove,<BR>
	 * _pActor->_X += _vX_XYMove*_iVelocity_XYMove/LEN_UNIT;<BR>
	 * _pActor->_Y += _vY_XYMove*_iVelocity_XYMove/LEN_UNIT;<BR>
	 * _pActor->_Z += _iVelocity_ZMove
	 */
	virtual void behave();


	void setZMoveVelocity(int prm_iVelocity_ZMove);

	void setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove);

	void setZMoveAcceleration(int prm_iAcceleration_ZMoveVelocity);


//	void setXYZMove(int prm_iVelocity, int tx, int ty, int tz);

	virtual ~StgMover();
};


#endif /*STGMOVER_H_*/

