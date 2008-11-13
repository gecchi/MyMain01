#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_

//�߂������ɉ�]
#define TURN_CLOSE_TO 0
//���v���ɉ�]
#define TURN_CLOCKWISE (-1)
//�����v���ɉ�]
#define TURN_COUNTERCLOCKWISE 1
//��]�ǂ���ł�
#define TURN_BOTH 0



//��X
#define AXIS_X 0
//��Y
#define AXIS_Y 1
//��Z
#define AXIS_Z 2


class GgafDx9GeometryMover {

public:
	/** �ΏۃA�N�^�[ */
	GgafDx9UntransformedActor* _pActor;

	/** �L�����̎���]���p�̕��p�l(0�`360,000) */
	angle _angAxisRot[3];
	/** ����]���p�̊p���x�i����]���p�l�ɖ��t���[�����Z������p�l�j */
	angle _angVelocity_AxisRotAngle[3];
	/** ����]���p�l�̊p���x���(�ō��l��360,000) */
	angle _angTopAngVelocity_AxisRotAngle[3];
	/** ����]���p�l�̊p���x����(�ō��l��-360,000) */
	angle _angBottomVelocity_AxisRotAngle[3];
	/** ����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
	angle _angAcceleration_AxisRotAngleVelocity[3];
	/** �ڕW�̎���]���p������~�@�\�L���t���O */
	bool _auto_rot_angle_target_Flg[3];
	/** �ڕW�Ƃ���L�����̎���]���p�̕��p�l(0�`360,000) */
	angle _angTarget_AxisRot[3];
	/** �ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
	int _auto_rot_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
	/** �ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
	angle _auto_rot_angle_target_allow_velocity[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���
	/**
	 * �R���X�g���N�^<BR>
	 * @param	prm_pActor	�K�pActor
	 */
	GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor);

	/**
	 * ���p�l���ȒP�ɂ���B
	 * @param prm_ang ���p�l
	 * @return �ȒP�ɂ��ꂽ���p�l
	 */
	angle simplifyAngle(angle prm_ang);


	/**
	 * Actor�̎��̉�]���p�l��ݒ�B<BR>
	 *
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_angAxisRot	���p�l(-360,000�`360,000)
	 */
	void setAxisRotAngle(int prm_iAxis, angle prm_angAxisRot);

	/**
	 * Actor�̎��̉�]���p�l��������XY���W����̑Ώ�XY���W�Őݒ�B<BR>
	 * ���̏�Z���w�肮�炢�����p�r���v�������т܂���B<BR>
	 *
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_tX	x XY���W
	 * @param	prm_tY	y XY���W
	 */
	void setAxisRotAngle(int prm_iAxis, int prm_tX, int prm_tY);


	/**
	 * ���݂� Actor �̎��̉�]���p�l�։��Z�i���Ō��Z�j�B<BR>
	 *
	 * �����ɓn���̂́A���Ɖ�]���p�l�����ł��BActor�̉�]���p�l�i_angAxisRot�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
	 * ���Z��̉�]���p�l���͈͊O�i0�`360,000�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setAxisRotAngle(int) ���Ăяo���܂��̂�<BR>
	 * ������ 0�`360,000 �͈͓̔��̒l�ɐݒ肳��܂��B<BR>
	 * �����ł�����Z�i���Z�j�����]���p�l�́A��]�����x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
	 * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
	 *
	 *   _iBottom_AxisRotVelocityAngle �� �����̉�]�p�l���� �� _angTopAngVelocity_AxisRotAngle  �ł��B<BR>
	 *
	 * �����͈͊O�̈����̉�]���p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
	 * �܂��A�����O�������@�\���L��(synchronize_ZaxisAxisRotAngle_to_AxisRotAngle_Flg)�̏ꍇ�A<BR>
	 * ���Z��̉�]���p�l�̒l���AZ���̖ڕW�̉�]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
	 *
	 * �y�⑫�F�z<BR>
	 * �����̉�]���p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�������Ȏ���]���邱�Ƃ��Ӗ����܂��B<BR>
	 * �t�ɁA�����̉�]���p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A��������]���邱�Ƃ��Ӗ����܂��B<BR>
	 * �f�t�H���g�̉�]�����x�̏���Ɖ����i_iBottom_AxisRotVelocityAngle�A_angTopAngVelocity_AxisRotAngle) ��<BR>
	 *
	 *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
	 *
	 * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�w�莲�ɂ��Ăǂ�ȉ�]���p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
	 *
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_iDistance_AxisRotAngle	��]���p�l����(�͈́F_iBottom_AxisRotVelocityAngle �` _angTopAngVelocity_AxisRotAngle)
	 */
	void addAxisRotAngle(int prm_iAxis, angle prm_iDistance_AxisRotAngle);

	/**
	 * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�l�ݒ�)<BR>
	 * �����ɐݒ肳�ꂽ���̉�]���p�l�ɂȂ�܂ŁA��]���p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
	 * ���Z�����Z���́A���݂̉�]���p�̊p���x�i_angVelocity_AxisRotAngle[prm_iAxis]�j�̐����Ō��肳��܂��B<BR>
	 * ��]���p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
	 * �����I�ɂ́AaddAxisRotAngle(prm_iAxis, int) �����t���[���s����d�g�݂ł��B<BR>
	 * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉�������܂��B<BR>
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_angRzMove	���B�ڕW�̉�]���p�l(0�`360,000)
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ��]����
	 * @param	prm_angAllowVelocity ������~�@�\���L���ɂȂ��]�p���x
	 */
	 void setTargetAxisRotAngle(int prm_iAxis, angle prm_angRzMove, int prm_iAllowRotWay = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	/**
	 * Actor�̖ڕW��]����������~�@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_tX	�Ώ�X���W
	 * @param	prm_tY	�Ώ�Y���W
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ��]����
	 * @param	prm_angAllowVelocity ������~�@�\���L���ɂȂ��]�p���x
	 */
	void setTargetAxisRotAngleV(int prm_iAxis, int prm_tX, int prm_tY, int prm_iAllowRotWay = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	void setAxisRotAngleVelocity(int prm_iAxis, angle prm_angVelocity_AxisRotAngle);

	void setAxisRotAngleVelocityRenge(int prm_iAxis, angle prm_angVelocity01_AxisRotAngle, angle prm_angVelocity02_AxisRotAngle);

	void setAxisRotAngleAcceleration(int prm_iAxis, angle prm_angAcceleration_AxisRotAngleVelocity);

	angle getDistanceFromAxisRotAngleTo(int prm_iAxis, int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromAxisRotAngleTo(int prm_iAxis, angle prm_angTarget_AxisRot, int prm_iWay);

////////////////////////////////////////////////////MOVER
public:
	/** �L�����̈ړ����p�P�ʃx�N�g�� */
	double _vX, _vY, _vZ;
	/** �ړ����p��Z����] */
	angle _angRz_Move;
	/** �ړ����p��Y����] */
	angle _angRy_Move;
	/** �ړ����x */
	int _iVelocity_Move;
	/** �ړ����x��� */
	int _iTopAngVelocity_Move;
	/** �ړ����x���� */
	int _iBottomVelocity_Move;
	/** �ړ������x */
	int _iAcceleration_MoveVelocity;

///////�R�s�[��begin
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
	/** �ڕW��Rz���ʈړ����p������~�@�\���L���ɂȂ�i����]���� */
	int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
	/** �ڕW��Rz���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x */
	int _auto_move_angle_rz_target_allow_velocity;
	/** �����O�������@�\�L���t���O */
	bool _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg;
	//true  : Rz���ʈړ����p��ύX����ƁA����ɔ����������p�l��Z������]���p�ɂ��ݒ肳���
	//false : Rz���ʈړ����p��Z������]���p�͓Ɨ�
////////�R�s�[��end

///////�R�s�[��begin
	/** Ry���ʈړ����p�̊p���x�iRy���ʈړ����p�l�ɖ��t���[�����Z������p�l�j */
	angle _angVelocity_MoveAngleRy;
	/** Ry���ʈړ����p�l�̊p���x���(�ō��l��360,000) */
	angle _angTopAngVelocity_MoveAngleRy;
	/** Ry���ʈړ����p�l�̊p���x����(�ō��l��-360,000) */
	angle _angBottomVelocity_MoveAngleRy;
	/** Ry���ʈړ����p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
	angle _angAcceleration_MoveAngleRyVelocity;
	/** �ڕW��Ry���ʈړ����p������~�@�\�L���t���O */
	bool _auto_move_angle_ry_target_Flg;
	/** �ڕW�Ƃ���L������Ry���ʈړ����p�̕��p�l(0�`360,000) */
	int _angRyTarget_Move;
	/** �ڕW��Ry���ʈړ����p������~�@�\���L���ɂȂ�i����]���� */
	int _auto_move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
	/** �ڕW��Ry���ʈړ����p������~�@�\���L���ɂȂ�ړ����p�p���x */
	int _auto_move_angle_ry_target_allow_velocity;
	/** �����O�������@�\�L���t���O */
	bool _synchronize_YAxisRotAngle_to_MoveAngleRy_Flg;
	//true  : Ry���ʈړ����p��ύX����ƁA����ɔ����������p�l��Z������]���p�ɂ��ݒ肳���
	//false : Ry���ʈړ����p��Z������]���p�͓Ɨ�
////////�R�s�[��end

	/** X�������ړ����x */
	int _iVelocity_XMove;
	/** X�������ړ����x��� */
	int _iTopAngVelocity_XMove;
	/** X�������ړ����x���� */
	int _iBottomVelocity_XMove;
	/** Z�������ړ������x */
	int _iAcceleration_XMoveVelocity;
	/** Y�������ړ����x */
	int _iVelocity_YMove;
	/** Y�������ړ����x��� */
	int _iTopAngVelocity_YMove;
	/** Y�������ړ����x���� */
	int _iBottomVelocity_YMove;
	/** Y�������ړ������x */
	int _iAcceleration_YMoveVelocity;
	/** Z�������ړ����x */
	int _iVelocity_ZMove;
	/** Z�������ړ����x��� */
	int _iTopAngVelocity_ZMove;
	/** Z�������ړ����x���� */
	int _iBottomVelocity_ZMove;
	/** Z�������ړ������x */
	int _iAcceleration_ZMoveVelocity;


	/**
	 * Actor��Rz���ʈړ��X�s�[�h��ݒ�<BR>
	 * @param	prm_iVelocity_Move	Rz���ʈړ��X�s�[�h
	 */
	void setMoveVelocity(int prm_iVelocity_Move);


	void setMoveVelocityRenge(int prm_iVelocity01_Move, int prm_iVelocity02_Move);

	void setMoveAcceleration(int prm_angAcceleration_MoveAngleRzVelocity);


///////�R�s�[��begin

	/**
	 * Actor��Rz���ʈړ����p�l��ݒ�B<BR>
	 * ���Z���Rz���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
	 * �����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)�̏ꍇ�A<BR>
	 * Actor�̌�����Rz���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_angRzMove	Rz���ʈړ����p�l(0�`360,000)
	 */
	void setMoveAngleRz(angle prm_angle);

	/**
	 * Actor��Rz���ʈړ����p�l������Rz���ʍ��W����̑Ώ�Rz���ʍ��W�ւ̕���������o���A�ݒ肷��B<BR>
	 * �����O�������@�\���L��(_synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg)�̏ꍇ�A<BR>
	 * Actor��Z�����p�l�i�����j��Rz���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_tX	�Ώ�xRz���ʍ��W
	 * @param	prm_tY	�Ώ�yRz���ʍ��W
	 */
	void setMoveAngleRz(int prm_tX, int prm_tY);

	/**
	 * ���݂� Actor ��Rz���ʈړ����p�l�։��Z�i���Ō��Z�j�B<BR>
	 *
	 * �����ɓn���̂́ARz���ʈړ����p�l�̑����ł��BActor��Rz���ʈړ����p�l�i_angRz_Move�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
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
	 * @param	prm_angRzMove	���B�ڕW��Rz���ʈړ����p�l(-360,000�`360,000)
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ�i����]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetMoveAngleRz(angle prm_angRzMove, int _auto_move_angle_rz_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	/**
	 * Actor�̖ڕW��Rz���ʈړ����p������~�@�\��L��(�ڕW��Rz���ʈړ����p������Rz���ʍ��W����̑Ώ�Rz���ʍ��W�Őݒ�)<BR>
	 * �@�\��setTargetMoveAngleRz(int)�Ɠ���<BR>
	 *
	 * @param	prm_tX	xRz���W
	 * @param	prm_tY	yRy���W
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ�i����]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetMoveAngleRzV(int prm_tX, int prm_tY, int _auto_move_angle_rz_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);


	void setMoveAngleRzVelocity(int prm_angVelocity_MoveAngleRz);

	void setMoveAngleRzVelocityRenge(angle prm_angVelocity01_MoveAngleRz, angle prm_angVelocity02_MoveAngleRz);

	void setMoveAngleRzAcceleration(angle prm_angAcceleration_MoveAngleRzVelocity);


	angle getDistanceFromMoveAngleRzTo(int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromMoveAngleRzTo(angle prm_angRzTarget_Move, int prm_iWay);
///�R�s�[��end

///////�R�s�[��begin

	/**
	 * Actor��Ry���ʈړ����p�l��ݒ�B<BR>
	 * ���Z���Ry���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
	 * �����O�������@�\���L��(_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg)�̏ꍇ�A<BR>
	 * Actor�̌�����Ry���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_angRyMove	Ry���ʈړ����p�l(0�`360,000)
	 */
	void setMoveAngleRy(angle prm_angle);

	/**
	 * Actor��Ry���ʈړ����p�l������Ry���ʍ��W����̑Ώ�Ry���ʍ��W�ւ̕���������o���A�ݒ肷��B<BR>
	 * �����O�������@�\���L��(_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg)�̏ꍇ�A<BR>
	 * Actor��Z�����p�l�i�����j��Ry���ʈړ����p�Ɠ��������������悤�� setTargetAxisRotAngle(int) �����s����܂��B<BR>
	 *
	 * @param	prm_tX	�Ώ�xRy���ʍ��W
	 * @param	prm_tY	�Ώ�yRy���ʍ��W
	 */
	void setMoveAngleRy(int prm_tX, int prm_tY);

	/**
	 * ���݂� Actor ��Ry���ʈړ����p�l�։��Z�i���Ō��Z�j�B<BR>
	 *
	 * �����ɓn���̂́ARy���ʈړ����p�l�̑����ł��BActor��Ry���ʈړ����p�l�i_angRy_Move�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
	 * ���Z���Ry���ʈړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setMoveAngleRy(int) ���Ăяo���܂��̂�<BR>
	 * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
	 * �����ł�����Z�i���Z�j����Ry���ʈړ����p�l�́ARy���ʈړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
	 * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
	 *
	 *   _angBottomVelocity_MoveAngleRy �� �����̓����p�l���� �� _angTopAngVelocity_MoveAngleRy  �ł��B<BR>
	 *
	 * �����͈͊O�̈�����Ry���ʈړ����p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
	 * �܂��A�����O�������@�\���L��(_synchronize_YAxisRotAngle_to_MoveAngleRy_Flg)�̏ꍇ�A<BR>
	 * ���Z���Ry���ʈړ����p�l�̒l���AZ���̖ڕW�̎���]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
	 *
	 * �y�⑫�F�z<BR>
	 * ������Ry���ʈړ����p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
	 * �t�ɁA������Ry���ʈړ����p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
	 * �f�t�H���g��Ry���ʈړ������x�̏���Ɖ����i_angBottomVelocity_MoveAngleRy�A_angTopAngVelocity_MoveAngleRy) ��<BR>
	 *
	 *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
	 *
	 * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ��Ry���ʈړ����p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
	 *
	 * @param	prm_iDistance_MoveAngleRy	Ry���ʈړ����p�l����(�͈́F_angBottomVelocity_MoveAngleRy �` _angTopAngVelocity_MoveAngleRy)
	 */
	void addMoveAngleRy(angle prm_iDistance_MoveAngleRy);


	/**
	 * Actor�̖ڕW��Ry���ʈړ����p������~�@�\��L��(�ڕW��Ry���ʈړ����p�l�ݒ�)<BR>
	 * �����ɐݒ肳�ꂽRy���ʈړ����p�l�ɂȂ�܂ŁARy���ʈړ����p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
	 * ���Z�����Z���́ARy���ʈړ����p�̊p���x�i_angVelocity_MoveAngleRy�j�̐����Ō��肳��܂��B<BR>
	 * Ry���ʈړ����p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
	 * �����I�ɂ́AaddMoveAngleRy(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
	 * �ڕW��Ry���ʈړ����p�ɓ��B�����Ȃ�΁A���̖ڕW��Ry���ʈړ����p������~�@�\�͉�������܂��B<BR>
	 *
	 * @param	prm_angRyMove	���B�ڕW��Ry���ʈړ����p�l(-360,000�`360,000)
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ�i����]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetMoveAngleRy(angle prm_angRyMove, int _auto_move_angle_ry_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);

	/**
	 * Actor�̖ڕW��Ry���ʈړ����p������~�@�\��L��(�ڕW��Ry���ʈړ����p������Ry���ʍ��W����̑Ώ�Ry���ʍ��W�Őݒ�)<BR>
	 * �@�\��setTargetMoveAngleRy(int)�Ɠ���<BR>
	 *
	 * @param	prm_tX	xRy���W
	 * @param	prm_tY	yRy���W
	 * @param	prm_iAllowRotWay  ������~�@�\���L���ɂȂ�i����]����
	 * @param	prm_angAllowVelocity ��~�@�\���L���ɂȂ�ړ����p�p���x
	 */
	void setTargetMoveAngleRyV(int prm_tX, int prm_tY, int _auto_move_angle_ry_target_allow_way = TURN_BOTH, angle prm_angAllowVelocity = ANGLE180);


	void setMoveAngleRyVelocity(int prm_angVelocity_MoveAngleRy);

	void setMoveAngleRyVelocityRenge(angle prm_angVelocity01_MoveAngleRy, angle prm_angVelocity02_MoveAngleRy);

	void setMoveAngleRyAcceleration(angle prm_angAcceleration_MoveAngleRyVelocity);


	angle getDistanceFromMoveAngleRyTo(int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromMoveAngleRyTo(angle prm_angRyTarget_Move, int prm_iWay);
///�R�s�[��end

	void setMoveAngleRzRy(angle prm_angleRz, angle prm_angleRy);

	void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);


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
	//virtual void behave();

	void setXMoveVelocity(int prm_iVelocity_XMove);
	void setXMoveVelocityRenge(int prm_iVelocity01_XMove, int prm_iVelocity02_XMove);
	void setXMoveAcceleration(int prm_iAcceleration_XMoveVelocity);

	void setYMoveVelocity(int prm_iVelocity_YMove);
	void setYMoveVelocityRenge(int prm_iVelocity01_YMove, int prm_iVelocity02_YMove);
	void setYMoveAcceleration(int prm_iAcceleration_YMoveVelocity);

	void setZMoveVelocity(int prm_iVelocity_ZMove);
	void setZMoveVelocityRenge(int prm_iVelocity01_ZMove, int prm_iVelocity02_ZMove);
	void setZMoveAcceleration(int prm_iAcceleration_ZMoveVelocity);













	/**
	 * ���t���[����Actor�̐U�镑���B<BR>
	 */
	virtual void behave();


	virtual ~GgafDx9GeometryMover();
};


#endif /*GGAFDX9GEOMETRYMOVER_H_*/

