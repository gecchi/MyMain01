#ifndef GGAFDX9MVNAVIGATOR_H_
#define GGAFDX9MVNAVIGATOR_H_
namespace GgafDx9Core {

//��X
#define AXIS_X 0
//��Y
#define AXIS_Y 1
//��Z
#define AXIS_Z 2


/**
 * ���qA(����A) .
 * ���qA�͕���ɂ͌����Ȃ��ł����A����(�A�N�^�[)�������グ�A�u�����ړ��v�u�����̉�]�v���s�킹�鐢�b�l�ł��B<BR>
 * ���҂͎���̈ӎv�œ��삹���Ƃ��A���qA�̂������ŕ�����щ�܂�邱�Ƃ��ł��܂��B<BR>
 * ��{�I�Ȉړ�����͍��qA�łقƂ�ǃJ�o�[�ł��܂����A���\�ł͂���܂���B<BR>
 * ���qA���撣���Ă��Ή��ł��Ȃ����G�Ȉړ�����́A����(�A�N�^�[)���g�����͂��Ĉړ��E��]���s���K�v������܂��B<BR>
 * ���҈�l�ɂ��A���qA���W���ň�l�t�����Ă��܂��B<BR>
 * <BR>
 * ����͂��Ēu���A�܂�͍��W�v�Z�x���i���ʉ��j�N���X�ł��B<BR>
 * GgafDx9GeometricActor �̃����o��<BR>
 *  _X ,  _Y,  _Z  �E�E�E �A�N�^�[�̍��W<BR>
 * _RX , _RY, _RZ  �E�E�E �A�N�^�[�̎���]�p�x<BR>
 * ���A�����x�N�g���A���x�A�����A���ԁA�ɂ���ĊǗ����삷�邽�߂ɍ쐬�����N���X�B<BR>
 * ���ʂ̊�{�I�Ȉړ��A��]�͍��qA�ɔC���āA<BR>
 * �A�N�^�[�ŗL�̓���Ȉړ���]����� processBehave() �ɒ��ڋL�q�B�Ƃ����݌v�v�z�B<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9KurokoA : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDx9KurokoA(GgafDx9GeometricActor* prm_pActor);



public: //_RX , _RY, _RZ ����֘A //////////////////////////////////////////////

    /** �L�����̎���]���p�̕��p(0�`360,000) */
    angle _angFace[3];
    /** ����]���p�̊p���x�i����]���p�ɖ��t���[�����Z������p�j */
    ang_velo _ang_veloFace[3];
    /** ����]���p�̊p���x���(�ō��l��360,000) */
    ang_velo _ang_veloTopFace[3];
    /** ����]���p�̊p���x����(�ō��l��-360,000) */
    ang_velo _ang_veloBottomFace[3];
    /** ����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    ang_acce _ang_acceFace[3];
    /** ����]���p�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    ang_jerk _ang_jerkFace[3];
    /** �ڕW�̎���]���p���������L���t���O */
    bool _face_ang_targeting_flg[3];
    /** �ڕW�̎���]���p������~�@�\�L���t���O */
    bool _face_ang_targeting_stop_flg[3];
    /** �ڕW�Ƃ���L�����̎���]���p�̕��p(0�`360,000) */
    angle _angTargetFace[3];
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
    int _face_ang_target_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
    ang_velo _face_ang_target_allow_velo[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���z

    /**
     * Actor�̎���]���p��ݒ�B<BR>
     * @param   prm_axis    ��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_angFace ���p�̃A���O���l(-360,000�`360,000)
     */
    void setFaceAng(axis prm_axis, angle prm_angFace);

    /**
     * Actor�̎���]���p��Ώۍ��W�_�Ɍ�����B<BR>
     * @param prm_tX �Ώۓ_X���W
     * @param prm_tY �Ώۓ_Y���W
     * @param prm_tZ �Ώۓ_Z���W
     */
    void setFaceAng(coord prm_tX, coord prm_tY, coord prm_tZ);

    /**
     * ���݂� Actor �̎���]���p�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A����]���p�̑����ł��BActor�̎���]���p�i_angFace�j�𑊑Ύw��ł��郁�\�b�h�ł��B<BR>
     * ���Z��̎���]���p�̃A���O���l�͂��P��������܂��B
     * �����ł�����Z�i���Z�j���鎲��]���p�́A����]�p�p���x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _iBottom_RotVeloAngle �� �����̉�]�����p�l�̑��� �� _ang_veloTopRot  �ł��B<BR>
     *
     * �������Z�i���Z�j��A�͈͊O�ɂȂ����ꍇ�A���߂͈͓̔��̒l�ɋ����I�ɗ}�����܂��B<BR>
     * �y�⑫�F�z<BR>
     * �f�t�H���g�̉�]�����x�̏���Ɖ����i_iBottom_RotVeloAngle�A_ang_veloTopRot) ��<BR>
     *
     *  -360000 , 360000<BR>
     *
     *  �ł��B
     *  <BR>
     *
     * @param   prm_axis    ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_angDistance ��]�����p�l�̑����A���O���l(�͈́F_iBottom_RotVeloAngle �` _ang_veloTopRot)
     */
    void addFaceAng(axis prm_axis, angle prm_angDistance);

    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ����]���p�ɂȂ�ƁA����]���p�p���x�y�ю���]���p�p�����x�� 0 �ɂ��A��]���~�����܂��B<BR>
     * ����]���p�p���x���̐ݒ�𕹂��Ď��s���āA�܂��͎���]���s�Ȃ��Ă��������B<BR>
     * ����]���p�p���x�� 0 �̏ꍇ�A�����N����܂���B�{���\�b�h�����s��������ƌ����ď���Ɍ������ς��ƂƂ����Ӗ��ł͂���܂���B <BR>
     * �����I�ɂ́AaddFaceAng(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉���(�����̃t���O���A���Z�b�g)����܂��B<BR>
     * @param   prm_axis    ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_angTargetRot    ���B�ڕW�̉�]���p(0�`360,000)
     * @param   prm_way_allow  ������~��������i������(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param   prm_ang_veloAllow ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTarget_FaceAng(axis prm_axis,
                               angle prm_angTargetRot,
                               int prm_way_allow = TURN_BOTH,
                               ang_velo prm_ang_veloAllow = ANGLE180);

    /**
     * Actor�̖ڕW��]����������~�@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
     * @param   prm_axis    ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_tX  �Ώ�X���W
     * @param   prm_tY  �Ώ�Y���W
     * @param   prm_way_allow  ������~�@�\���L���ɂȂ��]����
     * @param   prm_ang_veloAllowRyMv ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTarget_FaceAngV(axis prm_axis,
                                coord prm_tX,
                                coord prm_tY,
                                int prm_way_allow = TURN_BOTH,
                                ang_velo prm_ang_veloAllowRyMv = ANGLE180);

    void setFaceAngVelo(axis prm_axis, ang_velo prm_ang_veloRot);

    void forceFaceAngVeloRange(axis prm_axis,
                               ang_velo prm_ang_veloRot01,
                               ang_velo prm_ang_veloRot02);

    void setFaceAngAcce(axis prm_axis, ang_acce prm_ang_acceRot);

    angle getFaceAngDistance(axis prm_axis, coord prm_tX, coord prm_tY, int prm_way);

    angle getFaceAngDistance(axis prm_axis, angle prm_angTargetRot, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_X , _Y, _Z ����֘A //////////////////////////////////////////////
    /** [r]�L�����̈ړ����p�P�ʃx�N�g�� */
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
    //jerk _jerkMv;

    /** �ړ����p�iZ����]�j�̊p���x�i�ړ����p�iZ����]�j�ɖ��t���[�����Z������p�j */
    ang_velo _ang_veloRzMv;
    /** �ړ����p�iZ����]�j�̊p���x���(�ō��l��360,000) */
    ang_velo _ang_veloRzTopMv;
    /** �ړ����p�iZ����]�j�̊p���x����(�ō��l��-360,000) */
    ang_velo _ang_veloRzBottomMv;
    /** �ړ����p�iZ����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    ang_acce _ang_acceRzMv;
    /** �ړ����p�iZ����]�j�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    ang_jerk _ang_jerkRzMv;
    /** �ڕW�̈ړ����p�iZ����]�j�����L���t���O */
    bool _mv_ang_rz_target_flg;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\�L���t���O */
    bool _mv_ang_rz_target_stop_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iZ����]�j�̕��p(0�`360,000) */
    angle _angTargetRzMv;
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _mv_ang_rz_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    ang_velo _mv_ang_rz_target_allow_velo;
    /** �����O�������@�\�L���t���O */
    bool _relate_RzFaceAng_with_RzMvAng_flg;
    //true  : �ړ����p�iZ����]�j��ύX����ƁA����ɔ����������p������]���p(Z��)�ɂ��ݒ肳���
    //false : �ړ����p�iZ����]�j��Z������]���p�͓Ɨ�

    /** �ړ����p�iY����]�j�̊p���x�i�ړ����p�iY����]�j�ɖ��t���[�����Z������p�j */
    ang_velo _ang_veloRyMv;
    /** �ړ����p�iY����]�j�̊p���x���(�ō��l��360,000) */
    ang_velo _ang_veloRyTopMv;
    /** �ړ����p�iY����]�j�̊p���x����(�ō��l��-360,000) */
    ang_velo _ang_veloRyBottomMv;
    /** �ړ����p�iY����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    ang_acce _ang_acceRyMv;
    /** �ړ����p�iY����]�j�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    ang_jerk _ang_jerkRyMv;
    /** �ڕW�̈ړ����p�iY����]�j���������L���t���O */
    bool _mv_ang_ry_target_flg;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\�L���t���O */
    bool _mv_ang_ry_target_stop_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iY����]�j�̕��p(0�`360,000) */
    angle _angTargetRyMv;
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _mv_ang_ry_target_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** �ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    ang_velo _mv_ang_ry_target_allow_velo;
    /** �����O�������@�\�L���t���O */
    bool _relate_RyFaceAng_with_RyMvAng_flg;
    //true  : �ړ����p�iY����]�j��ύX����ƁA����ɔ����������p������]���p(Y��)�ɂ��ݒ肳���
    //false : �ړ����p�iY����]�j��Y������]���p�͓Ɨ�



    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�����s����true */
    bool _smooth_mv_velo_seq_flg;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�����s�������̉����x�ݒ�itrue�F�����x0�ɐݒ�^false:�����x�����̂܂܂ɂ��Ă����j */
    bool _smooth_mv_velo_seq_endacc_flg;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�g�b�v�X�s�[�h�i�����ړ������x�j */
    velo _smooth_mv_velo_seq_top_velo;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�I�����̑��x */
    velo _smooth_mv_velo_seq_end_velo;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ړ����� */
    coord _smooth_mv_velo_seq_target_distance;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̈ړ����� */
    coord _smooth_mv_velo_seq_mv_distance;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW���� */
    int  _smooth_mv_velo_seq_target_frames;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̌o�ߎ��� */
    int  _smooth_mv_velo_seq_frame_of_spent;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
    int  _smooth_mv_velo_seq_p1;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
    int  _smooth_mv_velo_seq_p2;
    /** �Ȃ߂炩�Ȉړ��V�[�N�G���X�̐i���� */
    int  _smooth_mv_velo_seq_progress;


    bool _taget_mv_ang_alltime_flg;
    GgafDx9GeometricActor* _taget_mv_ang_alltime_pActor;
    coord _taget_mv_ang_alltime_tX;
    coord _taget_mv_ang_alltime_tY;
    coord _taget_mv_ang_alltime_tZ;
    ang_velo  _taget_mv_ang_alltime_angVelo;
    ang_acce _taget_mv_ang_alltime_angAcce;
    int _taget_mv_ang_alltime_way;
    bool _taget_mv_ang_alltime_optimize_ang;
    /**
     * �ړ����x��ݒ� .
     * @param   prm_veloMv  �ړ����x
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
    void forceMvVeloRange(velo prm_veloMv);
    /**
     * �ړ������x��ݒ� .
     * @param prm_acceMove �ړ������x
     */
    void setMvAcce(acce prm_acceMove);

    /**
     * �ړ������x���A�u��~���ړ������v�ɂ��ݒ肷�� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^       a:�������x
     *     |       D:�ړ������i��~�ɔ�₷�����j
     *     |      Vo:�����_�̑��x
     *   Vo|      Te:��~����t���[��
     *     |�_
     *     |  �_
     *     |    �_ �Εӂ̌X��a
     *     |   D  �_
     *     |        �_
     *   --+----------�_-----> ����(t)
     *   0 |          Te
     *
     *    D = (1/2) Vo Te  �E�E�E�@
     *    a = -Vo / Te     �E�E�E�A
     *    �@���
     *    Te = 2D / Vo
     *    ������A�֑��
     *    a = -Vo / (2D / Vo)
     *    �� a = -(Vo^2) / 2D
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�����̋���(D)����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * ��~�܂ł̃t���[��(Te) �� ����(D) �ɂ��ω����邽�ߎw��s�B<BR>
     * @param prm_target_distance ��~���ړ�����(D)
     */
    void setMvAcceToStop(coord prm_target_distance);

    /**
     * �ړ������x���A�u�ڕW���B���x�v�u�ړ�����(�B����܂łɔ�₷����)�v�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x
     *     |        D:�ړ������i�ڕW���B���x�ɒB����܂łɔ�₷�����j
     *     |       Vo:�����_�̑��x
     *     |       Vt:�ڕW���B���x
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> ����(t)
     *   0 |        Te
     *
     *    D = (1/2) (Vo + Vt) Te   �E�E�E�@
     *    a = (Vt - Vo) / Te         �E�E�E�A
     *    �@��� Te = (Vt - Vo) / a
     *    ������A�֑��
     *    D = (Vt^2 - Vo^2) / 2a
     *    �� a = (Vt^2 - Vo^2) / 2D
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA�ړ�����(D)����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ڕW���B�܂ŕK�v�ȃt���[��(Te) �̓p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * �ߑ��FsetMvAcceBy_Dv(0, D) �� setMvAcceToStop(D) �Ɠ����ł���
     * @param prm_target_distance  �ڕW���B���x�ɒB����܂łɔ�₷����(D)
     * @param prm_target_velo �ڕW���B���x(Vt)
     */
    void setMvAcceBy_Dv(coord prm_target_distance, velo prm_target_velo);


    /**
     * �ړ������x���A�u�ڕW���B���x�v�u��₷���ԁv�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x
     *     |        D:�ړ�����
     *     |       Vo:�����_�̑��x
     *     |       Vt:�ڕW���B���x
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�t���[�����j
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   Vo|    D   |
     *     |        |
     *   --+--------+---> ����(t�t���[��)
     *   0 |        Te
     *
     *    a = (Vt-Vo) / Te
     *    D�͖���
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA���̓��B����(Te) ����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ړ�����(D)�́A�p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * @param prm_target_frames ��₷����(Te)
     * @param prm_target_velo  �ڕW���B���x(Vt)
     */
    void setMvAcceBy_tv(int prm_target_frames, velo prm_target_velo);

    /**
     * Actor�̈ړ����p�iZ����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_relate_RzFaceAng_with_RzMvAng_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     *
     * @param   prm_ang �ړ����p�iZ����]�j(0�`360,000)
     */
    void setRzMvAng(angle prm_ang);

    /**
     * Actor�̈ړ����p�iZ����]�j������XY���W����̑Ώ�XY���W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_relate_RzFaceAng_with_RzMvAng_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     *
     * @param   prm_tX  �Ώ�xZ�����W
     * @param   prm_tY  �Ώ�yZ�����W
     */
    void setRzMvAng(coord prm_tX, coord prm_tY);

    /**
     * ���݂� Actor �̈ړ����p�iZ����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iZ����]�j�̑����ł��BActor�̈ړ����p�iZ����]�j�i_angRzMv�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRzMvAng(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iZ����]�j�́AZ���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _ang_veloRzBottomMv �� �����̓����p���� �� _ang_veloRzTopMv  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iZ����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_relate_RzFaceAng_with_RzMvAng_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iZ����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �{���\�b�h���t���[�����s���邱�Ƃ�XY���ʂ̉~�^�����\�ɂȂ�܂��B<BR>
     * �����̈ړ����p�iZ����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iZ����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Z���ړ������x�̏���Ɖ����i_ang_veloRzBottomMv�A_ang_veloRzTopMv) ��<BR>
     *
     *  -360000 , 360000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iZ����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param   prm_angDistance �ړ����p�iZ����]�j����(�͈́F_ang_veloRzBottomMv �` _ang_veloRzTopMv)
     */
    void addRzMvAng(angle prm_angDistance);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iZ����]�j�ɂȂ�܂ŁA�ړ����p�iZ����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iZ����]�j�̊p���x�i_ang_veloRzMv�j�̐����Ō��肳��܂��B<BR>
     * <B>�ړ����p�iZ����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRzMvAng(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iZ����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iZ����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param   prm_angRzMv ���B�ڕW�̈ړ����p�iZ����]�j(-360,000�`360,000)
     * @param   prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param   prm_ang_veloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RzMvAng(angle prm_angRzMv,
                               int prm_way_allow = TURN_BOTH,
                               ang_velo prm_ang_veloAllowRyMv = ANGLE180);

    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j������Z�����W����̑Ώ�Z�����W�Őݒ�)<BR>
     * �@�\��setStopTarget_RzMvAng(int)�Ɠ���<BR>
     *
     * @param   prm_tX  xRz���W
     * @param   prm_tY  yRy���W
     * @param   prm_way_allow  ������~�@�\���L���ɂȂ�i����]����
     * @param   prm_ang_veloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RzMvAngV(coord prm_tX,
                                       coord prm_tY,
                                       int prm_way_allow = TURN_BOTH,
                                       ang_velo prm_ang_veloAllowRyMv = ANGLE180);

    void setRzMvAngVelo(ang_velo prm_ang_veloRzMv);

    void forceRzMvAngVeloRange(ang_velo prm_ang_veloRzMv01, ang_velo prm_ang_veloRzMv02);

    void setRzMvAngAcce(ang_acce prm_ang_acceRzMv);

    angle getRzMvAngDistance(coord prm_tX, coord prm_tY, int prm_way);

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
     * �����O�������@�\���L��(_relate_RyFaceAng_with_RyMvAng_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iY����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     * @param prm_ang �ړ����p�iY����]�j(0�`360,000)
     */
    void setRyMvAng(angle prm_ang);

    /**
     * Actor�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�ւ̕���������o���A�ݒ肷��B<BR>
     * �����O�������@�\���L��(_relate_RyFaceAng_with_RyMvAng_flg)�̏ꍇ�A<BR>
     * Actor��Z�����p�i�����j���ړ����p�iY����]�j�Ɠ��������������悤�� setStopTarget_FaceAng(int) �����s����܂��B<BR>
     *
     * @param   prm_tX  �Ώ�xY�����W
     * @param   prm_tY  �Ώ�yY�����W
     */
    void setRyMvAng(coord prm_tX, coord prm_tY);

    /**
     * ���݂� Actor �̈ړ����p�iY����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iY����]�j�̑����ł��BActor�̈ړ����p�iY����]�j�i_angRyMv�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRyMvAng(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iY����]�j�́AY���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _ang_veloRyBottomMv �� �����̓����p���� �� _ang_veloRyTopMv  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iY����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_relate_RyFaceAng_with_RyMvAng_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iY����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �{���\�b�h���t���[�����s���邱�Ƃ�XZ���ʂ̉~�^�����\�ɂȂ�܂��B<BR>
     * �����̈ړ����p�iY����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iY����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Y���ړ������x�̏���Ɖ����i_ang_veloRyBottomMv�A_ang_veloRyTopMv) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iY����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param   prm_angDistance �ړ����p�iY����]�j����(�͈́F_ang_veloRyBottomMv �` _ang_veloRyTopMv)
     */
    void addRyMvAng(angle prm_angDistance);

    /**
     * Actor�̖ڕW��Y����]�ړ����p�̎�����~�@�\��L�� .
     * �ڕW�̈ړ����p�iY����]�j�ݒ肷��B<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iY����]�j�ɂȂ�܂ŁA�ړ����p�iY����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iY����]�j�̊p���x�i_ang_veloRyMv�j�̐����Ō��肳��܂��B<BR>
     * <B>�ړ����p�iY����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRyMvAng(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iY����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iY����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param   prm_angRyMv ���B�ڕW�̈ړ����p�iY����]�j(-360,000�`360,000)
     * @param   prm_mv_ang_ry_target_allow_way  ������~�@�\���L���ɂȂ�i����]����
     * @param   prm_ang_veloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RyMvAng(angle prm_angRyMv,
                               int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                               ang_velo prm_ang_veloAllowRyMv = ANGLE180);

    /**
     * Actor�̖ڕW��Y����]�ړ����p������~�@�\��L�� .
     * �ڕW�̈ړ����p�iY����]�j������Y�����W����̑Ώ�Y�����W�Őݒ�<BR>
     * �@�\��setStopTarget_RyMvAng(int)�Ɠ���<BR>
     * @param   prm_tX  xRy���W
     * @param   prm_tY  yRy���W
     * @param   prm_mv_ang_ry_target_allow_way  ������~�@�\���L���ɂȂ�i����]����
     * @param   prm_ang_veloAllowRyMv ��~�@�\���L���ɂȂ�ړ����p�p���x
     */
    void setStopTarget_RyMvAngV(coord prm_tX,
                                coord prm_tY,
                                int prm_mv_ang_ry_target_allow_way = TURN_BOTH,
                                ang_velo prm_ang_veloAllowRyMv = ANGLE180);

    void setRyMvAngVelo(ang_velo prm_ang_veloRyMv);

    void forceRyMvAngVeloRange(ang_velo prm_ang_veloRyMv01, ang_velo prm_ang_veloRyMv02);

    void setRyMvAngAcce(ang_acce prm_ang_acceRyMv);

    angle getRyMvAngDistance(coord prm_tX, coord prm_tY, int prm_way);

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
     * �ڕW���W�_�w��ňړ����p��ݒ�B.
     * �����x�N�g�����K���������ōs�Ȃ��B
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     */
    void setMvAng(coord prm_tX, coord prm_tY, coord prm_tZ);

    void setMvAng(GgafDx9GeometricActor* prm_pActor_Target);

    void setStopTarget_RzRyMvAng(coord prm_tX, coord prm_tY, coord prm_tZ);

    void setStopTarget_RzRyMvAng(GgafDx9GeometricActor* prm_pActor_Target);


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
    void execTurnFaceAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
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
    void execTurnFaceAngSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
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
    void execTurnFaceAngSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
                                      int prm_way, bool prm_optimize_ang = true) {
        execTurnFaceAngSequence(
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
    void execTurnRzFaceAngSequence(angle prm_angRz_Target,
                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                        int prm_way);

    /**
     * ����]���p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRy_Target �ڕW����]���p(Y��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTurnRyFaceAngSequence(angle prm_angRy_Target,
                                        ang_velo prm_angVelo, ang_acce prm_angAcce,
                                        int prm_way);

    /**
     * ����]���p(X��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRx_Target �ڕW����]���p(X��)
     * @param prm_angVelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTurnRxSpinAngSequence(angle prm_angRx_Target,
                                          ang_velo prm_angVelo, ang_acce prm_angAcce,
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
    void execTurnMvAngSequence(angle prm_angRz_Target, angle prm_angRy_Target,
                                    ang_velo prm_angVelo, ang_acce prm_angAcce,
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
    void execTurnMvAngSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                    ang_velo prm_angVelo, ang_acce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true);

    void keepTurnMvAngAllTime(coord prm_tX, coord prm_tY, coord prm_tZ,
                            ang_velo prm_angVelo, ang_acce prm_angAcce,
                            int prm_way, bool prm_optimize_ang = true) {
        execTurnMvAngSequence(prm_tX, prm_tY, prm_tZ,
                                    prm_angVelo,  prm_angAcce,
                                    prm_way, prm_optimize_ang );
        _taget_mv_ang_alltime_flg = true;
        _taget_mv_ang_alltime_pActor = NULL;
        _taget_mv_ang_alltime_tX = prm_tX;
        _taget_mv_ang_alltime_tY = prm_tY;
        _taget_mv_ang_alltime_tZ = prm_tZ;
        _taget_mv_ang_alltime_angVelo = prm_angVelo;
        _taget_mv_ang_alltime_angAcce = prm_angAcce;
        _taget_mv_ang_alltime_way = prm_way;
        _taget_mv_ang_alltime_optimize_ang = prm_optimize_ang;
    }
    void keepTurnMvAngAllTime(GgafDx9GeometricActor* prm_pActor_Target,
                            ang_velo prm_angVelo, ang_acce prm_angAcce,
                            int prm_way, bool prm_optimize_ang = true) {
        keepTurnMvAngAllTime(
                prm_pActor_Target->_X,
                prm_pActor_Target->_Y,
                prm_pActor_Target->_Z,
                prm_angVelo, prm_angAcce,
                prm_way, prm_optimize_ang);
        _taget_mv_ang_alltime_pActor = prm_pActor_Target;
    }

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
    void execTurnMvAngSequence(GgafDx9GeometricActor* prm_pActor_Target,
                                    ang_velo prm_angVelo, ang_acce prm_angAcce,
                                    int prm_way, bool prm_optimize_ang = true) {
        execTurnMvAngSequence(
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
    void execTurnRzMvAngSequence(angle prm_angRz_Target,
                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
                                      int prm_way);

    /**
     * �ړ����p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_angRy_Target �ڕW�ړ����p(Y��)
     * @param prm_angVelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x�i������������j
     * @param prm_angAcce �p�����x�i������������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void execTurnRyMvAngSequence(angle prm_angRy_Target,
                                      ang_velo prm_angVelo, ang_acce prm_angAcce,
                                      int prm_way);


    void stopTurnMvAngSequence() {
        _mv_ang_rz_target_flg = false;
        _mv_ang_rz_target_stop_flg = false;
        _mv_ang_ry_target_flg = false;
        _mv_ang_rz_target_stop_flg = false;
        _taget_mv_ang_alltime_pActor = NULL;
        _taget_mv_ang_alltime_flg = false;
    }

    /**
     * �ڕW����]���p�Ƀ^�[�Q�b�g����V�[�N�G���X�����s���� .
     * @return true:���s��/false:���s���łȂ�
     */
    bool isTurningFaceAng() {
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
    bool isTurningMvAng() {
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
    void relateFaceAngWithMvAng(bool prm_b) {
        _relate_RyFaceAng_with_RyMvAng_flg = prm_b;
        _relate_RzFaceAng_with_RzMvAng_flg = prm_b;
    }


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s .
     * �ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    ���x(v)
     *     ^
     *     |
     *     |                         Vo:�����_�̑��x
     *     |                         Ve:�ŏI���x
     *     |                          D:�ڕW�ړ�����
     *   Vt|....___________          Te:�ڕW���ԁi�t���[�����j
     *     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *     | /  :         :    |     Vt:�����E���Ԃ��瓱���������g�b�v�X�s�[�h
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * �ŏI�X�s�[�h(Ve)�A�ڕW�ړ�����(D)�A���B�ڕW����(Te)�A�y�� p1, p2 ���w�肷��B<BR>
     * �g�b�v�X�s�[�h(Vt)�͓����Ŏ����v�Z�����肳���B<BR>
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void execSmoothMvVeloSequence(velo prm_end_velo, coord prm_target_distance,
                                  int prm_target_frames, float prm_p1, float prm_p2,
                                  bool prm_endacc_flg = true);


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s .
     * �ړ�������3�̃Z�N�V����(d1,d2,d3)�ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� d1       �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� d1    �` ���� d1+d2    �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� d1+d2 �` ���� d1+d2+d3 �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *    ���x(v)
     *     ^
     *     |                         Vo:�����_�̑��x
     *     |                         Vt:�g�b�v�X�s�[�h
     *     |                         Ve:�ŏI���x
     *     |         D=d1+d2+d3       D:�ڕW�ړ�����(D=d1+d2+d3)
     *   Vt|....___________          p1:�g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     *     |   /|         |�_            �܂�    d1 = D*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
     *   Ve|../.|.........|..�_      p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     *     | /  |         |    |         �܂� d1+d2 = D*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
     *     |/   |         |    |     Te:��₳���K�v���ԁi�t���[�����j
     *   Vo| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |                  Te
     *
     * </pre>
     * �g�b�v�X�s�[�h(Vt)�A�ŏI�X�s�[�h(Ve)�A�ڕW�ړ�����(D)�A�y�� p1, p2 ���w�肷��B<BR>
     * ��₳��鎞��(Te)�͓����Ŏ����v�����肳���B<BR>
     * <BR>
     * @param prm_top_velo �g�b�v�X�s�[�h(Vt)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     * @param prm_endacc_flg
     */
    void execSmoothMvVeloSequenceD(velo prm_top_velo, velo prm_end_velo,
                                   coord prm_target_distance, float prm_p1, float prm_p2,
                                   bool prm_endacc_flg = true);


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s .
     * �ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    ���x(v)
     *     ^
     *     |
     *     |                         Vo:�����_�̑��x
     *     |                         Vt:�g�b�v�X�s�[�h
     *     |                         Ve:�ŏI���x
     *   Vt|....___________          Te:���B�ڕW���ԁi�t���[�����j
     *     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *     | /  :         :    |      D:�K�v�Ȉړ�����
     *     |/   :         :    |
     *   Vo|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * �g�b�v�X�s�[�h(Vt)�A�ŏI�X�s�[�h(Ve)�A���B�ڕW����(Te)�A�y�� p1, p2 ���w�肷��B<BR>
     * �K�v�Ȉړ�����(D)�͓����Ŏ����v�Z�����肳���B<BR>
     * <BR>
     * @param prm_top_velo �g�b�v�X�s�[�h(Vt)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_target_frames ���B�ڕW����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     * @param prm_endacc_flg true:�ڕW���ԂɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void execSmoothMvVeloSequenceT(velo prm_top_velo, velo prm_end_velo,
                                   int prm_target_frames, float prm_p1, float prm_p2,
                                   bool prm_endacc_flg = true);




//    void execSmoothMvVeloSequence4(velo prm_end_velo, coord prm_target_distance, int prm_target_frames,
//                                   bool prm_endacc_flg = true);
    bool isMoveingSmooth();


    /**
     * ���qA�̎d�������p�� .
     * ���� GgafDx9KurokoA �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pKurokoA ���p��
     */
    void takeoverMvFrom(GgafDx9KurokoA* prm_pKurokoA);

    void resetMv();


    /**
     * ���qA���@�\���� .
     * ���qA�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɍ��qA��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9KurokoA();
};

}
#endif /*GGAFDX9MVNAVIGATOR_H_*/

