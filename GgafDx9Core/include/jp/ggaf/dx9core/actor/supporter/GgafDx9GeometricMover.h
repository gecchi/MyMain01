#ifndef GGAFDX9GEOMETRICMOVER_H_
#define GGAFDX9GEOMETRICMOVER_H_
namespace GgafDx9Core {

//��X
#define AXIS_X 0
//��Y
#define AXIS_Y 1
//��Z
#define AXIS_Z 2


/**
 * ���W�v�Z�x���N���X .
 * GgafDx9GeometricActor �̃����o��<BR>
 *  _X ,  _Y,  _Z  �E�E�E �A�N�^�[�̍��W<BR>
 * _RX , _RY, _RZ  �E�E�E �A�N�^�[�̎���]�p�x<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�B<BR>
 * TODO:���̊Ԃɂ���剻�B��������B
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometricMover : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDx9GeometricMover(GgafDx9GeometricActor* prm_pActor);



public: //_RX , _RY, _RZ ����֘A //////////////////////////////////////////////

    /** �L�����̎���]���p�̕��p(0�`360,000) */
    angle _angFace[3];
    /** ����]���p�̊p���x�i����]���p�ɖ��t���[�����Z������p�j */
    angvelo _angveloFace[3];
    /** ����]���p�̊p���x���(�ō��l��360,000) */
    angvelo _angveloTopFace[3];
    /** ����]���p�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloBottomFace[3];
    /** ����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceFace[3];
    /** ����]���p�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    angjerk _angjerkFace[3];
    /** �ڕW�̎���]���p������~�@�\�L���t���O */
    bool _face_ang_targeting_flg[3];
    /** �ڕW�Ƃ���L�����̎���]���p�̕��p(0�`360,000) */
    angle _angTargetFace[3];
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
    int _face_ang_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
    angvelo _face_ang_target_allow_velo[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���z

    /**
     * Actor�̎��̉�]���p��ݒ�B<BR>
     * @param	prm_axis	��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angFace	���p�̃A���O���l(-360,000�`360,000)
     */
    void setFaceAng(int prm_axis, angle prm_angFace);

    /**
     * Actor�̎��̉�]���p��Ώۍ��W�Ɍ�����B<BR>
     * @param prm_tX �Ώ�X���W
     * @param prm_tY �Ώ�Y���W
     * @param prm_tZ �Ώ�Z���W
     */
    void setFaceAng(int prm_tX, int prm_tY, int prm_tZ);

    /**
     * ���݂� Actor �̎���]���p�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A����]���p�̑����ł��BActor�̎���]���p�i_angFace�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̎���]���p�̃A���O���l�͂��P��������܂��B
     * �����ł�����Z�i���Z�j���鎲��]���p�́A����]�p�p���x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _iBottom_RotVeloAngle �� �����̉�]�����p�l�̑��� �� _angveloTopRot  �ł��B<BR>
     *
     * �������Z�i���Z�j��A�͈͊O�ɂȂ����ꍇ�A���߂͈͓̔��̒l�ɋ����I�ɗ}�����܂��B<BR>
     * �y�⑫�F�z<BR>
     * �f�t�H���g�̉�]�����x�̏���Ɖ����i_iBottom_RotVeloAngle�A_angveloTopRot) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angDistance	��]�����p�l�̑����A���O���l(�͈́F_iBottom_RotVeloAngle �` _angveloTopRot)
     */
    void addFaceAng(int prm_axis, angle prm_angDistance);

    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ����]���p�ɂȂ�ƁA����]���p�p���x�y�ю���]���p�p�����x�� 0 �ɂ��A��]���~�����܂��B<BR>
     * ����]���p�p���x���̐ݒ�𕹂��Ď��s���āA�܂��͎���]���s�Ȃ��Ă��������B<BR>
     * ����]���p�p���x�� 0 �̏ꍇ�A�����N����܂���B�{���\�b�h�����s��������ƌ����ď���Ɍ������ς��ƂƂ����Ӗ��ł͂���܂���B <BR>
     * �����I�ɂ́AaddFaceAng(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉���(�����̃t���O���A���Z�b�g)����܂��B<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_angTargetRot	���B�ڕW�̉�]���p(0�`360,000)
     * @param	prm_way_allow  ������~��������i������(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param	prm_angveloAllow ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTarget_FaceAng(int prm_axis,
                                 angle prm_angTargetRot,
                                 int prm_way_allow = TURN_BOTH,
                                 angvelo prm_angveloAllow = ANGLE180);

    /**
     * Actor�̖ڕW��]����������~�@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
     * @param	prm_axis	��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param	prm_tX	�Ώ�X���W
     * @param	prm_tY	�Ώ�Y���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ��]����
     * @param	prm_angveloAllowRyMv ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTarget_FaceAngV(int prm_axis,
                                  int prm_tX,
                                  int prm_tY,
                                  int prm_way_allow = TURN_BOTH,
                                  angvelo prm_angveloAllowRyMv = ANGLE180);

    void setFaceAngVelo(int prm_axis, angvelo prm_angveloRot);

    void forceFaceAngVeloRange(int prm_axis,
                                  angvelo prm_angveloRot01,
                                  angvelo prm_angveloRot02);

    void setFaceAngAcce(int prm_axis, angacce prm_angacceRot);

    angle getFaceAngDistance(int prm_axis, int prm_tX, int prm_tY, int prm_way);

    angle getFaceAngDistance(int prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z ����֘A //////////////////////////////////////////////
    /** �L�����̈ړ����p�P�ʃx�N�g�� */
    float _vX, _vY, _vZ;
    /** �ړ����p��Z����]�p */
    angle _angRzMv;
    /** �ړ����p��Y����]�p */
    angle _angRyMv;
    /** �ړ����x */
    velo _veloMv;
    /** �ړ����x��� */
    velo _veloTopMv;
    /** �ړ����x���� */
    velo _veloBottomMv;
    /** �ړ������x */
    acce _accMv;
    /** �ړ����x */
    jerk _jerkMv;

    /** �ړ����p�iZ����]�j�̊p���x�i�ړ����p�iZ����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angveloRzMv;
    /** �ړ����p�iZ����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRzTopMv;
    /** �ړ����p�iZ����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRzBottomMv;
    /** �ړ����p�iZ����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRzMv;
    /** �ړ����p�iZ����]�j�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    angjerk _angjerkRzMv;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\�L���t���O */
    bool _mv_ang_rz_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iZ����]�j�̕��p(0�`360,000) */
    angle _angTargetRzMv;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _mv_ang_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _mv_ang_rz_target_allow_velo;
    /** �����O�������@�\�L���t���O */
    bool _relate_RzFaceAng_to_RzMvAng_flg;
    //true  : �ړ����p�iZ����]�j��ύX����ƁA����ɔ����������p������]���p(Z��)�ɂ��ݒ肳���
    //false : �ړ����p�iZ����]�j��Z������]���p�͓Ɨ�

    /** �ړ����p�iY����]�j�̊p���x�i�ړ����p�iY����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angveloRyMv;
    /** �ړ����p�iY����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _angveloRyTopMv;
    /** �ړ����p�iY����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _angveloRyBottomMv;
    /** �ړ����p�iY����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacceRyMv;
    /** �ړ����p�iY����]�j�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    angjerk _angjerkRyMv;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\�L���t���O */
    bool _mv_ang_ry_target_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iY����]�j�̕��p(0�`360,000) */
    int _angTargetRyMv;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _mv_ang_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    int _mv_ang_ry_target_allow_velo;
    /** �����O�������@�\�L���t���O */
    bool _relate_RyFaceAng_to_RyMvAng_flg;
    //true  : �ړ����p�iY����]�j��ύX����ƁA����ɔ����������p������]���p(Y��)�ɂ��ݒ肳���
    //false : �ړ����p�iY����]�j��Y������]���p�͓Ɨ�

    /** X�������ړ����x */
    velo _veloVxMv;
    /** X�������ړ����x��� */
    velo _veloTopVxMv;
    /** X�������ړ����x���� */
    velo _veloBottomVxMv;
    /** X�������ړ������x */
    acce _acceVxMv;
    /** X�������ړ������x���*/
    acce _acceTopVxMv;
    /** X�������ړ������x����*/
    acce _acceBottomVxMv;
    /** Y�������ړ����x */
    velo _veloVyMv;
    /** Y�������ړ����x��� */
    velo _veloTopVyMv;
    /** Y�������ړ����x���� */
    velo _veloBottomVyMv;
    /** Y�������ړ������x */
    acce _acceVyMv;
    /** Y�������ړ������x���*/
    acce _acceTopVyMv;
    /** Y�������ړ������x����*/
    acce _acceBottomVyMv;
    /** Z�������ړ����x */
    velo _veloVzMv;
    /** Z�������ړ����x��� */
    velo _veloTopVzMv;
    /** Z�������ړ����x���� */
    velo _veloBottomVzMv;
    /** Z�������ړ������x */
    acce _acceVzMv;
    /** Z�������ړ������x���*/
    acce _acceTopVzMv;
    /** Z�������ړ������x����*/
    acce _acceBottomVzMv;

    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�����s����true */
    bool _smooth_mv_velo_seq_flg;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�����s�������̉����x�ݒ�itrue�F�����x0�ɐݒ�^false:�����x�����̂܂܂ɂ��Ă����j */
    bool _smooth_mv_velo_seq_endacc_flg;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�g�b�v�X�s�[�h�i�����ړ������x�j */
    velo _smooth_mv_velo_seq_top_velo;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�I�����̑��x */
    velo _smooth_mv_velo_seq_end_velo;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ړ����� */
    int  _smooth_mv_velo_seq_distance_of_target;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̈ړ����� */
    int  _smooth_mv_velo_seq_mv_distance;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ�鋗���̈ʒu */
    int  _smooth_mv_velo_seq_distance_of_p1;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ�鋗���̈ʒu */
    int  _smooth_mv_velo_seq_distance_of_p2;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�̐i���� */
    int  _smooth_mv_velo_seq_progress;


    /**
     * �ړ����x��ݒ� .
     * @param	prm_veloMv	�ړ����x
     */
    void setMvVelo(velo prm_veloMv);

    /**
     * �ړ����x�����Z .
     * @param prm_veloMv_Offset ���Z�ړ����x
     */
    void addMvVelo(velo prm_veloMv_Offset);

    /**
     * �ړ����x�̏��������ݒ肵�A�ړ����x�͈̔͂𐧌����� .
     * �����̈ړ����x�P�A�ړ����x�Q�̑召�͂ǂ���ł����܂�Ȃ��B�i�����Ŕ��肷��j
     * @param prm_veloMv01  �ړ����x�P
     * @param prm_veloMv02  �ړ����x�Q
     */
    void forceMvVeloRange(velo prm_veloMv01, velo prm_veloMv02);

    /**
     * �ړ������x��ݒ� .
     * @param prm_acceMove �ړ������x
     */
    void setMvAcce(acce prm_acceMove);

    /**
     * �ړ������x���A�u��~�ړ������v�ɂ��ݒ肷�� .
     * <pre><code>
     *    ���x
     *     ^       a:�������x
     *     |       S:�ړ������i��~�ɔ�₷�����j
     *     |      v0:�����_�̑��x
     *   v0|       t:��~����t���[��
     *     |�_
     *     |  �_
     *     |    �_ �X����a
     *     | S    �_
     *   --+--------�_-----> ����(�t���[��)
     *   0 |         t
     *
     *    S = (1/2) v0 t  �E�E�E�@
     *    a = -v0 / t     �E�E�E�A
     *    �@���
     *    t = 2S / v0
     *    ������A�֑��
     *    a = -v0 / (2S / v0)
     *    �� a = -(v0^2) / 2S
     * </code></pre>
     * ��̓I�ɂ́A�̏�}�̂悤�ȏ�Ԃ�z�肵�A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * @param prm_distance_of_target ��~�ړ�����
     */
    void setMvAcceToStop(int prm_distance_of_target);

    /**
     * �ړ������x���A�u�ڕW���B���x�v�u�ړ������v�ɒB����܂łɔ�₷�����A�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x
     *     ^        a:�����x
     *     |        S:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
     *     |       v0:�����_�̑��x
     *     |       vx:�ڕW���B���x
     *     |       t:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
     *   vx|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �X����a
     *     |�^      |
     *   v0|  S     |
     *     |        |
     *   --+--------+---> ����(�t���[��)
     *   0 |        t
     *
     *    S = (1/2) (v0 + vx) t   �E�E�E�@
     *    a = (vx-v0) / t         �E�E�E�A
     *    �@���
     *    t = (vx-v0) / a
     *    ������A�֑��
     *    S = (vx^2 - v0^2) / 2a
     *    �� a = (vx^2 - v0^2) / 2S
     * </code></pre>
     * ��̓I�ɂ́A�̏�}�̂悤�ȏ�Ԃ�z�肵�A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ߑ��FsetMvAcce(0, d) �� setMvAcceToStop(d) �Ɠ����ł���
     * @param prm_velo_target �ڕW���B���x
     * @param prm_distance_of_target  �ڕW���B���x�ɒB����܂łɔ�₷����
     */
    void setMvAcce(int prm_distance_of_target, velo prm_velo_target);


    /**
     * Actor�̈ړ����p�iZ����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_relate_RzFaceAng_to_RzMvAng_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     *
     * @param	prm_ang	�ړ����p�iZ����]�j(0�`360,000)
     */
    void setRzMvAng(angle prm_ang);

    /**
     * Actor�̈ړ����p�iZ����]�j������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_relate_RzFaceAng_to_RzMvAng_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     *
     * @param	prm_tX	�Ώ�xZ�����W
     * @param	prm_tY	�Ώ�yZ�����W
     */
    void setRzMvAng(int prm_tX, int prm_tY);

    /**
     * ���݂� Actor �̈ړ����p�iZ����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iZ����]�j�̑����ł��BActor�̈ړ����p�iZ����]�j�i_angRzMv�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRzMvAng(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iZ����]�j�́AZ���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _angveloRzBottomMv �� �����̓����p���� �� _angveloRzTopMv  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iZ����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_relate_RzFaceAng_to_RzMvAng_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iZ����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �{���\�b�h���t���[�����s���邱�Ƃ�XY���ʂ̉~�^�����\�ɂȂ�܂��B<BR>
     * �����̈ړ����p�iZ����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iZ����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Z���ړ������x�̏���Ɖ����i_angveloRzBottomMv�A_angveloRzTopMv) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iZ����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_angDistance	�ړ����p�iZ����]�j����(�͈́F_angveloRzBottomMv �` _angveloRzTopMv)
     */
    void addRzMvAng(angle prm_angDistance);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iZ����]�j�ɂȂ�܂ŁA�ړ����p�iZ����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iZ����]�j�̊p���x�i_angveloRzMv�j�̐����Ō��肳��܂��B<BR>
     * <B>�ړ����p�iZ����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRzMvAng(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iZ����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iZ����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRzMv	���B�ڕW�̈ړ����p�iZ����]�j(-360,000�`360,000)
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RzMvAng(angle prm_angRzMv,
                               int prm_way_allow = TURN_BOTH,
                               angvelo prm_angveloAllowRyMv = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j������Z�����W����̑Ώ�Z�����W�Őݒ�)<BR>
     * �@�\��setStopTarget_RzMvAng(int)�Ɠ���<BR>
     *
     * @param	prm_tX	xRz���W
     * @param	prm_tY	yRy���W
     * @param	prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RzMvAngV(int prm_tX,
                                       int prm_tY,
                                       int prm_way_allow = TURN_BOTH,
                                       angvelo prm_angveloAllowRyMv = ANGLE180);

    void setRzMvAngVelo(angvelo prm_angveloRzMv);

    void forceRzMvAngVeloRange(angvelo prm_angveloRzMv01, angvelo prm_angveloRzMv02);

    void setRzMvAngAcce(angacce prm_angacceRzMv);

    angle getRzMvAngDistance(int prm_tX, int prm_tY, int prm_way);

    /**
     * ���g�̈ړ����p��Z����]�p( _angRzMv )�ƁA�^�[�Q�b�g�̉�]�p�Ƃ̍������擾.
     * TURN_COUNTERCLOCKWISE �E�E�E ��]�����������ō��يp�擾�A���̒l�ŕԂ�B
     * TURN_CLOCKWISE        �E�E�E ��]�������E���ō��يp�擾�A���̒l�ɕԂ�B
     * TURN_CLOSE_TO         �E�E�E �^�[�Q�b�g�̉�]�p�Ƌ������߂����̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * TURN_ANTICLOSE_TO     �E�E�E�^�[�Q�b�g�̉�]�p�Ƌ������������̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * @param prm_angTargetRzMv �^�[�Q�b�g�p�̒l
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @return
     */
    angle getRzMvAngDistance(angle prm_angTargetRzMv, int prm_way);

    /**
     * Actor�̈ړ����p�iY����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_relate_RyFaceAng_to_RyMvAng_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iY����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     * @param prm_ang �ړ����p�iY����]�j(0�`360,000)
     */
    void setRyMvAng(angle prm_ang);

    /**
     * Actor�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_relate_RyFaceAng_to_RyMvAng_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iY����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     *
     * @param	prm_tX	�Ώ�xY�����W
     * @param	prm_tY	�Ώ�yY�����W
     */
    void setRyMvAng(int prm_tX, int prm_tY);

    /**
     * ���݂� Actor �̈ړ����p�iY����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iY����]�j�̑����ł��BActor�̈ړ����p�iY����]�j�i_angRyMv�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRyMvAng(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iY����]�j�́AY���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _angveloRyBottomMv �� �����̓����p���� �� _angveloRyTopMv  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iY����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_relate_RyFaceAng_to_RyMvAng_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iY����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �{���\�b�h���t���[�����s���邱�Ƃ�XZ���ʂ̉~�^�����\�ɂȂ�܂��B<BR>
     * �����̈ړ����p�iY����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iY����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Y���ړ������x�̏���Ɖ����i_angveloRyBottomMv�A_angveloRyTopMv) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iY����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param	prm_angDistance	�ړ����p�iY����]�j����(�͈́F_angveloRyBottomMv �` _angveloRyTopMv)
     */
    void addRyMvAng(angle prm_angDistance);

    /**
     * Actor�̖ڕW��Y����]�ړ����p�̎�����~�@�\��L�� .
     * �ڕW�̈ړ����p�iY����]�j�ݒ肷��B<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iY����]�j�ɂȂ�܂ŁA�ړ����p�iY����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iY����]�j�̊p���x�i_angveloRyMv�j�̐����Ō��肳��܂��B<BR>
     * <B>�ړ����p�iY����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRyMvAng(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iY����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iY����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param	prm_angRyMv	���B�ڕW�̈ړ����p�iY����]�j(-360,000�`360,000)
     * @param	prm_mv_ang_ry_target_allow_way  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RyMvAng(angle prm_angRyMv,
                               int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                               angvelo prm_angveloAllowRyMv = ANGLE180);

    /**
     * Actor�̖ڕW��Y����]�ړ����p������~�@�\��L�� .
     * �ڕW�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�Őݒ�<BR>
     * �@�\��setStopTarget_RyMvAng(int)�Ɠ���<BR>
     * @param	prm_tX	xRy���W
     * @param	prm_tY	yRy���W
     * @param	prm_mv_ang_ry_target_allow_way  ������~�@�\���L���ɂȂ�i����]����
     * @param	prm_angveloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RyMvAngV(int prm_tX,
                                int prm_tY,
                                int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                                angvelo prm_angveloAllowRyMv = ANGLE180);

    void setRyMvAngVelo(angvelo prm_angveloRyMv);

    void forceRyMvAngVeloRange(angvelo prm_angveloRyMv01, angvelo prm_angveloRyMv02);

    void setRyMvAngAcce(angacce prm_angacceRyMv);

    angle getRyMvAngDistance(int prm_tX, int prm_tY, int prm_way);

    angle getRyMvAngDistance(angle prm_angTargetRyMv, int prm_way);


    void getRzRyMvAngDistance(int prm_way,
                              angle prm_target_angRz, angle prm_target_angRy,
                              angle& out_d_angRz, angle& out_d_angRy,
                              angle& out_target_angRz, angle& out_target_angRy);

    void getRzRyFaceAngDistance(int prm_way,
                                angle prm_target_angRz, angle prm_target_angRy,
                                angle& out_d_angRz, angle& out_d_angRy,
                                angle& out_target_angRz, angle& out_target_angRy);
    /**
     * �ړ�����(RzRy)��ݒ�B.
     * @param prm_angRz
     * @param prm_angRy
     */
    void setRzRyMvAng(angle prm_angRz, angle prm_angRy);

    /**
     *  �ړ�����(RzRy)���ARyRz�Őݒ�B
     * @param prm_angRy
     * @param prm_angRz
     */
    void setRzRyMvAng_by_RyRz(angle prm_angRy, angle prm_angRz);

    /**
     * �ڕW���W�w��ňړ����p��ݒ�B.
     * �����x�N�g�����K���������ōs�Ȃ��B
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMvAng(int prm_tX, int prm_tY, int prm_tZ);

    void setMvAng(GgafDx9GeometricActor* prm_pActor_Target);

    void setStopTarget_RzRyMvAng(int prm_tX, int prm_tY, int prm_tZ);

    void setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target);

    //virtual void behave();

    void setVxMvVelo(velo prm_veloVxMv);
    void addVxMvVelo(velo prm_veloVxMv);
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);
    void setVxMvAcce(acce prm_acceVxMv);
    void addVxMvAcce(acce prm_acceVxMv);
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);
    void setVyMvVelo(velo prm_veloVyMv);
    void addVyMvVelo(velo prm_veloVyMv);
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);
    void setVyMvAcce(acce prm_acceVyMv);
    void addVyMvAcce(acce prm_acceVyMv);
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);
    void setVzMvVelo(velo prm_veloVzMv);
    void addVzMvVelo(velo prm_veloVzMv);
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);
    void setVzMvAcce(acce prm_acceVzMv);
    void addVzMvAcce(acce prm_acceVzMv);
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    /**
     * ����]���p(Z����Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW����]���p(Z��)
     * @param prm_angRy_Target �ڕW����]���p(Y��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B
     *                         true: ������ prm_angRz_Target, prm_angRy_Target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                         false:������ prm_angRz_Target, prm_angRy_Target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void execTagettingFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true);

    /**
     * ����]���p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tX �ڕWX���W
     * @param prm_tY �ڕWY���W
     * @param prm_tZ �ڕWZ���W
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_angRz_Target, prm_angRy_Target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_angRz_Target, prm_angRy_Target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void execTagettingFaceAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true);


    /**
     * ����]���p(Z����Y��)��ڕW�Ƀ^�[�Q�b�g�̕����������悤�ȃV�[�N�G���X�����s
     * @param prm_pActor_Target �ڕW�I�u�W�F�N�g
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_angRz_Target, prm_angRy_Target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_angRz_Target, prm_angRy_Target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void execTagettingFaceAngSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true) {
        execTagettingFaceAngSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo,
                prm_angAcce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * ����]���p(Z��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW����]���p(Z��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRzFaceAngSequence(angle prm_angRz_Target,
                                        angvelo prm_angVelo, angacce prm_angAcce,
                                        int prm_way);

    /**
     * ����]���p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRy_Target �ڕW����]���p(Y��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRyFaceAngSequence(angle prm_angRy_Target,
                                        angvelo prm_angVelo, angacce prm_angAcce,
                                        int prm_way);

    /**
     * ����]���p(X��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRx_Target �ڕW����]���p(X��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRxSpinAngleSequence(angle prm_angRx_Target,
                                          angvelo prm_angVelo, angacce prm_angAcce,
                                          int prm_way);

    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW�ړ����p(Z��)
     * @param prm_angRy_Target �ڕW�ړ����p(Y��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_angRz_Target, prm_angRy_Target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_angRz_Target, prm_angRy_Target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void execTagettingMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true);

    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tX �ڕWX���W
     * @param prm_tY �ڕWY���W
     * @param prm_tZ �ڕWZ���W
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_angRz_Target, prm_angRy_Target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_angRz_Target, prm_angRy_Target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void execTagettingMvAngSequence(int prm_tX, int prm_tY, int prm_tZ,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true);


    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g�̍��W�ɂ���V�[�N�G���X�����s
     * @param prm_pActor_Target �ڕW�I�u�W�F�N�g
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_angRz_Target, prm_angRy_Target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_angRz_Target, prm_angRy_Target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void execTagettingMvAngSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                    angvelo prm_angVelo, angacce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true) {
        execTagettingMvAngSequence(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo,
                prm_angAcce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * �ړ����p(Z��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRz_Target �ڕW�ړ����p(Z��)
     * @param prm_angVelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRzMvAngSequence(angle prm_angRz_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way);

    /**
     * �ړ����p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRy_Target �ڕW�ړ����p(Y��)
     * @param prm_angVelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTagettingRyMvAngSequence(angle prm_angRy_Target,
                                      angvelo prm_angVelo, angacce prm_angAcce,
                                      int prm_way);


    void stopTagettingMvAngSequence() {
        _mv_ang_rz_target_flg = false;
        _mv_ang_ry_target_flg = false;
    }


    /**
     * �ڕW����]���p�Ƀ^�[�Q�b�g����V�[�N�G���X�����s���� .
     * @return true:���s��/false:���s���łȂ�
     */
    bool isTagettingFaceAng() {
        if (_face_ang_targeting_flg[AXIS_X] ||
            _face_ang_targeting_flg[AXIS_Y] ||
            _face_ang_targeting_flg[AXIS_Z]) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �ڕW�ړ����p�Ƀ^�[�Q�b�g����V�[�N�G���X�����s���� .
     * @return true:���s��/false:���s���łȂ�
     */
    bool isTagettingMvAng() {
        if (_mv_ang_rz_target_flg || _mv_ang_rz_target_flg) {
            return true;
        } else {
            return false;
        }
    }


    /**
     * �ړ����p�ɔ����Ď���]���p���X�V .
     * true ��ݒ肷��ƁA�����I�Ɉړ����p�̕��Ɍ������ς��B<BR>
     * false ��ݒ肷��ƁA�ړ����p�ƌ����͓Ɨ��B<BR>
     * @param prm_b true:�ړ����p�ɔ����Ď���]���p���X�V/false:�ړ����p�Ǝ���]���p�͓Ɨ�
     */
    void relateRzRyFaceAngToMvAng(bool prm_b) {
        _relate_RyFaceAng_to_RyMvAng_flg = prm_b;
        _relate_RzFaceAng_to_RzMvAng_flg = prm_b;
    }

    /**
     * �Ȃ߂炩�Ȉړ����x�ňړ�����V�[�N�G���X�����s .
     * �����̈ړ��������S�������A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * ���� 0    �`���� 1/4 �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���<BR>
     * ���� 1/4 �` ���� 3/4 �܂� �E�E�E �g�b�v�X�s�[�h�œ���<BR>
     * ���� 3/4 �` ���� 4/4 �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���<BR>
     * @param prm_top_velo �g�b�v�X�s�[�h
     * @param prm_end_velo �ŏI�X�s�[�h
     * @param prm_distance_of_target �ڕW�ړ�����
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɂ���/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void execSmoothMvVeloSequence(velo prm_top_velo, velo prm_end_velo, int prm_distance_of_target,
                                  bool prm_endacc_flg = true);

    bool isMoveingSmooth();



    /**
     * ���t���[����Actor�̐U�镑���B<BR>
     * �{�N���X���@�\�𗘗p����ꍇ�́A����behave() �𖈃t���[���Ăяo�����s���Ă��������B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometricMover();
};

}
#endif /*GGAFDX9GEOMETRICMOVER_H_*/

