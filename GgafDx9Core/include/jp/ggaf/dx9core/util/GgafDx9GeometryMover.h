#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_
namespace GgafDx9Core {

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

typedef int velo;
typedef int acce;
typedef int angvelo;
typedef int angacce;
/**
 * �ړ��̂��߂̍��W�v�Z�@�\�����N���X.
 */
class GgafDx9GeometryMover : public GgafCore::GgafObject {
    double _dummy1, _dummy2, _dummy3;

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9UntransformedActor* _pActor;
    /** �L�����̎���]���p�̕��p(0�`360,000) */
    angle _angRot[3];
    /** ����]���p�̊p���x�i����]���p�ɖ��t���[�����Z������p�j */
    angvelo _angveloRot[3];
    /** ����]���p�̊p���x���(�ō��l��360,000) */
    angvelo _angveloTopRot[3];
    /** ����]���p�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloBottomRot[3];
    /** ����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRot[3];
    /** �ڕW�̎���]���p������~�@�\�L���t���O */
    bool _auto_rot_angle_targeting_flg[3];
    /** �ڕW�Ƃ���L�����̎���]���p�̕��p(0�`360,000) */
    angle _angAutoTargetRot[3];
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
    int _auto_rot_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
    angvelo _auto_rot_angle_target_allow_velocity[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9GeometryMover(GgafDx9UntransformedActor* prm_pActor);

    /**
     * ���p���ȒP�ɂ���B
     * @param prm_ang ���p
     * @return �ȒP�ɂ��ꂽ���p
     */
    static angle simplifyAngle(angle prm_ang);

    /**
     * Actor�̎��̉�]���p��ݒ�B<BR>
     *
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRot	���p(-360,000�`360,000)
     */
    void setRotAngle(int prm_axis, angle prm_angRot);

    /**
     * Actor�̎��̉�]���p��Ώۍ��W�Ɍ�����B<BR>
     * �����̍��W���Ɍ����悤��Z��Y���iRz �� Ry�j�̉�]�l��ݒ肵�܂��B
     * @param prm_tX �Ώ�X���W
     * @param prm_tY �Ώ�Y���W
     * @param prm_tZ �Ώ�Z���W
     */
    void setRotAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * ���݂� Actor �̎��̉�]���p�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A���Ɖ�]���p�����ł��BActor�̉�]���p�i_angRot�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̉�]���p���͈͊O�i0�`360,000�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRotAngle(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j�����]���p�́A��]�����x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _iBottom_RotVelocityAngle �� �����̉�]�p�l���� �� _angveloTopRot  �ł��B<BR>
     *
     * �����͈͊O�̈����̉�]���p�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(synchronize_ZaxisRotAngle_to_RotAngle_Flg)�̏ꍇ�A<BR>
     * ���Z��̉�]���p�̒l���AZ���̖ڕW�̉�]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �����̉�]���p���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�������Ȏ���]���邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̉�]���p���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A��������]���邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g�̉�]�����x�̏���Ɖ����i_iBottom_RotVelocityAngle�A_angveloTopRot) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�w�莲�ɂ��Ăǂ�ȉ�]���p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	��]���p����(�͈́F_iBottom_RotVelocityAngle �` _angveloTopRot)
     */
    void addRotAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ���̉�]���p�ɂȂ�܂ŁA��]���p�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A���݂̉�]���p�̊p���x�i_angveloRot[prm_axis]�j�̐����Ō��肳��܂��B<BR>
     * ��]���p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
     * �����I�ɂ́AaddRotAngle(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉�������܂��B<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	���B�ڕW�̉�]���p(0�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ��]����
     * @param	prm_angveloAllowRyMove ������~�@�\���L���ɂȂ��]�p���x
     */
    void setAutoTargetRotAngle(int prm_axis,
                               angle prm_angAutoTargetRot,
                               int prm_way_allow = TURN_BOTH,
                               angvelo prm_angveloAllow = ANGLE180);

    /**
     * Actor�̖ڕW��]����������~�@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_tX	�Ώ�X���W
     * @param	prm_tY	�Ώ�Y���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ��]����
     * @param	prm_angveloAllowRyMove ������~�@�\���L���ɂȂ��]�p���x
     */
    void setAutoTargetRotAngleV(int prm_axis,
                            int prm_tX,
                            int prm_tY,
                            int prm_way_allow = TURN_BOTH,
                            angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRotAngleVelocity(int prm_axis, angvelo prm_angveloRot);

    void setRotAngleVelocityRenge(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setRotAngleAcceleration(int prm_axis, angacce prm_angacceRot);

    angle getDistanceFromRotAngleTo(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getDistanceFromRotAngleTo(int prm_axis, angle prm_angAutoTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER
public:
    /** �L�����̈ړ����p�P�ʃx�N�g�� */
    double _vX, _vY, _vZ;
    /** �ړ����p��Z����]�p */
    angle _angRzMove;
    /** �ړ����p��Y����]�p */
    angle _angRyMove;
    /** �ړ����x */
    velo _veloMove;
    /** �ړ����x��� */
    velo _veloTopMove;
    /** �ړ����x���� */
    velo _veloBottomMove;
    /** �ړ������x */
    acce _accMove;

    ///////�R�s�[��begin
    /** �ړ����p�iZ����]�j�̊p���x�i�ړ����p�iZ����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angveloRzMove;
    /** �ړ����p�iZ����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRzTopMove;
    /** �ړ����p�iZ����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRzBottomMove;
    /** �ړ����p�iZ����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRzMove;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\�L���t���O */
    bool _auto_move_angle_rz_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iZ����]�j�̕��p(0�`360,000) */
    angle _angAutoTargetRzMove;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _auto_move_angle_rz_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_ZRotAngle_to_RzMoveAngle_flg;
    //true  : �ړ����p�iZ����]�j��ύX����ƁA����ɔ����������p��Z������]���p�ɂ��ݒ肳���
    //false : �ړ����p�iZ����]�j��Z������]���p�͓Ɨ�
    ////////�R�s�[��end

    ///////�R�s�[��begin
    /** �ړ����p�iY����]�j�̊p���x�i�ړ����p�iY����]�j�ɖ��t���[�����Z������p�j */
    angle _angveloRyMove;
    /** �ړ����p�iY����]�j�̊p���x���(�ō��l��360,000) */
    angle _angveloRyTopMove;
    /** �ړ����p�iY����]�j�̊p���x����(�ō��l��-360,000) */
    angle _angveloRyBottomMove;
    /** �ړ����p�iY����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRyMove;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\�L���t���O */
    bool _auto_move_angle_ry_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iY����]�j�̕��p(0�`360,000) */
    int _angAutoTargetRyMove;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _auto_move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    int _auto_move_angle_ry_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_YRotAngle_to_RyMoveAngle_flg;
    //true  : �ړ����p�iY����]�j��ύX����ƁA����ɔ����������p��Z������]���p�ɂ��ݒ肳���
    //false : �ړ����p�iY����]�j��Z������]���p�͓Ɨ�
    ////////�R�s�[��end

    /** X�������ړ����x */
    velo _veloVxMove;
    /** X�������ړ����x��� */
    velo _veloTopVxMove;
    /** X�������ړ����x���� */
    velo _veloBottomVxMove;
    /** X�������ړ������x */
    acce _acceVxMove;
    /** Y�������ړ����x */
    velo _veloVyMove;
    /** Y�������ړ����x��� */
    velo _veloTopVyMove;
    /** Y�������ړ����x���� */
    velo _veloBottomVyMove;
    /** Y�������ړ������x */
    acce _acceVyMove;
    /** Z�������ړ����x */
    velo _veloVzMove;
    /** Z�������ړ����x��� */
    velo _veloTopVzMove;
    /** Z�������ړ����x���� */
    velo _veloBottomVzMove;
    /** Z�������ړ������x */
    acce _acceVzMove;

    /**
     * Actor��Z���ړ��X�s�[�h��ݒ�<BR>
     * @param	prm_veloMove	Z���ړ��X�s�[�h
     */
    void setMoveVelocity(velo prm_veloMove);

    void addMoveVelocity(velo prm_veloMove_Offset);

    void setMoveVelocityRenge(velo prm_veloMove01, velo prm_veloMove02);

    void setMoveAcceleration(acce prm_acceMove);

    ///////�R�s�[��begin

    /**
     * Actor�̈ړ����p�iZ����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iZ����]�j�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRzMove	�ړ����p�iZ����]�j(0�`360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actor�̈ړ����p�iZ����]�j������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iZ����]�j�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_tX	�Ώ�xZ�����W
     * @param	prm_tY	�Ώ�yZ�����W
     */
    void setRzMoveAngle(int prm_tX, int prm_tY);

    /**
     * ���݂� Actor �̈ړ����p�iZ����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iZ����]�j�̑����ł��BActor�̈ړ����p�iZ����]�j�i_angRzMove�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRzMoveAngle(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iZ����]�j�́AZ���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _angveloRzBottomMove �� �����̓����p���� �� _angveloRzTopMove  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iZ����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iZ����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �����̈ړ����p�iZ����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iZ����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Z���ړ������x�̏���Ɖ����i_angveloRzBottomMove�A_angveloRzTopMove) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iZ����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_angDistance	�ړ����p�iZ����]�j����(�͈́F_angveloRzBottomMove �` _angveloRzTopMove)
     */
    void addRzMoveAngle(angle prm_angDistance);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iZ����]�j�ɂȂ�܂ŁA�ړ����p�iZ����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iZ����]�j�̊p���x�i_angveloRzMove�j�̐����Ō��肳��܂��B<BR>
     * �ړ����p�iZ����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
     * �����I�ɂ́AaddRzMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iZ����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iZ����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRzMove	���B�ڕW�̈ړ����p�iZ����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setAutoTargetRzMoveAngle(angle prm_angRzMove,
                                  int _auto_move_angle_rz_target_allow_way = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j������Z�����W����̑Ώ�Z�����W�Őݒ�)<BR>
     * �@�\��setAutoTargetRzMoveAngle(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRz���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setAutoTargetRzMoveAngleV(int prm_tX,
                               int prm_tY,
                               int _auto_move_angle_rz_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRzMoveAngleVelocity(angvelo prm_angveloRzMove);

    void setRzMoveAngleVelocityRenge(angvelo prm_angveloRzMove01, angvelo prm_angveloRzMove02);

    void setRzMoveAngleAcceleration(angacce prm_angacceRzMove);

    angle getDistanceFromRzMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    angle getDistanceFromRzMoveAngleTo(angle prm_angAutoTargetRzMove, int prm_way);
    ///�R�s�[��end

    ///////�R�s�[��begin

    /**
     * Actor�̈ړ����p�iY����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iY����]�j�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRyMove	�ړ����p�iY����]�j(0�`360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actor�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iY����]�j�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_tX	�Ώ�xY�����W
     * @param	prm_tY	�Ώ�yY�����W
     */
    void setRyMoveAngle(int prm_tX, int prm_tY);

    /**
     * ���݂� Actor �̈ړ����p�iY����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iY����]�j�̑����ł��BActor�̈ړ����p�iY����]�j�i_angRyMove�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRyMoveAngle(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iY����]�j�́AY���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _angveloRyBottomMove �� �����̓����p���� �� _angveloRyTopMove  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iY����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iY����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �����̈ړ����p�iY����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iY����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Y���ړ������x�̏���Ɖ����i_angveloRyBottomMove�A_angveloRyTopMove) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iY����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_angDistance	�ړ����p�iY����]�j����(�͈́F_angveloRyBottomMove �` _angveloRyTopMove)
     */
    void addRyMoveAngle(angle prm_angDistance);

    /**
     * Actor�̖ڕW�̈ړ����p�iY����]�j������~�@�\��L��(�ڕW�̈ړ����p�iY����]�j�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iY����]�j�ɂȂ�܂ŁA�ړ����p�iY����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iY����]�j�̊p���x�i_angveloRyMove�j�̐����Ō��肳��܂��B<BR>
     * �ړ����p�iY����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
     * �����I�ɂ́AaddRyMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iY����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iY����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRyMove	���B�ڕW�̈ړ����p�iY����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setAutoTargetRyMoveAngle(angle prm_angRyMove,
                              int _auto_move_angle_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iY����]�j������~�@�\��L��(�ڕW�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�Őݒ�)<BR>
     * �@�\��setAutoTargetRyMoveAngle(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRy���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setAutoTargetRyMoveAngleV(int prm_tX,
                               int prm_tY,
                               int _auto_move_angle_ry_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRyMoveAngleVelocity(angvelo prm_angveloRyMove);

    void setRyMoveAngleVelocityRenge(angvelo prm_angveloRyMove01, angvelo prm_angveloRyMove02);

    void setRyMoveAngleAcceleration(angacce prm_angacceRyMove);

    angle getDistanceFromRyMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    angle getDistanceFromRyMoveAngleTo(angle prm_angAutoTargetRyMove, int prm_way);
    ///�R�s�[��end

    void setRzRyMoveAngle(angle prm_angRz, angle prm_angRy);

    void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setMoveAngle(GgafDx9UntransformedActor* prm_pActor_Target);

    void setAutoTargetMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setAutoTargetMoveAngle(GgafDx9UntransformedActor* prm_pActor_Target);

    /**
     * ���t���[����Actor�̐U�镑���B<BR>
     * �{�C���^�[�t�F�[�X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
     * behave() �̋�̓I�Ȗ��t���[���̏����͈ȉ��̒ʂ�B<BR>
     * �E�����x(_accMove)��0�łȂ��ꍇ�A�����x�ɂ��X�s�[�h���������B<BR>
     * �@�@�����Z��̃X�s�[�h�� setMoveVelocity(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW�̈ړ����p�iZ����]�j������~�@�\���g�p���̏ꍇ�A�ړ����p�iZ����]�j�ύX����<BR>
     * �@�@���v�Z���ꂽ�ړ����p�iZ����]�j�� addRzMoveAngle(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW�̈ړ����p�iZ����]�j������~�@�\�g�p���ł͂Ȃ��ꍇ�A���ʈړ����p�iZ����]�j���Z����<BR>
     * �@�@��addRzMoveAngle(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW�̎���]���p������~�@�\�g�p���̏ꍇ�A����]���p�ύX����<BR>
     * �@�@���v�Z���ꂽ����]���p�� addRotAngle(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW�̎���]���p������~�@�\���g�p���ł͂Ȃ��ꍇ�A���ʎ���]���p���Z����<BR>
     * �@�@��addRotAngle(int) �����t���[�����s����܂��B<BR>
     * �ȏ�̏������s������AActor�̈ȉ��̃����o�ցA���W�������AZ����]����ݒ肵�܂��B<BR>
     *  _X ��� �ړ����p�iZ����]�j��Z���ړ��X�s�[�h����X���W�����v�Z�����Z<BR>
     *  _Y ��� �ړ����p�iZ����]�j��Z���ړ��X�s�[�h����Y���W�����v�Z�����Z<BR>
     *  _Z ���_veloVzMove �����Z
     *  _RX   ��� ����]���p����<BR>
     *  _RY   ��� ����]���p����<BR>
     *  _RZ   ��� ����]���p����<BR>
     * �y�K���l���ݒ肳��郁���o�[�z<BR>
     * _veloMove,<BR>
     * _pActor->_X += _vX_Move*_veloMove/LEN_UNIT;<BR>
     * _pActor->_Y += _vY_Move*_veloMove/LEN_UNIT;<BR>
     * _pActor->_Z += _veloVzMove
     */
    //virtual void behave();

    void setVxMoveVelocity(velo prm_veloVxMove);
    void setVxMoveVelocityRenge(velo prm_veloVxMove01, velo prm_veloVxMove02);
    void setVxMoveAcceleration(acce prm_acceVxMove);

    void setVyMoveVelocity(velo prm_veloVyMove);
    void setVyMoveVelocityRenge(velo prm_veloVyMove01, velo prm_veloVyMove02);
    void setVyMoveAcceleration(acce prm_acceVyMove);

    void setVzMoveVelocity(velo prm_veloVzMove);
    void setVzMoveVelocityRenge(velo prm_veloVzMove01, velo prm_veloVzMove02);
    void setVzMoveAcceleration(acce prm_acceVzMove);

    /**
     * ���t���[����Actor�̐U�镑���B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryMover();
};

}
#endif /*GGAFDX9GEOMETRYMOVER_H_*/

