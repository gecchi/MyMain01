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
    /** �L�����̎���]���p�̕��p�l(0�`360,000) */
    angle _angRot[3];
    /** ����]���p�̊p���x�i����]���p�l�ɖ��t���[�����Z������p�l�j */
    angvelo _angveloRot[3];
    /** ����]���p�l�̊p���x���(�ō��l��360,000) */
    angvelo _angveloTopRot[3];
    /** ����]���p�l�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloBottomRot[3];
    /** ����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRot[3];
    /** �ڕW�̎���]���p������~�@�\�L���t���O */
    bool _auto_rot_angle_target_Flg[3];
    /** �ڕW�Ƃ���L�����̎���]���p�̕��p�l(0�`360,000) */
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
     * ���p�l���ȒP�ɂ���B
     * @param prm_ang ���p�l
     * @return �ȒP�ɂ��ꂽ���p�l
     */
    angle simplifyAngle(angle prm_ang);

    /**
     * Actor�̎��̉�]���p�l��ݒ�B<BR>
     *
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRot	���p�l(-360,000�`360,000)
     */
    void setRotAngle(int prm_axis, angle prm_angRot);

    /**
     * Actor�̎��̉�]���p�l��Ώۍ��W�Ɍ�����B<BR>
     * �����̍��W���Ɍ����悤��Z��Y���iRz �� Ry�j�̉�]�l��ݒ肵�܂��B
     * @param prm_tX �Ώ�X���W
     * @param prm_tY �Ώ�Y���W
     * @param prm_tZ �Ώ�Z���W
     */
    void setRotAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * ���݂� Actor �̎��̉�]���p�l�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A���Ɖ�]���p�l�����ł��BActor�̉�]���p�l�i_angRot�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̉�]���p�l���͈͊O�i0�`360,000�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRotAngle(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j�����]���p�l�́A��]�����x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _iBottom_RotVelocityAngle �� �����̉�]�p�l���� �� _angveloTopRot  �ł��B<BR>
     *
     * �����͈͊O�̈����̉�]���p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(synchronize_ZaxisRotAngle_to_RotAngle_Flg)�̏ꍇ�A<BR>
     * ���Z��̉�]���p�l�̒l���AZ���̖ڕW�̉�]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �����̉�]���p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�������Ȏ���]���邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̉�]���p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A��������]���邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g�̉�]�����x�̏���Ɖ����i_iBottom_RotVelocityAngle�A_angveloTopRot) ��<BR>
     *
     *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�w�莲�ɂ��Ăǂ�ȉ�]���p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	��]���p�l����(�͈́F_iBottom_RotVelocityAngle �` _angveloTopRot)
     */
    void addRotAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�l�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ���̉�]���p�l�ɂȂ�܂ŁA��]���p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A���݂̉�]���p�̊p���x�i_angveloRot[prm_axis]�j�̐����Ō��肳��܂��B<BR>
     * ��]���p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
     * �����I�ɂ́AaddRotAngle(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉�������܂��B<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	���B�ڕW�̉�]���p�l(0�`360,000)
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
    /** �ړ����p��Z����]�p���x */
    angle _angRzMove;
    /** �ړ����p��Y����]�p���x */
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
    /** Z���ړ����p�̊p���x�iZ���ړ����p�l�ɖ��t���[�����Z������p�l�j */
    angvelo _angveloRzMove;
    /** Z���ړ����p�l�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRzTopMove;
    /** Z���ړ����p�l�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRzBottomMove;
    /** Z���ړ����p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRzMove;
    /** �ڕW��Z���ړ����p������~�@�\�L���t���O */
    bool _auto_move_angle_rz_target_Flg;
    /** �ڕW�Ƃ���L������Z���ړ����p�̕��p�l(0�`360,000) */
    angle _angAutoTargetRzMove;
    /** �ڕW��Z���ړ����p������~�@�\���L���ɂȂ�i����]���� */
    int _auto_move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW��Z���ړ����p������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _auto_move_angle_rz_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_ZRotAngle_to_RzMoveAngle_Flg;
    //true  : Z���ړ����p��ύX����ƁA����ɔ����������p�l��Z������]���p�ɂ��ݒ肳���
    //false : Z���ړ����p��Z������]���p�͓Ɨ�
    ////////�R�s�[��end

    ///////�R�s�[��begin
    /** Y���ړ����p�̊p���x�iY���ړ����p�l�ɖ��t���[�����Z������p�l�j */
    angle _angveloRyMove;
    /** Y���ړ����p�l�̊p���x���(�ō��l��360,000) */
    angle _angveloRyTopMove;
    /** Y���ړ����p�l�̊p���x����(�ō��l��-360,000) */
    angle _angveloRyBottomMove;
    /** Y���ړ����p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRyMove;
    /** �ڕW��Y���ړ����p������~�@�\�L���t���O */
    bool _auto_move_angle_ry_target_Flg;
    /** �ڕW�Ƃ���L������Y���ړ����p�̕��p�l(0�`360,000) */
    int _angAutoTargetRyMove;
    /** �ڕW��Y���ړ����p������~�@�\���L���ɂȂ�i����]���� */
    int _auto_move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW��Y���ړ����p������~�@�\���L���ɂȂ�ړ����p�p���x */
    int _auto_move_angle_ry_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_YRotAngle_to_RyMoveAngle_Flg;
    //true  : Y���ړ����p��ύX����ƁA����ɔ����������p�l��Z������]���p�ɂ��ݒ肳���
    //false : Y���ړ����p��Z������]���p�͓Ɨ�
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
     * Actor��Z���ړ����p�l��ݒ�B<BR>
     * ���Z���Z���ړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_Flg)�̏ꍇ�A<BR>
     * Actor�̌�����Z���ړ����p�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRzMove	Z���ړ����p�l(0�`360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actor��Z���ړ����p�l������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_Flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�l�i�����j��Z���ړ����p�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_tX	�Ώ�xZ�����W
     * @param	prm_tY	�Ώ�yZ�����W
     */
    void setRzMoveAngle(int prm_tX, int prm_tY);

    /**
     * ���݂� Actor ��Z���ړ����p�l�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́AZ���ړ����p�l�̑����ł��BActor��Z���ړ����p�l�i_angRzMove�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z���Z���ړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRzMoveAngle(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����Z���ړ����p�l�́AZ���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _angveloRzBottomMove �� �����̓����p�l���� �� _angveloRzTopMove  �ł��B<BR>
     *
     * �����͈͊O�̈�����Z���ړ����p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_Flg)�̏ꍇ�A<BR>
     * ���Z���Z���ړ����p�l�̒l���AZ���̖ڕW�̎���]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * ������Z���ړ����p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA������Z���ړ����p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Z���ړ������x�̏���Ɖ����i_angveloRzBottomMove�A_angveloRzTopMove) ��<BR>
     *
     *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ��Z���ړ����p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_angDistance	Z���ړ����p�l����(�͈́F_angveloRzBottomMove �` _angveloRzTopMove)
     */
    void addRzMoveAngle(angle prm_angDistance);

    /**
     * Actor�̖ڕW��Z���ړ����p������~�@�\��L��(�ڕW��Z���ړ����p�l�ݒ�)<BR>
     * �����ɐݒ肳�ꂽZ���ړ����p�l�ɂȂ�܂ŁAZ���ړ����p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́AZ���ړ����p�̊p���x�i_angveloRzMove�j�̐����Ō��肳��܂��B<BR>
     * Z���ړ����p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
     * �����I�ɂ́AaddRzMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW��Z���ړ����p�ɓ��B�����Ȃ�΁A���̖ڕW��Z���ړ����p������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRzMove	���B�ڕW��Z���ړ����p�l(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setAutoTargetRzMoveAngle(angle prm_angRzMove,
                                  int _auto_move_angle_rz_target_allow_way = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW��Z���ړ����p������~�@�\��L��(�ڕW��Z���ړ����p������Z�����W����̑Ώ�Z�����W�Őݒ�)<BR>
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
     * Actor��Y���ړ����p�l��ݒ�B<BR>
     * ���Z���Y���ړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_Flg)�̏ꍇ�A<BR>
     * Actor�̌�����Y���ړ����p�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRyMove	Y���ړ����p�l(0�`360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actor��Y���ړ����p�l������Y�����W����̑Ώ�Y�����W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_Flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�l�i�����j��Y���ړ����p�Ɠ��������������悤�� setAutoTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_tX	�Ώ�xY�����W
     * @param	prm_tY	�Ώ�yY�����W
     */
    void setRyMoveAngle(int prm_tX, int prm_tY);

    /**
     * ���݂� Actor ��Y���ړ����p�l�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́AY���ړ����p�l�̑����ł��BActor��Y���ړ����p�l�i_angRyMove�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z���Y���ړ����p�l���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRyMoveAngle(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����Y���ړ����p�l�́AY���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _angveloRyBottomMove �� �����̓����p�l���� �� _angveloRyTopMove  �ł��B<BR>
     *
     * �����͈͊O�̈�����Y���ړ����p�l�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_Flg)�̏ꍇ�A<BR>
     * ���Z���Y���ړ����p�l�̒l���AZ���̖ڕW�̎���]���p�l�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * ������Y���ړ����p�l���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA������Y���ړ����p�l���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Y���ړ������x�̏���Ɖ����i_angveloRyBottomMove�A_angveloRyTopMove) ��<BR>
     *
     *  -360,000 �� �����̓����p�l���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ��Y���ړ����p�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_angDistance	Y���ړ����p�l����(�͈́F_angveloRyBottomMove �` _angveloRyTopMove)
     */
    void addRyMoveAngle(angle prm_angDistance);

    /**
     * Actor�̖ڕW��Y���ړ����p������~�@�\��L��(�ڕW��Y���ړ����p�l�ݒ�)<BR>
     * �����ɐݒ肳�ꂽY���ړ����p�l�ɂȂ�܂ŁAY���ړ����p�l�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́AY���ړ����p�̊p���x�i_angveloRyMove�j�̐����Ō��肳��܂��B<BR>
     * Y���ړ����p�̊p���x�� 0 �Ȃ�΁A�����N����܂���B<BR>
     * �����I�ɂ́AaddRyMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW��Y���ړ����p�ɓ��B�����Ȃ�΁A���̖ڕW��Y���ړ����p������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRyMove	���B�ڕW��Y���ړ����p�l(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setAutoTargetRyMoveAngle(angle prm_angRyMove,
                              int _auto_move_angle_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW��Y���ړ����p������~�@�\��L��(�ڕW��Y���ړ����p������Y�����W����̑Ώ�Y�����W�Őݒ�)<BR>
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

    void setAutoTargetMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * ���t���[����Actor�̐U�镑���B<BR>
     * �{�C���^�[�t�F�[�X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
     * behave() �̋�̓I�Ȗ��t���[���̏����͈ȉ��̒ʂ�B<BR>
     * �E�����x(_accMove)��0�łȂ��ꍇ�A�����x�ɂ��X�s�[�h���������B<BR>
     * �@�@�����Z��̃X�s�[�h�� setMoveVelocity(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW��Z���ړ����p������~�@�\���g�p���̏ꍇ�AZ���ړ����p�ύX����<BR>
     * �@�@���v�Z���ꂽZ���ړ����p�l�� addRzMoveAngle(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW��Z���ړ����p������~�@�\�g�p���ł͂Ȃ��ꍇ�A����Z���ړ����p�l���Z����<BR>
     * �@�@��addRzMoveAngle(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW�̎���]���p������~�@�\�g�p���̏ꍇ�A����]���p�ύX����<BR>
     * �@�@���v�Z���ꂽ����]���p�l�� addRotAngle(int) �����t���[�����s����܂��B<BR>
     * �E�ڕW�̎���]���p������~�@�\���g�p���ł͂Ȃ��ꍇ�A���ʎ���]���p�l���Z����<BR>
     * �@�@��addRotAngle(int) �����t���[�����s����܂��B<BR>
     * �ȏ�̏������s������AActor�̈ȉ��̃����o�ցA���W�������AZ����]����ݒ肵�܂��B<BR>
     *  _X ��� Z���ړ����p�l��Z���ړ��X�s�[�h����X���W�����v�Z�����Z<BR>
     *  _Y ��� Z���ړ����p�l��Z���ړ��X�s�[�h����Y���W�����v�Z�����Z<BR>
     *  _Z ���_veloVzMove �����Z
     *  _RX   ��� ����]���p�l����<BR>
     *  _RY   ��� ����]���p�l����<BR>
     *  _RZ   ��� ����]���p�l����<BR>
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

