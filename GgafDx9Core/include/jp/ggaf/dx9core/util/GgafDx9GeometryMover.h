#ifndef GGAFDX9GEOMETRYMOVER_H_
#define GGAFDX9GEOMETRYMOVER_H_
namespace GgafDx9Core {

//�߂������ɉ�]
#define TURN_CLOSE_TO 0
//���������ɉ�]
#define TURN_ANTICLOSE_TO 2
//���v���ɉ�]
#define TURN_CLOCKWISE (-1)
//�����v���ɉ�]
#define TURN_COUNTERCLOCKWISE 1
//�ǂ���̉�]�ł��󂯓����
#define TURN_BOTH 0

//��X
#define AXIS_X 0
//��Y
#define AXIS_Y 1
//��Z
#define AXIS_Z 2


/**
 * ���W�v�Z�x���N���X.
 * GgafDx9GeometricActor �̃����o��<BR>
 *  _X ,  _Y,  _Z  ��� �A�N�^�[�̍��W<BR>
 * _RX , _RY, _RZ  ��� �A�N�^�[�̎���]�p�x<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 */
class GgafDx9GeometryMover : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;
    /** �X�v���C���v���O����  */
    GgafDx9SplineProgram* _progSP;

    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor);



public: //_RX , _RY, _RZ ����֘A //////////////////////////////////////////////

    /** �L�����̎���]���p�̕��p(0�`360,000) */
    angle _angFace[3];
    /** ����]���p�̊p���x�i����]���p�ɖ��t���[�����Z������p�j */
    angvelo _angveloRotFace[3];
    /** ����]���p�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRotTopFace[3];
    /** ����]���p�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRotBottomFace[3];
    /** ����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRotFace[3];
    /** �ڕW�̎���]���p������~�@�\�L���t���O */
    bool _face_angle_targeting_flg[3];
    /** �ڕW�Ƃ���L�����̎���]���p�̕��p(0�`360,000) */
    angle _angTargetRotFace[3];
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
    int _face_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
    angvelo _face_angle_target_allow_velocity[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���z



    /**
     * �A���O���l��P��������B
     * ���̃A���O���l�A����360,000�ȏ�̃A���O���l���A0�`269,999 �ɕϊ����܂��B
     * @param prm_ang ���p
     * @return �P�������ꂽ�A���O���l
     */
    static angle simplifyAngle(angle prm_ang);

    /**
     * Actor�̎��̉�]���p��ݒ�B<BR>
     * @param	prm_axis	��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angFace	���p�̃A���O���l(-360,000�`360,000)
     */
    void setFaceAngle(int prm_axis, angle prm_angFace);

    /**
     * Actor�̎��̉�]���p��Ώۍ��W�Ɍ�����B<BR>
     * @param prm_tX �Ώ�X���W
     * @param prm_tY �Ώ�Y���W
     * @param prm_tZ �Ώ�Z���W
     */
    void setFaceAngle(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * ���݂� Actor �̎���]���p�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A����]���p�̑����ł��BActor�̎���]���p�i_angFace�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̎���]���p�̃A���O���l�͂��P��������܂��B
     * �����ł�����Z�i���Z�j���鎲��]���p�́A����]�p�p���x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _iBottom_RotVelocityAngle �� �����̉�]�����p�l�̑��� �� _angveloTopRot  �ł��B<BR>
     *
     * �������Z�i���Z�j��A�͈͊O�ɂȂ����ꍇ�A���߂͈͓̔��̒l�ɋ����I�ɗ}�����܂��B<BR>
     * �y�⑫�F�z<BR>
     * �f�t�H���g�̉�]�����x�̏���Ɖ����i_iBottom_RotVelocityAngle�A_angveloTopRot) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	��]�����p�l�̑����A���O���l(�͈́F_iBottom_RotVelocityAngle �` _angveloTopRot)
     */
    void addFaceAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ����]���p�ɂȂ�ƁA����]���p�p���x�y�ю���]���p�p�����x�� 0 �ɂ��A��]���~�����܂��B<BR>
     * ����]���p�p���x���̐ݒ�𕹂��Ď��s���āA�܂��͎���]���s�Ȃ��Ă��������B<BR>
     * ����]���p�p���x�� 0 �̏ꍇ�A�����N����܂���B�{���\�b�h�����s��������ƌ����ď���Ɍ������ς��ƂƂ����Ӗ��ł͂���܂���B <BR>
     * �����I�ɂ́AaddFaceAngle(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉���(�����̃t���O���A���Z�b�g)����܂��B<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	���B�ڕW�̉�]���p(0�`360,000)
     * @param	prm_way_allow  ������~��������i������(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param	prm_angveloAllowRyMove ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTarget_FaceAngle(int prm_axis,
                           angle prm_angTargetRot,
                           int prm_way_allow = TURN_BOTH,
                           angvelo prm_angveloAllow = ANGLE180);

    /**
     * Actor�̖ڕW��]����������~�@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	�@�@prm_tX	�Ώ�X���W
     * @param	prm_tY	�Ώ�Y���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ��]����
     * @param	prm_angveloAllowRyMove ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTarget_FaceAngleV(int prm_axis,
                                int prm_tX,
                                int prm_tY,
                                int prm_way_allow = TURN_BOTH,
                                angvelo prm_angveloAllowRyMove = ANGLE180);

    void setFaceAngleVelocity(int prm_axis, angvelo prm_angveloRot);

    void setFaceAngleVeloRenge(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setFaceAngleVeloAcceleration(int prm_axis, angacce prm_angacceRot);

    angle getFaceAngleDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getFaceAngleDistance(int prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z ����֘A //////////////////////////////////////////////
    /** �L�����̈ړ����p�P�ʃx�N�g�� */
    float _vX, _vY, _vZ;
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

    /** �ړ����p�iZ����]�j�̊p���x�i�ړ����p�iZ����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angveloRzMove;
    /** �ړ����p�iZ����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRzTopMove;
    /** �ړ����p�iZ����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRzBottomMove;
    /** �ړ����p�iZ����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRzMove;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\�L���t���O */
    bool _move_angle_rz_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iZ����]�j�̕��p(0�`360,000) */
    angle _angTargetRzMove;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _move_angle_rz_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_RzFaceAngle_to_RzMoveAngle_flg;
    //true  : �ړ����p�iZ����]�j��ύX����ƁA����ɔ����������p������]���p(Z��)�ɂ��ݒ肳���
    //false : �ړ����p�iZ����]�j��Z������]���p�͓Ɨ�

    /** �ړ����p�iY����]�j�̊p���x�i�ړ����p�iY����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angveloRyMove;
    /** �ړ����p�iY����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRyTopMove;
    /** �ړ����p�iY����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRyBottomMove;
    /** �ړ����p�iY����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRyMove;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\�L���t���O */
    bool _move_angle_ry_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iY����]�j�̕��p(0�`360,000) */
    int _angTargetRyMove;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    int _move_angle_ry_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_RyFaceAngle_to_RyMoveAngle_flg;
    //true  : �ړ����p�iY����]�j��ύX����ƁA����ɔ����������p������]���p(Y��)�ɂ��ݒ肳���
    //false : �ړ����p�iY����]�j��Y������]���p�͓Ɨ�

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

    void setMoveVeloRenge(velo prm_veloMove01, velo prm_veloMove02);

    void setMoveVeloAcceleration(acce prm_acceMove);


    /**
     * Actor�̈ړ����p�iZ����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_RzFaceAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTarget_FaceAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRzMove	�ړ����p�iZ����]�j(0�`360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actor�̈ړ����p�iZ����]�j������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_RzFaceAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTarget_FaceAngle(int) �����s����܂��B<BR>
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
     * �܂��A�����O�������@�\���L��(_synchronize_RzFaceAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
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
     * <B>�ړ����p�iZ����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRzMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iZ����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iZ����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRzMove	���B�ڕW�̈ړ����p�iZ����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RzMoveAngle(angle prm_angRzMove,
                                      int prm_way_allow = TURN_BOTH,
                                      angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j������Z�����W����̑Ώ�Z�����W�Őݒ�)<BR>
     * �@�\��setStopTarget_RzMoveAngle(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRz���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RzMoveAngleV(int prm_tX,
                                       int prm_tY,
                                       int prm_way_allow = TURN_BOTH,
                                       angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRzMoveAngleVelocity(angvelo prm_angveloRzMove);

    void setRzMoveAngleVeloRenge(angvelo prm_angveloRzMove01, angvelo prm_angveloRzMove02);

    void setRzMoveAngleVeloAcceleration(angacce prm_angacceRzMove);

    angle getRzMoveAngleDistance(int prm_tX, int prm_tY, int prm_way);

    /**
     * ���g�̈ړ����p��Z����]�p( _angRzMove )�ƁA�^�[�Q�b�g�̉�]�p�Ƃ̍������擾.
     * TURN_COUNTERCLOCKWISE ��� ��]�����������ō��يp�擾�A���̒l�ŕԂ�B
     * TURN_CLOCKWISE        ��� ��]�������E���ō��يp�擾�A���̒l�ɕԂ�B
     * TURN_CLOSE_TO         ��� �^�[�Q�b�g�̉�]�p�Ƌ������߂����̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * TURN_ANTICLOSE_TO     �E�E�E�^�[�Q�b�g�̉�]�p�Ƌ������������̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * @param prm_angTargetRzMove �^�[�Q�b�g�p�̒l
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @return
     */
    angle getRzMoveAngleDistance(angle prm_angTargetRzMove, int prm_way);

    /**
     * Actor�̈ړ����p�iY����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_RyFaceAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iY����]�j�Ɠ��������������悤�� setStopTarget_FaceAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRyMove	�ړ����p�iY����]�j(0�`360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actor�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_RyFaceAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iY����]�j�Ɠ��������������悤�� setStopTarget_FaceAngle(int) �����s����܂��B<BR>
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
     * �܂��A�����O�������@�\���L��(_synchronize_RyFaceAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
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
     * <B>�ړ����p�iY����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRyMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iY����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iY����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRyMove	���B�ڕW�̈ړ����p�iY����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RyMoveAngle(angle prm_angRyMove,
                                      int _move_angle_ry_target_allow_way = TURN_BOTH,
                                      angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iY����]�j������~�@�\��L��(�ڕW�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�Őݒ�)<BR>
     * �@�\��setStopTarget_RyMoveAngle(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRy���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RyMoveAngleV(int prm_tX,
                                       int prm_tY,
                                       int _move_angle_ry_target_allow_way = TURN_BOTH,
                                       angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRyMoveAngleVelocity(angvelo prm_angveloRyMove);

    void setRyMoveAngleVeloRenge(angvelo prm_angveloRyMove01, angvelo prm_angveloRyMove02);

    void setRyMoveAngleVeloAcceleration(angacce prm_angacceRyMove);

    angle getRyMoveAngleDistance(int prm_tX, int prm_tY, int prm_way);

    angle getRyMoveAngleDistance(angle prm_angTargetRyMove, int prm_way);

    /**
     * �ܓx�o�x�w��ňړ�������ݒ�B.
     * @param prm_angRz
     * @param prm_angRy
     */
    void setRzRyMoveAngle(angle prm_angRz, angle prm_angRy);

    /**
     * �ڕW���W�w��ňړ����p��ݒ�B.
     * �����x�N�g�����K���������ōs�Ȃ��B
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setMoveAngle(GgafDx9GeometricActor* prm_pActor_Target);

    void setStopTarget_RzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setStopTarget_RzRyMoveAngle(GgafDx9GeometricActor* prm_pActor_Target);

    //virtual void behave();

    void setVxMoveVelocity(velo prm_veloVxMove);
    void setVxMoveVeloRenge(velo prm_veloVxMove01, velo prm_veloVxMove02);
    void setVxMoveVeloAcceleration(acce prm_acceVxMove);

    void setVyMoveVelocity(velo prm_veloVyMove);
    void setVyMoveVeloRenge(velo prm_veloVyMove01, velo prm_veloVyMove02);
    void setVyMoveVeloAcceleration(acce prm_acceVyMove);

    void setVzMoveVelocity(velo prm_veloVzMove);
    void setVzMoveVeloRenge(velo prm_veloVzMove01, velo prm_veloVzMove02);
    void setVzMoveVeloAcceleration(acce prm_acceVzMove);


    /**
     * �X�v���C���v���O�������s
     * @param prm_progSP �X�v���C���v���O����
     * @param prm_option �I�v�V�����BGgafDx9SplineProgram���I�u�W�F�N�g�Ɉˑ�����BGgafDx9SplineProgram�p���N���X���Q�Ƃ���B
     */
    void executeSplineMoveProgram(GgafDx9SplineProgram* prm_progSP, int prm_option);



    /**
     * ����]���p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tX �ڕWX���W
     * @param prm_tY �ڕWY���W
     * @param prm_tZ �ڕWZ���W
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingFaceAngleSequence(int prm_tX, int prm_tY, int prm_tZ,
                                           angvelo prm_angVelocity,
                                           int prm_way);
    /**
     * ����]���p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW����]���p(Z��)
     * @param prm_angRy_Target �ڕW����]���p(Y��)
     * @param prm_angVelocity �^�[�Q�b�g�֎���]���p����]�ړ����ɓK�p����ڕW����]���p��]�ړ��p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingFaceAngleSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                           angvelo prm_angVelocity, int prm_way);

    /**
     * ����]���p��ڕW�Ƀ^�[�Q�b�g�̍��W�ɂ���V�[�N�G���X�����s
     * @param prm_pActor_Target �ڕW�I�u�W�F�N�g
     * @param prm_angVelocity �^�[�Q�b�g���s���ɋ������p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingFaceAngleSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                           angvelo prm_angVelocity,
                                           int prm_way = TURN_CLOSE_TO) {
        executeTagettingFaceAngleSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelocity,
                prm_way
        );
    }




    /**
     * ����]���p(Z��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW����]���p(Z��)
     * @param prm_angVelocity �^�[�Q�b�g�֎���]���p����]�ړ����ɓK�p����ڕW����]���p��]�ړ��p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRzFaceAngleSequence(angle prm_angRz_Target, angvelo prm_angVelocity, int prm_way);

    /**
     * ����]���p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRy_Target �ڕW����]���p(Y��)
     * @param prm_angVelocity �^�[�Q�b�g�֎���]���p����]�ړ����ɓK�p����ڕW����]���p��]�ړ��p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRyFaceAngleSequence(angle prm_angRy_Target, angvelo prm_angVelocity, int prm_way);




    void executeTagettingRxSpinAngleSequence(angle prm_angRx_Target, angvelo prm_angVelocity, int prm_way);



    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tX �ڕWX���W
     * @param prm_tY �ڕWY���W
     * @param prm_tZ �ڕWZ���W
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingMoveAngleSequence(int prm_tX, int prm_tY, int prm_tZ,
                                           angvelo prm_angVelocity,
                                           int prm_way);
    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW�ړ����p(Z��)
     * @param prm_angRy_Target �ڕW�ړ����p(Y��)
     * @param prm_angVelocity �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingMoveAngleSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                           angvelo prm_angVelocity, int prm_way);

    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g�̍��W�ɂ���V�[�N�G���X�����s
     * @param prm_pActor_Target �ڕW�I�u�W�F�N�g
     * @param prm_angVelocity �^�[�Q�b�g���s���ɋ������p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingMoveAngleSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                           angvelo prm_angVelocity,
                                           int prm_way = TURN_CLOSE_TO) {
        executeTagettingMoveAngleSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelocity,
                prm_way
        );
    }

    /**
     * �ړ����p(Z��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW�ړ����p(Z��)
     * @param prm_angVelocity �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRzMoveAngleSequence(angle prm_angRz_Target, angvelo prm_angVelocity, int prm_way);

    /**
     * �ړ����p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRy_Target �ڕW�ړ����p(Y��)
     * @param prm_angVelocity �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void executeTagettingRyMoveAngleSequence(angle prm_angRy_Target, angvelo prm_angVelocity, int prm_way);

    /**
     * ���t���[����Actor�̐U�镑���B<BR>
     * �{�N���X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryMover();
};

}
#endif /*GGAFDX9GEOMETRYMOVER_H_*/

