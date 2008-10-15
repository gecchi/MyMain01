#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_

//�߂������ɉ�]
#define TURN_CLOSE_TO 0
//���v���ɉ�]
#define TURN_CLOCKWISE (-1)
//�����v���ɉ�]
#define TURN_COUNTERCLOCKWISE 1



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

	/** �ڕW�Ƃ���L�����̎���]���p�̕��p�l(0�`360,000) */
	angle _angTarget_AxisRot[3];

	/** �ڕW�̎���]���p��������@�\�L���t���O */
	bool _auto_rot_angle_target_Flg[3];


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
	 * Actor�̖ڕW�̎���]���p��������@�\��L��(�ڕW�̎���]���p�l�ݒ�)<BR>
	 * �����ɐݒ肳�ꂽ���̉�]���p�l�ɂȂ�܂ŁA��]���p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
	 * ���Z�����Z���́A���݂̉�]���p�̊p���x�i_angVelocity_AxisRotAngle[prm_iAxis]�j�̐����Ō��肳��܂��B<BR>
	 * ��]���p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
	 * �����I�ɂ́AaddAxisRotAngle(prm_iAxis, int) �����t���[���s����d�g�݂ł��B<BR>
	 * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p��������@�\�͉�������܂��B<BR>
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_angXYMove	���B�ڕW�̉�]���p�l(0�`360,000)
	 */
	 void setTargetAxisRotAngle(int prm_iAxis, angle prm_angXYMove);

	/**
	 * Actor�̖ڕW��]������������@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
	 * @param	prm_iAxis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
	 * @param	prm_tX	�Ώ�X���W
	 * @param	prm_tY	�Ώ�Y���W
	 */
	void setTargetAxisRotAngle(int prm_iAxis, int prm_tX, int prm_tY);

	void setAxisRotAngleVelocity(int prm_iAxis, angle prm_angVelocity_AxisRotAngle);

	void setAxisRotAngleVelocityRenge(int prm_iAxis, angle prm_angVelocity01_AxisRotAngle, angle prm_angVelocity02_AxisRotAngle);

	void setAxisRotAngleAcceleration(int prm_iAxis, angle prm_angAcceleration_AxisRotAngleVelocity);

	angle getDistanceFromAxisRotAngleTo(int prm_iAxis, int prm_tX, int prm_tY, int prm_iWay);

	angle getDistanceFromAxisRotAngleTo(int prm_iAxis, angle prm_angTarget_AxisRot, int prm_iWay);

/**
	 * ���t���[����Actor�̐U�镑���B<BR>
	 */
	virtual void behave();


	virtual ~GgafDx9GeometryMover();
};


#endif /*GGAFDX9GEOMETRYMOVER_H_*/

