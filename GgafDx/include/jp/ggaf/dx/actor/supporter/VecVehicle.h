#ifndef GGAF_DX_VECVEHICLE_H_
#define GGAF_DX_VECVEHICLE_H_
#include "GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �A�N�^�[���悹��͎ԁi�A�N�^�[�̐���ړ��x���j .
 * �͎Ԃ͉�X�̖ڂɂ͐G��܂��񂪁A����(�A�N�^�[)�������グ�A�u�ړ��v�u�����̉�]�v���s�킹�鐢�b�l�ł��B<BR>
 * ����(�A�N�^�[)�͎���̈ӎv�œ��삹���Ƃ��A�͎Ԃ̂������ŕ�����щ�܂�邱�Ƃ��ł��܂��B<BR>
 * ��{�I�ȓ���͎͗ԂłقƂ�ǃJ�o�[�ł��Ă��܂��܂��B���̂����ŁA���҂͎��g�̉��Z�ɏW���ł���̂ł��B<BR>
 * ������񉉎Ҏ��g�����͂��Ĉړ��E��]���s���ƁA�͎Ԃ����ł͏o���Ȃ��A��蕡�G�Ȉړ�������\�ł��傤�B<BR>
 * ���҈�l�ɂ��A�͎Ԃ��W���ň�l�t�����Ă��܂��B<BR>
 * <BR>
 * ����͂��Ēu���A�܂�͍��W�v�Z�x���i���ʉ��j�N���X�ł��B<BR>
 * GeometricActor �̃����o��<BR>
 *  _x,  _y,  _z  �E�E�E �A�N�^�[�̍��W<BR>
 * _rx, _ry, _rz  �E�E�E �A�N�^�[�̎���]�p�x<BR>
 * ��ω������܂��B�����x�N�g���A���x�A�����A���ԁA�ɂ���ĊǗ����삷�邽�߂ɍ쐬�����N���X�B<BR>
 * ���ʂ̊�{�I�Ȉړ��A��]�͎͗ԂɔC���āA<BR>
 * �A�N�^�[�ŗL�̓���Ȉړ���]����� processBehave() �ɒ��ڋL�q�B�Ƃ����݌v�v�z�B<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class VecVehicle : public ActorVehicle {

private:
    /** [r]�͎Ԃ̏���A(�ړ����x�̕⍲) */
    VecVehicleMvAssistant* _pAsstMv;
    /** [r]�͎Ԃ̏���B(����]���p�p���x�̕⍲) */
    VecVehicleFaceAngAssistant* _pAsstFaceAng;
    /** [r]�͎Ԃ̏���C(�ړ����p�p���x�̕⍲) */
    VecVehicleMvAngAssistant* _pAsstMvAng;

public:
    /** [r]�ΏۃA�N�^�[ */
   // GeometricActor* const _pActor;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    explicit VecVehicle(GeometricActor* prm_pActor);

    /**
     * �͎Ԃ̏���A(�ړ����x�̕⍲)���擾 .
     * @return �͎Ԃ̏���A
     */
    VecVehicleMvAssistant* asstMv();

    /**
     * �͎Ԃ̏���B(����]���p�p���x�̕⍲)���擾 .
     * @return �͎Ԃ̏���B
     */
    VecVehicleFaceAngAssistant* asstFaceAng();

    /**
     * �͎Ԃ̏���C(�ړ����p�p���x�̕⍲)���擾 .
     * @return �͎Ԃ̏���C
     */
    VecVehicleMvAngAssistant* asstMvAng();

    void reset();

public: //_rx , _ry, _rz ����֘A //////////////////////////////////////////////
    /** [r]�ΏۃL�����̌���(_rx, _ry, _rz)�ւ̎Q�� */
    angle* _actor_face[3];
    /** [r/w]����]���p�̊p���x�i����]���p�ɖ��t���[�����Z������p�j */
    angvelo _angvelo_face[3];
    /** [r/w]����]���p�̊p���x���(�ō��l��360,000) */
    angvelo _top_angvelo_face[3];
    /** [r/w]����]���p�̊p���x����(�ō��l��-360,000) */
    angvelo _bottom_angvelo_face[3];
    /** [r/w]����]���p�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacce_face[3];
    /** [r/w]����]���p�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    angjerk _angjerk_face[3];
    /** [r/w]�ڕW�̎���]���p���������L���t���O */
    bool _is_targeting_face[3];
    /** [r/w]�ڕW�̎���]���p������~�@�\�L���t���O */
    bool _face_targeting_stop_flg[3];
    /** [r/w]�ڕW�Ƃ���L�����̎���]���p�̕��p(0�`360,000) */
    angle _target_face[3];
    /** [r/w]�ڕW�̎���]���p������~�@�\���L���ɂȂ��]���� */
    int _face_stop_allow_way[3]; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]�ڕW�̎���]���p������~�@�\���L���ɂȂ�p���x�i��]�������ʁj */
    angvelo _face_stop_allow_angvelo[3]; //���̊p���x��菬�����l�̏ꍇ�@�\�L���Ƃ���z

public:
    void setMvAngByFaceAng() {
        setRzRyMvAng(_pActor->_rz, _pActor->_ry);
    }
    /**
     * Actor�̖ڕW�̎���]���p������~�@�\��L��(�ڕW�̎���]���p�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ����]���p�ɂȂ�ƁA����]���p�p���x�y�ю���]���p�p�����x�� 0 �ɂ��A��]���~�����܂��B<BR>
     * ����]���p�p���x�� 0 �̏ꍇ�A�����N����܂���B�{���\�b�h�����s��������ƌ����ď���Ɍ������ς��ƂƂ����Ӗ��ł͂���܂���B <BR>
     * ����]���p�p���x���̐ݒ�𕹂��Ď��s���āA�ʓr����]���s�Ȃ��Ă��������B<BR>
     * �����I�ɂ́AaddFaceAng(prm_axis, int) �����t���[���s����d�g�݂ł��B<BR>
     * �ڕW�̉�]���p�ɓ��B�����Ȃ�΁A���̖ڕW�̎���]���p������~�@�\�͉���(�����̃t���O���A���Z�b�g)����܂��B<BR>
     * @param   prm_axis    ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_target    ���B�ڕW�̉�]���p(0�`360,000)
     * @param   prm_allow_way  ������~��������i������(TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE/TURN_BOTH)
     * @param   prm_allow_angvelo ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTargetFaceAng(axis prm_axis,
                              angle prm_target,
                              int prm_allow_way = TURN_BOTH,
                              angvelo prm_allow_angvelo = D360ANG);

    /**
     * Actor�̖ڕW��]����������~�@�\��L��(����XY���W����̑Ώ�XY���W�Őݒ�)<BR>
     * @param   prm_axis    ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param   prm_tx  �Ώ�X���W
     * @param   prm_ty  �Ώ�Y���W
     * @param   prm_allow_way  ������~�@�\���L���ɂȂ��]����
     * @param   prm_allow_angvelo ������~�@�\���L���ɂȂ��]�p���x
     */
    void setStopTargetFaceAngTwd(axis prm_axis,
                                 coord prm_tx,
                                 coord prm_ty,
                                 int prm_allow_way = TURN_BOTH,
                                 angvelo prm_allow_angvelo = D360ANG);
    /**
     * ����]���p�̊p���x�i����]���p�ɖ��t���[�����Z����l�j��ݒ� .
     * @param prm_axis ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_angvelo �p���x
     */
    void setFaceAngVelo(axis prm_axis, angvelo prm_angvelo);

    /**
     * ����]���p�̊p���x�i����]���p�ɖ��t���[�����Z����l�j��ݒ� .
     * @param prm_axis_x_angvelo X����]�̊p���x
     * @param prm_axis_z_angvelo Z����]�̊p���x
     * @param prm_axis_y_angvelo Y����]�̊p���x
     */
    void setRollPitchYawFaceAngVelo(angvelo prm_axis_x_angvelo,
                                    angvelo prm_axis_z_angvelo,
                                    angvelo prm_axis_y_angvelo);

    /**
     * Rolling(X����]���p)�̊p���x��ݒ� .
     * setFaceAngVelo(AXIS_X, prm_angvelo); �Ɠ����B
     * @param prm_axis_x_angvelo X����]�̊p���x
     */
    inline void setRollFaceAngVelo(angvelo prm_axis_x_angvelo) {
        setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    }
    inline void setRxFaceAngVelo(angvelo prm_axis_x_angvelo) {
        setFaceAngVelo(AXIS_X, prm_axis_x_angvelo);
    }

    /**
     * Pitching(Z����]���p)�̊p���x��ݒ� .
     * setFaceAngVelo(AXIS_Z, prm_angvelo); �Ɠ����B
     * @param prm_axis_z_angvelo Z����]�̊p���x
     */
    inline void setPitchFaceAngVelo(angvelo prm_axis_z_angvelo) {
        setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    }
    inline void setRzFaceAngVelo(angvelo prm_axis_z_angvelo) {
        setFaceAngVelo(AXIS_Z, prm_axis_z_angvelo);
    }

    /**
     * Yawing(Y����]���p)�̊p���x��ݒ� .
     * setFaceAngVelo(AXIS_Y, prm_angvelo); �Ɠ����B
     * @param prm_axis_y_angvelo Y����]�̊p���x
     */
    inline void setYawFaceAngVelo(angvelo prm_axis_y_angvelo) {
        setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
    }
    inline void setRyFaceAngVelo(angvelo prm_axis_y_angvelo) {
        setFaceAngVelo(AXIS_Y, prm_axis_y_angvelo);
    }


    void forceFaceAngVeloRange(axis prm_axis,
                               angvelo prm_angvelo01,
                               angvelo prm_angvelo02);
    /**
     * ����]���p�̊p�����x�i����]���p�̊p���x�ɖ��t���[�����Z����l�j��ݒ� .
     * @param prm_axis ��]���iAXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_angacce �p�����x
     */
    void setFaceAngAcce(axis prm_axis, angacce prm_angacce);

    /**
     * Rolling(X����]���p)�̊p�����x��ݒ� .
     * setFaceAngAcce(AXIS_X, prm_angacce); �Ɠ����B
     * @param prm_axis_x_angacce X����]���p�̊p�����x
     */
    inline void setRollFaceAngAcce(angvelo prm_axis_x_angacce) {
        setFaceAngAcce(AXIS_X, prm_axis_x_angacce);
    }
    inline void setRxFaceAngAcce(angvelo prm_axis_x_angacce) {
        setFaceAngAcce(AXIS_X, prm_axis_x_angacce);
    }

    /**
     * Pitching(Z����]���p)�̊p�����x��ݒ� .
     * setFaceAngAcce(AXIS_Z, prm_angacce); �Ɠ����B
     * @param prm_axis_z_angacce Z����]���p�̊p�����x
     */
    inline void setPitchFaceAngAcce(angvelo prm_axis_z_angacce) {
        setFaceAngAcce(AXIS_Z, prm_axis_z_angacce);
    }

    inline void setRzFaceAngAcce(angvelo prm_axis_z_angacce) {
        setFaceAngAcce(AXIS_Z, prm_axis_z_angacce);
    }

    /**
     * Yawing(Y����]���p)�̊p�����x��ݒ� .
     * setFaceAngAcce(AXIS_Y, prm_angacce); �Ɠ����B
     * @param prm_axis_y_angacce Y����]���p�̊p�����x
     */
    inline void setYawFaceAngAcce(angvelo prm_axis_y_angacce) {
        setFaceAngAcce(AXIS_Y, prm_axis_y_angacce);
    }

    inline void setRyFaceAngAcce(angvelo prm_axis_y_angacce) {
        setFaceAngAcce(AXIS_Y, prm_axis_y_angacce);
    }

    angle getFaceAngDistance(axis prm_axis, coord prm_tx, coord prm_ty, int prm_way);

    angle getFaceAngDistance(axis prm_axis, angle prm_target, int prm_way);

    ////////////////////////////////////////////////////MOVER

public: //_x, _y, _z ����֘A //////////////////////////////////////////////
    /** [r]�L�����̈ړ����p�P�ʃx�N�g�� */
    float _vX, _vY, _vZ;
    /** [r/w]�ړ����p��Z����]�p */
    angle _rz_mv;
    /** [r/w]�ړ����p��Y����]�p */
    angle _ry_mv;
    /** [r/w]�ړ����x */
    velo _velo_mv;
    /** [r/w]�ړ����x��� */
    velo _top_velo_mv;
    /** [r/w]�ړ����x���� */
    velo _bottom_velo_mv;
    /** [r/w]�ړ������x */
    acce _acc_mv;

    /** [r/w]�ړ����p�iZ����]�j�̊p���x�i�ړ����p�iZ����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angvelo_rz_mv;
    /** [r/w]�ړ����p�iZ����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _top_angvelo_rz_mv;
    /** [r/w]�ړ����p�iZ����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _bottom_angvelo_rz_mv;
    /** [r/w]�ړ����p�iZ����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacce_rz_mv;
    /** [r/w]�ړ����p�iZ����]�j�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    angjerk _angjerk_rz_mv;
    /** [r/w]�ڕW�̈ړ����p�iZ����]�j�����L���t���O */
    bool _is_targeting_rz_mv;
    /** [r/w]�ڕW�̈ړ����p�iZ����]�j������~�@�\�L���t���O */
    bool _rz_mv_targeting_stop_flg;
    /** �ڕW�Ƃ���L�����̈ړ����p�iZ����]�j�̕��p(0�`360,000) */
    angle _target_rz_mv;
    /** [r/w]�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _rz_mv_stop_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]�ڕW�̈ړ����p�iZ����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _rz_mv_stop_allow_angvelo;
    /** [r/w]�����O�������@�\�L���t���O */
    bool _relate_RzFaceAng_with_RzMvAng_flg;
    //true  : �ړ����p�iZ����]�j��ύX����ƁA����ɔ����������p������]���p(Z��)�ɂ��ݒ肳���
    //false : �ړ����p�iZ����]�j��Z������]���p�͓Ɨ�

    /** [r/w]�ړ����p�iY����]�j�̊p���x�i�ړ����p�iY����]�j�ɖ��t���[�����Z������p�j */
    angvelo _angvelo_ry_mv;
    /** [r/w]�ړ����p�iY����]�j�̊p���x���(�ō��l��360,000) */
    angvelo _top_angvelo_ry_mv;
    /** [r/w]�ړ����p�iY����]�j�̊p���x����(�ō��l��-360,000) */
    angvelo _bottom_angvelo_ry_mv;
    /** [r/w]�ړ����p�iY����]�j�̊p�����x�i�p���x�ɖ��t���[�����Z����l�j */
    angacce _angacce_ry_mv;
    /** [r/w]�ړ����p�iY����]�j�̊p���x�i�p�����x�ɖ��t���[�����Z����l�j */
    angjerk _angjerk_ry_mv;
    /** [r/w]�ڕW�̈ړ����p�iY����]�j���������L���t���O */
    bool _is_targeting_ry_mv;
    /** [r/w]�ڕW�̈ړ����p�iY����]�j������~�@�\�L���t���O */
    bool _ry_mv_targeting_stop_flg;
    /** [r/w]�ڕW�Ƃ���L�����̈ړ����p�iY����]�j�̕��p(0�`360,000) */
    angle _target_ry_mv;
    /** [r/w]�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�i����]���� */
    int _ry_mv_stop_allow_way; //TURN_CLOCKWISE or TURN_COUNTERCLOCKWISE or TURN_BOTH
    /** [r/w]�ڕW�̈ړ����p�iY����]�j������~�@�\���L���ɂȂ�ړ����p�p���x */
    angvelo _ry_mv_stop_allow_angvelo;
    /** [r/w]�����O�������@�\�L���t���O */
    bool _relate_RyFaceAng_with_RyMvAng_flg;
    //true  : �ړ����p�iY����]�j��ύX����ƁA����ɔ����������p������]���p(Y��)�ɂ��ݒ肳���
    //false : �ړ����p�iY����]�j��Y������]���p�͓Ɨ�

    bool _taget_face_alltime_flg;
    const GeometricActor* _taget_face_alltime_pActor;
    coord _taget_face_alltime_tx;
    coord _taget_face_alltime_ty;
    coord _taget_face_alltime_tz;
    angvelo _taget_face_alltime_angvelo;
    angacce _taget_face_alltime_angacce;
    int _taget_face_alltime_way;
    bool _taget_face_alltime_optimize_ang;

public:
    /**
     * �ړ����x��ݒ� .
     * @param   prm_velo_mv  �ړ����x
     */
    void setMvVelo(velo prm_velo_mv);

    /**
     * �ړ����x�����Z .
     * @param prm_velo_mv_Offset ���Z�ړ����x
     */
    void addMvVelo(velo prm_velo_mv_Offset);

    /**
     * �ړ����x�̏��������ݒ肵�A�ړ����x�͈̔͂𐧌����� .
     * �����̈ړ����x�P�A�ړ����x�Q�̑召�͂ǂ���ł����܂�Ȃ��B�i�����Ŕ��肷��j
     * @param prm_velo_mv01  �ړ����x�P
     * @param prm_velo_mv02  �ړ����x�Q
     */
    void forceMvVeloRange(velo prm_velo_mv01, velo prm_velo_mv02);

    /**
     * �ړ����x�̏��������ݒ肵�A�ړ����x�͈̔͂𐧌����� .
     * ��������l�́A-prm_velo_mv �` prm_velo_mv �͈̔͂ɂȂ�B
     * @param prm_velo_mv �ړ����x
     */
    void forceMvVeloRange(velo prm_velo_mv);

    /**
     * ���݂̈ړ����x���擾 .
     * @return ���݂̈ړ����x
     */
    inline velo getMvVelo() const {
        return _velo_mv;
    }

    /**
     * ����ړ����x���擾 .
     * @return ����ړ����x
     */
    inline velo getMvVeloTop() const {
        return _top_velo_mv;
    }

    /**
     * �����ړ����x���擾 .
     * @return �����ړ����x
     */
    inline velo getMvVeloBottom() const {
        return _bottom_velo_mv;
    }

    /**
     * ���݂̈ړ����x������ړ����x�ɍX�V .
     */
    inline void setMvVeloTop() {
        _velo_mv = _top_velo_mv;
    }

    /**
     * ���݂̈ړ����x�������ړ����x�ɍX�V .
     */
    inline void setMvVeloBottom() {
        _velo_mv = _bottom_velo_mv;
    }

    /**
     * �ړ������x��ݒ� .
     * @param prm_acceMove �ړ������x
     */
    void setMvAcce(acce prm_acceMove);

    /**
     * �ړ������x���A�u��~�ړ������v�ɂ��ݒ肷�� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^       a:�������x�i_acc_mv �ɐݒ肳���j
     *     |       D:��~�܂ł̈ړ������i�����j
     *     |      V0:�����_�̑��x�i= ���݂� _velo_mv ���g�p�����j
     *   V0|      Te:��~����t���[�� �i�߂�l�j
     *     |�_
     *     |  �_
     *     |    �_ �Εӂ̌X��a
     *     |   D  �_
     *     |        �_
     *   --+----------�_-----> ����(t)
     *   0 |          Te
     *
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�����̋���(D)����A�����x(a)���v�Z�� _acc_mv �ݒ肵�Ă���B<BR>
     * ��~�܂ł̃t���[��(Te) �� ����(D) �ɂ��ω����邽�ߎw��s�B<BR>
     * @param prm_target_distance ��~���ړ�����(D)
     * @return �K�v�Ȏ��ԃt���[��(Te)�B�Q�l�l�ɂǂ����B
     */
    frame setMvAcceToStop(coord prm_target_distance);


    /**
     * ����]���p�̊p�����x���A�u��~�̋����p�v�ɂ��ݒ肷�� .
     * @param prm_axis ��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_target_distance ��~�̈ړ��p�x����(D)
     * @return �K�v�Ȏ��ԃt���[��(Te)�B�Q�l�l�ɂǂ����B
     */
    frame setFaceAngAcceToStop(axis prm_axis, angle prm_target_distance);


    /**
     * �ړ������x���A�u�ڕW���B���x�v�u�ړ�����(�B����܂łɔ�₷����)�v�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x�i_acc_mv �ɐݒ肳���j
     *     |        D:�ړ������i�����j
     *     |       V0:�����_�̑��x�i= ���݂� _velo_mv ���g�p�����j
     *     |       Vt:�ڕW���B���x�i�����j
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�߂�l�j
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> ����(t)
     *   0 |        Te
     *
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA�ړ�����(D)����A�����x(a)���v�Z�� _acc_mv �ɐݒ肵�Ă���B<BR>
     * �ڕW���B�܂ŕK�v�ȃt���[��(Te) �̓p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * �ߑ��FsetMvAcceByD(0, D) �� setMvAcceToStop(D) �Ɠ����ł���
     * @param prm_target_distance  �ڕW���B���x�ɒB����܂łɔ�₷����(D)
     * @param prm_target_velo �ڕW���B���x(Vt)
     * @return �K�v�Ȏ��ԃt���[��(Te)�B�Q�l�l�ɂǂ����B
     */
    frame setMvAcceByD(coord prm_target_distance, velo prm_target_velo);

    /**
     * ����]���p�̊p�����x���u�����p(�B����܂łɔ�₷����)�v�u�ڕW���B���p���x�v�ɂ��ݒ� .
     * @param prm_axis ��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_target_distance �ڕW���B�p���x�ɒB����܂łɔ�₷��]����(D)
     * @param prm_target_angvelo �ڕW���B�p���x(Vt)
     * @return �K�v�Ȏ��ԃt���[��(Te)�B�Q�l�l�ɂǂ����B
     */
    frame setFaceAngAcceByD(axis prm_axis, angle prm_target_distance, angvelo prm_target_angvelo);

    /**
     * �ړ������x���A�u�ڕW���B���x�v�u��₷���ԁv�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x�i_acc_mv �ɐݒ肳���)
     *     |        D:�ړ����� �i�߂�l�j
     *     |       V0:�����_�̑��x�i= ���݂� _velo_mv ���g�p�����j
     *     |       Vt:�ڕW���B���x�i�����j
     *     |       Te:�ڕW���B���x�ɒB�������̎��ԁi�����j
     *   Vt|........
     *     |      �^|
     *     |    �^  |
     *     |  �^    |   �Εӂ̌X��a
     *     |�^      |
     *   V0|    D   |
     *     |        |
     *   --+--------+---> ����(t�t���[��)
     *   0 |        Te
     *
     *    a = (Vt-V0) / Te
     * </code></pre>
     * ��}�̂悤�ȏ�Ԃ�z�肵�A�ڕW���B���x(Vt)�ƁA���̓��B����(Te) ����A�����x(a)���v�Z���ݒ肵�Ă���B<BR>
     * �ړ�����(D)�́A�p�����[�^�ɂ��ω����邽�ߎw��s�B<BR>
     * @param prm_target_frames ��₷����(Te)
     * @param prm_target_velo   �ڕW���B���x(Vt)
     * @return �ړ�����(D)
     */
    coord setMvAcceByT(frame prm_target_frames, velo prm_target_velo);

    /**
     * ����]���p�̊p�����x���u�ڕW���B�p���x�v�u��₷���ԁv�ɂ��ݒ� .
     * @param prm_axis ��]��(AXIS_X / AXIS_Y / AXIS_Z)
     * @param prm_target_frames  ��₷����(Te)
     * @param prm_target_angvelo �ڕW���B���x(Vt)
     * @return �ړ��p����(D)
     */
    angle setFaceAngAcceByT(axis prm_axis, frame prm_target_frames, angvelo prm_target_angvelo);

    /**
     * Actor�̈ړ����p�iZ����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_relate_RzFaceAng_with_RzMvAng_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iZ����]�j�Ɠ��������������悤�� setStopTargetFaceAng(int) �����s����܂��B<BR>
     *
     * @param   prm_ang �ړ����p�iZ����]�j(0�`360,000)
     */
    void setRzMvAng(angle prm_ang);

    /**
     * ���݂� Actor �̈ړ����p�iZ����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iZ����]�j�̑����ł��BActor�̈ړ����p�iZ����]�j�i_rz_mv�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iZ����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRzMvAng(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iZ����]�j�́AZ���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _bottom_angvelo_rz_mv �� �����̓����p���� �� _top_angvelo_rz_mv  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iZ����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_relate_RzFaceAng_with_RzMvAng_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iZ����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �{���\�b�h���t���[�����s���邱�Ƃ�XY���ʂ̉~�^�����\�ɂȂ�܂��B<BR>
     * �����̈ړ����p�iZ����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iZ����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Z���ړ������x�̏���Ɖ����i_bottom_angvelo_rz_mv�A_top_angvelo_rz_mv) ��  -360000 , 360000<BR>
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iZ����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param   prm_ang �ړ����p�iZ����]�j����(�͈́F_bottom_angvelo_rz_mv �` _top_angvelo_rz_mv)
     */
    void addRzMvAng(angle prm_ang);

    angle getRzMvAng() {
        return _rz_mv;
    }
    /**
     * Actor�̖ڕW�̈ړ����p�iZ����]�j������~�@�\��L��(�ڕW�̈ړ����p�iZ����]�j�ݒ�)<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iZ����]�j�ɂȂ�܂ŁA�ړ����p�iZ����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iZ����]�j�̊p���x�i_angvelo_rz_mv�j�̐����Ō��肳��܂��B<BR>
     * <B>�ړ����p�iZ����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRzMvAng(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iZ����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iZ����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param   prm_target_rz_mv ���B�ڕW�̈ړ����p�iZ����]�j(-360,000�`360,000)
     * @param   prm_allow_way  ������~�@�\���L���ɂȂ�i����]����
     * @param   prm_allow_angvelo ��~�@�\���L���ɂȂ�ړ����p�p���x(����ȏ�̊p���x�̏ꍇ�͒�~���܂���)
     */
    void setStopTargetRzMvAng(angle prm_target_rz_mv,
                              int prm_allow_way = TURN_BOTH,
                              angvelo prm_allow_angvelo = D360ANG);

    void setRzMvAngVelo(angvelo prm_angvelo_rz_mv);

    void forceRzMvAngVeloRange(angvelo prm_angvelo_rz_mv01, angvelo prm_angvelo_rz_mv02);

    void setRzMvAngAcce(angacce prm_angacce_rz_mv);

    angle getRzMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way);

    /**
     * ���g�̈ړ����p��Z����]�p( _rz_mv )�ƁA�^�[�Q�b�g�̉�]�p�Ƃ̍������擾.
     * TURN_COUNTERCLOCKWISE �E�E�E��]�����������ō��يp�擾�A���̒l�ŕԂ�B
     * TURN_CLOCKWISE        �E�E�E��]�������E���ō��يp�擾�A���̒l�ɕԂ�B
     * TURN_CLOSE_TO         �E�E�E�^�[�Q�b�g�̉�]�p�Ƌ������߂����̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * TURN_ANTICLOSE_TO     �E�E�E�^�[�Q�b�g�̉�]�p�Ƌ������������̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B
     * @param prm_target_rz_mv �^�[�Q�b�g�p�̒l
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @return
     */
    angle getRzMvAngDistance(angle prm_target_rz_mv, int prm_way);

    /**
     * Actor�̈ړ����p�iY����]�j��ݒ�B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A������ 0�`360,000 �͈͓̔��̒l�ɍČv�Z����܂��B<BR>
     * �����O�������@�\���L��(_relate_RyFaceAng_with_RyMvAng_flg)�̏ꍇ�A<BR>
     * Actor�̌������ړ����p�iY����]�j�Ɠ��������������悤�� setStopTargetFaceAng(int) �����s����܂��B<BR>
     * @param prm_ang �ړ����p�iY����]�j(0�`360,000)
     */
    void setRyMvAng(angle prm_ang);

    /**
     * ���݂� Actor �̈ړ����p�iY����]�j�։��Z�i���Ō��Z�j�B<BR>
     *
     * �����ɓn���̂́A�ړ����p�iY����]�j�̑����ł��BActor�̈ړ����p�iY����]�j�i_ry_mv�j�𑊑Ύw��ł郁�\�b�h�ł��B<BR>
     * ���Z��̈ړ����p�iY����]�j���͈͊O�i0�`360,000 �ȊO�j�̒l�ɂȂ��Ă��A�ŏI�I�ɂ� setRyMvAng(int) ���Ăяo���܂��̂�<BR>
     * ������ 0�`360,000 �͈͓̔��̒l�ɍĐݒ肳��܂��B<BR>
     * �����ł�����Z�i���Z�j����ړ����p�iY����]�j�́AY���ړ������x�̏���Ɖ����̊Ԃ͈̔͂Ɍ���܂��B<BR>
     * �܂�A�����̗L���Ȕ͈͈͂ȉ��̒ʂ�ƂȂ�܂��B<BR>
     *
     *   _bottom_angvelo_ry_mv �� �����̓����p���� �� _top_angvelo_ry_mv  �ł��B<BR>
     *
     * �����͈͊O�̈����̈ړ����p�iY����]�j�������w�肵���ꍇ�́A���߂͈͓̔��̒l�ɋ����I�ɗ}�����A���̒l�����Z����܂��B<BR>
     * �܂��A�����O�������@�\���L��(_relate_RyFaceAng_with_RyMvAng_flg)�̏ꍇ�A<BR>
     * ���Z��̈ړ����p�iY����]�j�̒l���AZ���̖ڕW�̎���]���p�Ƃ��Đݒ肳��܂��B�i�����őO���������ɐݒ肳��܂��B�A���O�����A���O��0�̃L�����̏ꍇ�ł����ǁG�j<BR>
     *
     * �y�⑫�F�z<BR>
     * �{���\�b�h���t���[�����s���邱�Ƃ�XZ���ʂ̉~�^�����\�ɂȂ�܂��B<BR>
     * �����̈ړ����p�iY����]�j���A��������� 0 �ɁA���߂��l�����Z���������ꍇ�́A�ɂ₩�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �t�ɁA�����̈ړ����p�iY����]�j���A0 ����A��藣�ꂽ�l�����Z���������ꍇ�́A���s�p�I�ȃJ�[�u�`���Ȃ�����]�����邱�Ƃ��Ӗ����܂��B<BR>
     * �f�t�H���g��Y���ړ������x�̏���Ɖ����i_bottom_angvelo_ry_mv�A_top_angvelo_ry_mv) ��<BR>
     *
     *  -360,000 �� �����̓����p���� �� 360,000<BR>
     *
     * �ƂȂ��Ă��܂��B����͏u���Ɂi1�t���[���Łj�ǂ�Ȉړ����p�iY����]�j�ɂ�������ς���邱�Ƃ��Ӗ����܂��B<BR>
     *
     * @param   prm_ang �ړ����p�iY����]�j����(�͈́F_bottom_angvelo_ry_mv �` _top_angvelo_ry_mv)
     */
    void addRyMvAng(angle prm_ang);

    angle getRyMvAng() {
        return _ry_mv;
    }

    /**
     * Actor�̖ڕW��Y����]�ړ����p�̎�����~�@�\��L�� .
     * �ڕW�̈ړ����p�iY����]�j�ݒ肷��B<BR>
     * �����ɐݒ肳�ꂽ�ړ����p�iY����]�j�ɂȂ�܂ŁA�ړ����p�iY����]�j�����Z(���Z)�𖈃t���[���s�������܂��B<BR>
     * ���Z�����Z���́A�ړ����p�iY����]�j�̊p���x�i_angvelo_ry_mv�j�̐����Ō��肳��܂��B<BR>
     * <B>�ړ����p�iY����]�j�̊p���x�� 0 �Ȃ�΁A�����N����܂���B</B>���삳����ɂ́A�p���x���K�v�ł��B<BR>
     * �����I�ɂ́AaddRyMvAng(int) �����t���[���s����d�g�݂ł��B(this->behave()�Ŏ��s)<BR>
     * �ڕW�̈ړ����p�iY����]�j�ɓ��B�����Ȃ�΁A���̖ڕW�̈ړ����p�iY����]�j������~�@�\�͉�������܂��B<BR>
     *
     * @param   prm_target_ry_mv ���B�ڕW�̈ړ����p�iY����]�j(-360,000�`360,000)
     * @param   prm_allow_way  ������~�@�\���L���ɂȂ�i����]����
     * @param   prm_allow_angvelo ��~�@�\���L���ɂȂ�ړ����p�p���x(����ȏ�̊p���x�̏ꍇ�͒�~���܂���)
     */
    void setStopTargetRyMvAng(angle prm_target_ry_mv,
                              int prm_allow_way = TURN_BOTH,
                              angvelo prm_allow_angvelo = D360ANG);

    void setRyMvAngVelo(angvelo prm_angvelo_ry_mv);

    void forceRyMvAngVeloRange(angvelo prm_angvelo_ry_mv01, angvelo prm_angvelo_ry_mv02);

    void setRyMvAngAcce(angacce prm_angacce_ry_mv);

    angle getRyMvAngDistanceTwd(coord prm_tx, coord prm_ty, int prm_way);

    angle getRyMvAngDistance(angle prm_target_ry_mv, int prm_way);


    void forceRzRyMvAngVeloRange(angvelo prm_angvelo_rzry_mv01, angvelo prm_angvelo_rzry_mv02);

    void setRzRyMvAngVelo(angvelo prm_angvelo_rz_mv, angvelo prm_angvelo_ry_mv);

    void setRzRyMvAngAcce(angacce prm_angacce_rz_mv, angacce prm_angacce_ry_mv);


    /**
     * ���g�̈ړ����p��Z��Y����]�p(_rz_mv, _ry_mv)�ƁA�^�[�Q�b�g�̉�]�p�Ƃ̍œK�ȍ������擾 .
     * �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     * ���B�A���O�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     * (���ӁF�ɒnY����]�����邽�߁A�ŏ��A���O�����͕K�������ŒZ�����ɂ��炸)<BR>
     * ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     * �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     * ��v���Ȃ����Ƃ�����ꍇ�́AZ��Y���ʂɋ��������߂ĉ������B<BR>
     * @param prm_target_rz
     * @param prm_target_ry
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param out_d_rz
     * @param out_d_ry
     */
    void getRzRyMvAngDistanceTwd(angle prm_target_rz, angle prm_target_ry,int prm_way,
                                 angle& out_d_rz, angle& out_d_ry);

    /**
     * ���g�̎���]���p��Z��Y����]�p(_face[AXIS_Z], _face[AXIS_Y])�ƁA�^�[�Q�b�g�̉�]�p�Ƃ̍œK�ȍ������擾 .
     * �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     * ���B�A���O�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     * (���ӁF�ɒnY����]�����邽�߁A�ŏ��A���O�����͕K�������ŒZ�����ɂ��炸)<BR>
     * ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     * �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     * ��v���Ȃ����Ƃ�����ꍇ�́AZ��Y���ʂɋ��������߂ĉ������B<BR>
     * @param prm_target_rz
     * @param prm_target_ry
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param out_d_rz
     * @param out_d_ry
     */
    void getRzRyFaceAngDistanceTwd(angle prm_target_rz, angle prm_target_ry,int prm_way,
                                   angle& out_d_rz, angle& out_d_ry);
    /**
     * �ړ�����(RzRy)��ݒ� .
     * @param prm_rz
     * @param prm_ry
     */
    void setRzRyMvAng(angle prm_rz, angle prm_ry);

    /**
     * �ړ�����(RzRy)������x�N�g���ɂ��ݒ� .
     * @param prm_vx �����x�N�g��X���v�f
     * @param prm_vy �����x�N�g��Y���v�f
     * @param prm_vz �����x�N�g��Z���v�f
     * @param prm_opt �œK���t���O�itrue:RzRy�̍����ŏ��ɂȂ�悤�ɍœK������^false:���ʂ̃R���o�[�g)
     */
    void setRzRyMvAng(dxcoord prm_vx, dxcoord prm_vy, dxcoord prm_vz, bool prm_opt = false);

    /**
     *  �ړ�����(RzRy)���ARyRz�Őݒ�B
     * @param prm_ry
     * @param prm_rz
     */
    void setRzRyMvAngByRyRz(angle prm_ry, angle prm_rz);

    /**
     * �ڕW���W�_�����W�w��ňړ����p(RzRy)��ݒ�B.
     * �����x�N�g�����K���������ōs�Ȃ��B
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     */
    void setMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz);

    /**
     * �ڕW���W�_�����W�w��ňړ����p(RzRy)��ݒ�B.
     * �A�����s��(Z���W��)�������Čv�Z���s���B
     * �����x�N�g�����K���������ōs�Ȃ��B
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     */
    inline void setMvAngTwd(coord prm_tx, coord prm_ty) {
        setMvAngTwd(prm_tx, prm_ty, _pActor->_z);
    }

    /**
     * �ڕW���W�_�w��ΏۃA�N�^�[�̍��W�w��ňړ����p(RzRy)��ݒ�B.
     * �����x�N�g�����K���������ōs�Ȃ��B
     * @param prm_pActor_target �ڕW�ΏۃA�N�^�[
     */
    inline void setMvAngTwd(const GeometricActor* prm_pActor_target) {
        setMvAngTwd(
            prm_pActor_target->_x,
            prm_pActor_target->_y,
            prm_pActor_target->_z
        );
    }

    inline void setMvAngTwd(const GeoElem* prm_pGeoElem) {
        setMvAngTwd(
            prm_pGeoElem->x,
            prm_pGeoElem->y,
            prm_pGeoElem->z
        );
    }

    void reverseMvAng();

    void setStopTargetMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz);

    void setStopTargetMvAngTwd(const GeometricActor* prm_pActor_target);

    /**
     * ����]���p(Z����Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_rz_target �ڕW����]���p(Z��)
     * @param prm_ry_target �ڕW����]���p(Y��)
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void turnRzRyFaceAngTo(angle prm_rz_target, angle prm_ry_target,
                           angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                           int prm_way = TURN_CLOSE_TO,
                           bool prm_optimize_ang = false);

    /**
     * ����]���p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void turnFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                        angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                        int prm_way = TURN_CLOSE_TO,
                        bool prm_optimize_ang = false);


    /**
     * ����]���p(Z����Y��)��ڕW�Ƀ^�[�Q�b�g�̕����������悤�ȃV�[�N�G���X�����s
     * @param prm_pActor_target �ڕW�I�u�W�F�N�g
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    inline void turnFaceAngTwd(const GeometricActor* prm_pActor_target,
                               angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                               int prm_way = TURN_CLOSE_TO,
                               bool prm_optimize_ang = false) {
        turnFaceAngTwd(
                prm_pActor_target->_x,
                prm_pActor_target->_y,
                prm_pActor_target->_z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }
    inline void turnFaceAngTwd(const GeoElem* prm_pGeoElem,
                               angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                               int prm_way = TURN_CLOSE_TO,
                               bool prm_optimize_ang = false) {
        turnFaceAngTwd(
                prm_pGeoElem->x,
                prm_pGeoElem->y,
                prm_pGeoElem->z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * ����]���p��ڕW�̊p������]������V�[�N�G���X�����s .
     * @param prm_axis  �� (AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_distance �p�����i���FTURN_COUNTERCLOCKWISE�A���FTURN_CLOCKWISE�j
     * @param prm_angvelo �p���x�iprm_distance�̐����Ɉˑ��j
     * @param prm_angacce �p�����x�iprm_distance�̐����Ɉˑ��j
     */
    void turnFaceAng(axis prm_axis,
                     angle prm_distance,
                     angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0);

    /**
     * ����]���p(Z��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_rz_target �ڕW����]���p(Z��)
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRzFaceAngTo(angle prm_rz_target,
                         angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                         int prm_way = TURN_CLOSE_TO);

    /**
     * ����]���p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_ry_target �ڕW����]���p(Y��)
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRyFaceAngTo(angle prm_ry_target,
                         angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                         int prm_way = TURN_CLOSE_TO);

    /**
     * ����]���p(X��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_rx_target �ڕW����]���p(X��)
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void rollFaceAngTo(angle prm_rx_target,
                       angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                       int prm_way = TURN_CLOSE_TO);

    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_rz_target �ڕW�ړ����p(Z��)
     * @param prm_ry_target �ڕW�ړ����p(Y��)
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void turnRzRyMvAngTo(angle prm_rz_target, angle prm_ry_target,
                         angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                         int prm_way = TURN_CLOSE_TO,
                         bool prm_optimize_ang = false);

    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void turnMvAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                      angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                      int prm_way = TURN_CLOSE_TO,
                      bool prm_optimize_ang = false);

    /**
     * �ړ����p����ɖڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void keepOnTurningFaceAngTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                 angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                                 int prm_way = TURN_CLOSE_TO,
                                 bool prm_optimize_ang = false) {
        turnFaceAngTwd(prm_tx, prm_ty, prm_tz,
                       prm_angvelo,  prm_angacce,
                       prm_way, prm_optimize_ang );
        _taget_face_alltime_flg = true;
        _taget_face_alltime_pActor = nullptr;
        _taget_face_alltime_tx = prm_tx;
        _taget_face_alltime_ty = prm_ty;
        _taget_face_alltime_tz = prm_tz;
        _taget_face_alltime_angvelo = prm_angvelo;
        _taget_face_alltime_angacce = prm_angacce;
        _taget_face_alltime_way = prm_way;
        _taget_face_alltime_optimize_ang = prm_optimize_ang;
    }

    /**
     * �ړ����p����ɖڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_pActor_target �ڕW�I�u�W�F�N�g
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    void keepOnTurningFaceAngTwd(const GeometricActor* prm_pActor_target,
                                 angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                                 int prm_way = TURN_CLOSE_TO,
                                 bool prm_optimize_ang = false) {
        keepOnTurningFaceAngTwd(
                prm_pActor_target->_x,
                prm_pActor_target->_y,
                prm_pActor_target->_z,
                prm_angvelo, prm_angacce,
                prm_way, prm_optimize_ang);
        _taget_face_alltime_pActor = prm_pActor_target;
    }

    /**
     * �ړ����p��ڕW�Ƀ^�[�Q�b�g�̍��W�ɂ���V�[�N�G���X�����s
     * @param prm_pActor_target �ڕW�I�u�W�F�N�g
     * @param prm_angvelo �^�[�Q�b�e�B���O���s���ɉ��Z�����p�x�A�܂�p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO<BR>
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     */
    inline void turnMvAngTwd(const GeometricActor* prm_pActor_target,
                             angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                             int prm_way = TURN_CLOSE_TO,
                             bool prm_optimize_ang = false) {
        turnMvAngTwd(
                prm_pActor_target->_x,
                prm_pActor_target->_y,
                prm_pActor_target->_z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }

    inline void turnMvAngTwd(const GeoElem* prm_pGeoElem,
                             angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                             int prm_way = TURN_CLOSE_TO,
                             bool prm_optimize_ang = false) {
        turnMvAngTwd(
                prm_pGeoElem->x,
                prm_pGeoElem->y,
                prm_pGeoElem->z,
                prm_angvelo,
                prm_angacce,
                prm_way,
                prm_optimize_ang
        );
    }

    /**
     * �ړ����p(Z��)��ڕW�̊p������]������V�[�N�G���X�����s .
     * @param prm_rz_distance  �ړ����p�̉�]�p����(Z��)
     * @param prm_angvelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����p���x�i������prm_distance�̐����Ɉˑ��j
     * @param prm_angacce �p�����x�i������prm_distance�̐����Ɉˑ��j
     */
    void turnRzMvAng(angle prm_rz_distance,
                     angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0);

    /**
     * �ړ����p(Y��)��ڕW�̊p������]������V�[�N�G���X�����s .
     * @param prm_ry_distance  �ړ����p�̉�]�p����(Y��)
     * @param prm_angvelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����p���x�i������prm_distance�̐����Ɉˑ��j
     * @param prm_angacce �p�����x�i������prm_distance�̐����Ɉˑ��j
     */
    void turnRyMvAng(angle prm_ry_distance,
                     angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0);

    /**
     * �ړ����p(Z��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_rz_target �ڕW�ړ����p(Z��)
     * @param prm_angvelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRzMvAngTo(angle prm_rz_target,
                       angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                       int prm_way = TURN_CLOSE_TO);

    /**
     * �ړ����p(Y��)��ڕW�Ƀ^�[�Q�b�g����V�[�N�G���X�����s .
     * @param prm_ry_target �ڕW�ړ����p(Y��)
     * @param prm_angvelo �^�[�Q�b�g�ֈړ����p����]�ړ����ɓK�p����ڕW�ړ����p��]�ړ��p���x�i���̊p���x�Ŏw��B�����Ő�����������j
     * @param prm_angacce �p�����x�i���̊p�����x�Ŏw��B�����Ő�����������j
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     */
    void turnRyMvAngTo(angle prm_ry_target,
                       angvelo prm_angvelo = D360ANG, angacce prm_angacce = 0,
                       int prm_way = TURN_CLOSE_TO);

    void stopTurningMvAng();

    void stopTurningFaceAng();

    /**
     * �ڕW����]���p�Ƀ^�[�Q�b�g����V�[�N�G���X�����s���� .
     * turn**FaceAng**() �����s��A���]�̖ڕW�ړ����p�ɉ�]���̏ꍇ true�B
     * @return true:���s��/false:���s���łȂ�
     */
    bool isTurningFaceAng() const;

    /**
     * �ڕW�ړ����p�Ƀ^�[�Q�b�g����V�[�N�G���X�����s���� .
     * turn**MvAng**() �����s��A���]�̖ڕW�ړ����p�ɉ�]���̏ꍇ true�B
     * @return true:���s��/false:���s���łȂ�
     */
    bool isTurningMvAng() const;

    /**
     * �ړ����p�ɔ����Ď���]���p���X�V�iZ����]�ƁAY����]�����j .
     * true ��ݒ肷��ƁA�����I�Ɉړ����p�̕��Ɍ������ς��B<BR>
     * false ��ݒ肷��ƁA�ړ����p�ƌ����͓Ɨ��A�f�t�H���g�͂�����B<BR>
     * @param prm_b true:�ړ����p�ɔ����Ď���]���p���X�V/false:�ړ����p�Ǝ���]���p�͓Ɨ�
     */
    void linkFaceAngByMvAng(bool prm_b) {
        _relate_RyFaceAng_with_RyMvAng_flg = prm_b;
        _relate_RzFaceAng_with_RzMvAng_flg = prm_b;
        if (prm_b) {
            _pActor->_rz = _rz_mv;
            _pActor->_ry = _ry_mv;
        }
    }

    /**
     * �ړ����p�ɔ����Ď���]���p���X�V�iZ����]�̂݁j .
     * true ��ݒ肷��ƁAZ����]�̂ݎ����I�Ɉړ����p�̕��Ɍ������ς��B<BR>
     * false ��ݒ肷��ƁA�ړ����p�ƌ����͓Ɨ��A�f�t�H���g�͂�����B<BR>
     * @param prm_b true:Z����]�ɂ��Ĉړ����p�ɔ����Ď���]���p���X�V/false:�ړ����p�Ǝ���]���p�͓Ɨ�
     */
    void linkRzFaceAngByMvAng(bool prm_b) {
        _relate_RzFaceAng_with_RzMvAng_flg = prm_b;
        if (prm_b) {
            _pActor->_rz = _rz_mv;
        }
    }

    /**
     * �ړ����p�ɔ����Ď���]���p���X�V�iY����]�̂݁j .
     * true ��ݒ肷��ƁAY����]�̂ݎ����I�Ɉړ����p�̕��Ɍ������ς��B<BR>
     * false ��ݒ肷��ƁA�ړ����p�ƌ����͓Ɨ��A�f�t�H���g�͂�����B<BR>
     * @param prm_b true:Y����]�ɂ��Ĉړ����p�ɔ����Ď���]���p���X�V/false:�ړ����p�Ǝ���]���p�͓Ɨ�
     */
    void linkRyFaceAngByMvAng(bool prm_b) {
        _relate_RyFaceAng_with_RyMvAng_flg = prm_b;
        if (prm_b) {
            _pActor->_ry = _ry_mv;
        }
    }

    /**
     * �͎Ԃ̎d�������p�� .
     * ���� VecVehicle �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pVecVehicle ���p��
     */
    void takeoverFrom(VecVehicle* const prm_pVecVehicle);

    /**
     * �ړ����~���܂��B
     */
    void stop();

    /**
     * �͎Ԃ��U�镑�� .
     * �͎ԋ@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɗ͎Ԃ�K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~VecVehicle();
};

}
#endif /*GGAF_DX_VECVEHICLE_H_*/

