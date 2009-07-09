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
 * ���W�v�Z�x���N���X.
 * GgafDx9GeometricActor �̃����o��<BR>
 *  _X ,  _Y,  _Z  ��� �A�N�^�[�̍��W<BR>
 * _RX , _RY, _RZ  ��� �A�N�^�[�̎���]�p�x<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 */
class GgafDx9GeometryMover : public GgafCore::GgafObject {
    double _dummy1, _dummy2, _dummy3;

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;

public: //_RX , _RY, _RZ ����֘A //////////////////////////////////////////////

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
    bool _rot_angle_targeting_flg[3];
    /** �ڕW�Ƃ���L�����̎���]���p�̕��p(0�`360,000) */
    angle _angTargetRot[3];
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
    int _rot_angle_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
    angvelo _rot_angle_target_allow_velocity[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���z

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9GeometryMover(GgafDx9GeometricActor* prm_pActor);

    /**
     * �A���O���l��P��������B
     * ���̃A���O���l�A����360,000�ȏ�̃A���O���l���A0�`269,999 �ɕϊ����܂��B
     * @param prm_ang ���p
     * @return �P�������ꂽ�A���O���l
     */
    static angle simplifyAngle(angle prm_ang);

    /**
     * Actor�̎��̉�]���p��ݒ�B<BR>
     *
     * @param	prm_axis	��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRot	���p�̃A���O���l(-360,000�`360,000)
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
     * ���݂� Actor �̎���]���p�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A����]���p�̑����ł��BActor�̎���]���p�i_angRot�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
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
    void addRotAngle(int prm_axis, angle prm_angDistance);

    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ����]���p�ɂȂ�ƁA����]���p�p���x�y�ю���]���p�p�����x�� 0 �ɂ��A��]���~�����܂��B<BR>
     * ����]���p�p���x���̐ݒ�𕹂��Ď��s���āA�܂��͎���]���s�Ȃ��Ă��������B<BR>
     * ����]���p�p���x�� 0 �̏ꍇ�A�����N����܂���B�{���\�b�h�����s��������ƌ����ď���Ɍ������ς��ƂƂ����Ӗ��ł͂���܂���B <BR>
     * �����I�ɂ́AaddRotAngle(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉���(�����̃t���O���A���Z�b�g)����܂��B<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angRzMove	���B�ڕW�̉�]���p(0�`360,000)
     * @param	prm_way_allow  ������~��������i������(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param	prm_angveloAllowRyMove ������~�@�\���L���ɂȂ��]�p���x
     */
    void setTargetRotAngle(int prm_axis,
                           angle prm_angTargetRot,
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
    void setTargetRotAngleV(int prm_axis,
                                int prm_tX,
                                int prm_tY,
                                int prm_way_allow = TURN_BOTH,
                                angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRotAngleVelocity(int prm_axis, angvelo prm_angveloRot);

    void setRotAngleVelocityRenge(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setRotAngleAcceleration(int prm_axis, angacce prm_angacceRot);

    angle getDifferenceFromRotAngleTo(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getDifferenceFromRotAngleTo(int prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z ����֘A //////////////////////////////////////////////
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
    bool _move_angle_rz_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iZ����]�j�̕��p(0�`360,000) */
    angle _angTargetRzMove;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _move_angle_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _move_angle_rz_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_ZRotAngle_to_RzMoveAngle_flg;
    //true  : �ړ����p�iZ����]�j��ύX����ƁA����ɔ����������p������]���p(Z��)�ɂ��ݒ肳���
    //false : �ړ����p�iZ����]�j��Z������]���p�͓Ɨ�

    //�y���������z
    //������]���p�A�ړ����p�Ƃ������t�ɂ��ā�
    //�u����]���p�v�̓L�����̌����݂̂�\����B
    //�u�ړ����p�v�̓L�����̐i�s�����݂̂�\����B
    //��ʂŃL�����N�^���ォ�牺�ֈړ����Ă��A���������Ƃ͌���Ȃ��B
    //�E�ɃL�������������Ă���ړ��J�n�Ƃ��Ă��A���Ɉړ����邩������Ȃ��B���ꂼ��ݒ肪�K�v�B
    //
    //��Z����]�p�AY����]�p�Ƃ������t�ɂ��ā�
    //�u�ړ����p�v�̕����́A���_����P�ʋ��̕\�ʂɌ������ĐL�т�x�N�g���ŕ\���B
    //�����x�N�g���͒P�ʋ��̕\�ʂ����W�w��(_vX, _vY, _vZ)�ƁA�ܓx�o�x�̍��W�̂ǂ���ł��w�肷�邱�ł���悤�ɂ��Ă���B
    //�����ňܓx�o�x�\���̏ꍇ�A�ܓx��Z����]�p�A�o�x��Y����]�p�A�ƂȂ邽�߁A�̂Q�̐����𔺂��āu�ړ����p�v�ƌ����ꍇ������B
    //�����ł́A�u�ړ����p�iY���j�v�Ƃ������t�̌�b�́A�L�����̐i�s�����x�N�g����Y����]�p�̐����i�o�x�j���w���Ă��邱�ƂƂ���B
    //����������t�ŁA�u����]���p�iY���j�v�Ə����Ă���ꍇ�́A�L�����̌�����Y����]�p�������w���Ă���B���񂺂�ʂ̈Ӗ��ł���B
    //�u�ړ����p�iZ���j�v�͑��݂��Ȃ����A�u����]���p�iZ���j�v�͓��R���݂���B�������Ȃ��悤�ɁB
    //�ܓx�o�x�w��(_angRzMove, _angRyMove)�ƍ��W�w��(_vX, _vY, _vZ) �̓����ێ������o�ōŏI�I�Ƀ��[���h�ϊ��Ŏg�p�����̂�
    //���W�w��(_vX, _vY, _vZ)�̕��ł���B
    //�{�N���X�̃��\�b�h���g�p�������A����(_angRzMove, _angRyMove)��(_vX, _vY, _vZ) �́A�����͂Ƃ�Ă���B
    //
    //�������O�������@�\��
    //�����O�������@�\�Ƃ́u�ړ����p�v��ݒ肷��ƁA����ɔ����Ď����I�Ɂu����]���p�v��ݒ肷�鎖���Ӗ����Ă���B
    //��̓I�ɂ́A�ȉ��̂悤�Ƀt���[�����ɁA�A���O���l���㏑���R�s�[���Ă��邾���B
    // �E�ړ����p�iZ���j �� ����]���p(Z��)
    // �E�ړ����p�iY���j �� ����]���p(Y��)
    //�������u����]���p�v��ݒ�Ă��u�ړ����p�v�ω����Ȃ��i�֘A���Ȃ��j�B

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
    bool _move_angle_ry_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iY����]�j�̕��p(0�`360,000) */
    int _angTargetRyMove;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _move_angle_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    int _move_angle_ry_target_allow_velocity;
    /** �����O�������@�\�L���t���O */
    bool _synchronize_YRotAngle_to_RyMoveAngle_flg;
    //true  : �ړ����p�iY����]�j��ύX����ƁA����ɔ����������p������]���p(Y��)�ɂ��ݒ肳���
    //false : �ړ����p�iY����]�j��Y������]���p�͓Ɨ�
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
     * Actor�̌������ړ����p�iZ����]�j�Ɠ��������������悤�� setTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRzMove	�ړ����p�iZ����]�j(0�`360,000)
     */
    void setRzMoveAngle(angle prm_angle);

    /**
     * Actor�̈ړ����p�iZ����]�j������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_ZRotAngle_to_RzMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iZ����]�j�Ɠ��������������悤�� setTargetRotAngle(int) �����s����܂��B<BR>
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
     * <B>�ړ����p�iZ����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRzMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iZ����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iZ����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRzMove	���B�ڕW�̈ړ����p�iZ����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setTargetRzMoveAngle(angle prm_angRzMove,
                                  int prm_way_allow = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j������Z�����W����̑Ώ�Z�����W�Őݒ�)<BR>
     * �@�\��setTargetRzMoveAngle(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRz���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setTargetRzMoveAngleV(int prm_tX,
                                   int prm_tY,
                                   int prm_way_allow = TURN_BOTH,
                                   angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRzMoveAngleVelocity(angvelo prm_angveloRzMove);

    void setRzMoveAngleVelocityRenge(angvelo prm_angveloRzMove01, angvelo prm_angveloRzMove02);

    void setRzMoveAngleAcceleration(angacce prm_angacceRzMove);

    angle getDifferenceFromRzMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    /**
     * ���g�̈ړ����p��Z����]�p( _angRzMove )�ƁA�^�[�Q�b�g�̉�]�p�Ƃ̍������擾.
     * TURN_COUNTERCLOCKWISE ��� ��]�����������ō��يp�擾�A���̒l�ŕԂ�B
     * TURN_CLOCKWISE        ��� ��]�������E���ō��يp�擾�A���̒l�ɕԂ�B
     * TURN_CLOSE_TO         ��� �^�[�Q�b�g�̉�]�p�Ƌ������߂��ق��̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * @param prm_angTargetRzMove �^�[�Q�b�g�p�̒l
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO
     * @return
     */
    angle getDifferenceFromRzMoveAngleTo(angle prm_angTargetRzMove, int prm_way);
    ///�R�s�[��end

    ///////�R�s�[��begin

    /**
     * Actor�̈ړ����p�iY����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iY����]�j�Ɠ��������������悤�� setTargetRotAngle(int) �����s����܂��B<BR>
     *
     * @param	prm_angRyMove	�ړ����p�iY����]�j(0�`360,000)
     */
    void setRyMoveAngle(angle prm_angle);

    /**
     * Actor�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_synchronize_YRotAngle_to_RyMoveAngle_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iY����]�j�Ɠ��������������悤�� setTargetRotAngle(int) �����s����܂��B<BR>
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
     * <B>�ړ����p�iY����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRyMoveAngle(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iY����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iY����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRyMove	���B�ڕW�̈ړ����p�iY����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setTargetRyMoveAngle(angle prm_angRyMove,
                              int _move_angle_ry_target_allow_way = TURN_BOTH,
                              angvelo prm_angveloAllowRyMove = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iY����]�j������~�@�\��L��(�ڕW�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�Őݒ�)<BR>
     * �@�\��setTargetRyMoveAngle(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRy���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMove ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setTargetRyMoveAngleV(int prm_tX,
                               int prm_tY,
                               int _move_angle_ry_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMove = ANGLE180);

    void setRyMoveAngleVelocity(angvelo prm_angveloRyMove);

    void setRyMoveAngleVelocityRenge(angvelo prm_angveloRyMove01, angvelo prm_angveloRyMove02);

    void setRyMoveAngleAcceleration(angacce prm_angacceRyMove);

    angle getDifferenceFromRyMoveAngleTo(int prm_tX, int prm_tY, int prm_way);

    angle getDifferenceFromRyMoveAngleTo(angle prm_angTargetRyMove, int prm_way);
    ///�R�s�[��end
    /**
     * �ܓx�o�x�ňړ�������ݒ�B.
     * @param prm_angRz
     * @param prm_angRy
     */
    void setRzRyMoveAngle(angle prm_angRz, angle prm_angRy);
    /**
     * ���W�w��ňړ�������ݒ�B.
     * ���K���͓����ōs�Ȃ����߁A�ړ������������W���w�肷�邾���ł悢�B
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setMoveAngle(GgafDx9GeometricActor* prm_pActor_Target);

    void setTargetRzRyMoveAngle(int prm_tX, int prm_tY, int prm_tZ);

    void setTargetRzRyMoveAngle(GgafDx9GeometricActor* prm_pActor_Target);

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
     * �{�N���X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryMover();
};

}
#endif /*GGAFDX9GEOMETRYMOVER_H_*/

