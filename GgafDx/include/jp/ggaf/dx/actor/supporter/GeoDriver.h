#ifndef GGAF_DX_GEODRIVER_H_
#define GGAF_DX_GEODRIVER_H_
#include "GgafDxCommonHeader.h"
#include "ActorDriver.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �A�N�^�[���悹����āi�A�N�^�[�̕��s�ړ��x���j .
 * GeometricActor �̃����o��<BR>
 *  _x, _y, _z  �E�E�E �A�N�^�[�̍��W<BR>
 * ���A�e�������ɊȒP�ɑ��삷�邽�߂ɍ쐬�B<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GeoDriver : public ActorDriver {

public:
    /** [r]�ΏۃA�N�^�[ */
    //GeometricActor* const _pActor;
    /** [r/w]X�������ړ����x */
    velo _velo_vx_mv;
    /** [r/w]X�������ړ����x��� */
    velo _top_velo_vx_mv;
    /** [r/w]X�������ړ����x���� */
    velo _bottom_velo_vx_mv;
    /** [r/w]X�������ړ������x */
    acce _acce_vx_mv;
    /** [r/w]X�������ړ������x���*/
    acce _top_acce_vx_mv;
    /** [r/w]X�������ړ������x����*/
    acce _bottom_acce_vx_mv;
    /** [r/w]Y�������ړ����x */
    velo _velo_vy_mv;
    /** [r/w]Y�������ړ����x��� */
    velo _top_velo_vy_mv;
    /** [r/w]Y�������ړ����x���� */
    velo _bottom_velo_vy_mv;
    /** [r/w]Y�������ړ������x */
    acce _acce_vy_mv;
    /** [r/w]Y�������ړ������x���*/
    acce _top_acce_vy_mv;
    /** [r/w]Y�������ړ������x����*/
    acce _bottom_acce_vy_mv;
    /** [r/w]Z�������ړ����x */
    velo _velo_vz_mv;
    /** [r/w]Z�������ړ����x��� */
    velo _top_velo_vz_mv;
    /** [r/w]Z�������ړ����x���� */
    velo _bottom_velo_vz_mv;
    /** [r/w]Z�������ړ������x */
    acce _acce_vz_mv;
    /** [r/w]Z�������ړ������x���*/
    acce _top_acce_vz_mv;
    /** [r/w]Z�������ړ������x����*/
    acce _bottom_acce_vz_mv;

    coord _grv_mv_target_x;
    coord _grv_mv_target_y;
    coord _grv_mv_target_z;
    const GeometricActor* _grv_mv_pActor_target;
    velo _grv_mv_max_velo;
    acce _grv_mv_acce;
    coord _grv_mv_stop_renge;
    bool _grv_mv_flg;
    /** [r]���Ă̏���A */
    GeoDriverAssistantA* _pAsstMv;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  ���Ăɏ��Actor
     */
    explicit GeoDriver(GeometricActor* prm_pActor);

    /**
     * ���Ă̏���(���炩�ړ��S��)���擾 .
     * @return ���Ă̏���
     */
    GeoDriverAssistantA* asst();

    int dot(int prm_vX, int prm_vY, int prm_vZ);
    /**
     * X�������ړ����x�ݒ� .
     * @param prm_velo_vx_mv X�������ړ����x
     */
    void setVxMvVelo(velo prm_velo_vx_mv);

    /**
     * X�������ړ����x���Z .
     * @param prm_velo_vx_mv X�������ړ����x����
     */
    void addVxMvVelo(velo prm_velo_vx_mv);

    /**
     * X�������ړ����x�̏������������ .
     * @param prm_velo_vx_mv01 ���x�P
     * @param prm_velo_vx_mv02 ���x�Q
     */
    void forceVxMvVeloRange(velo prm_velo_vx_mv01, velo prm_velo_vx_mv02);

    /**
     * X�������ړ������x�ݒ� .
     * @param prm_acce_vx_mv X�������ړ������x
     */
    void setVxMvAcce(acce prm_acce_vx_mv);

    /**
     * X�������ړ������x���Z .
     * @param prm_acce_vx_mv X�������ړ������x����
     */
    void addVxMvAcce(acce prm_acce_vx_mv);

    /**
     * X�������ړ������x�̏������������ .
     * @param prm_acce_vx_mv01 �����x�P
     * @param prm_acce_vx_mv02 �����x�Q
     */
    void forceVxMvAcceRange(acce prm_acce_vx_mv01, acce prm_acce_vx_mv02);

    /**
     * Y�������ړ����x�ݒ� .
     * @param prm_velo_vy_mv Y�������ړ����x
     */
    void setVyMvVelo(velo prm_velo_vy_mv);

    /**
     * Y�������ړ����x���Z .
     * @param prm_velo_vy_mv Y�������ړ����x����
     */
    void addVyMvVelo(velo prm_velo_vy_mv);

    /**
     * Y�������ړ����x�̏������������ .
     * @param prm_velo_vy_mv01 ���x�P
     * @param prm_velo_vy_mv02 ���x�Q
     */
    void forceVyMvVeloRange(velo prm_velo_vy_mv01, velo prm_velo_vy_mv02);

    /**
     * Y�������ړ������x�ݒ� .
     * @param prm_acce_vy_mv Y�������ړ������x
     */
    void setVyMvAcce(acce prm_acce_vy_mv);

    /**
     * Y�������ړ������x���Z .
     * @param prm_acce_vy_mv Y�������ړ������x����
     */
    void addVyMvAcce(acce prm_acce_vy_mv);

    /**
     * Y�������ړ������x�̏������������ .
     * @param prm_acce_vy_mv01 �����x�P
     * @param prm_acce_vy_mv02 �����x�Q
     */
    void forceVyMvAcceRange(acce prm_acce_vy_mv01, acce prm_acce_vy_mv02);

    /**
     * Z�������ړ����x�ݒ� .
     * @param prm_velo_vz_mv Z�������ړ����x
     */
    void setVzMvVelo(velo prm_velo_vz_mv);

    /**
     * Z�������ړ����x���Z .
     * @param prm_velo_vz_mv Z�������ړ����x����
     */
    void addVzMvVelo(velo prm_velo_vz_mv);

    /**
     * Z�������ړ����x�̏������������ .
     * @param prm_velo_vz_mv01 ���x�P
     * @param prm_velo_vz_mv02 ���x�Q
     */
    void forceVzMvVeloRange(velo prm_velo_vz_mv01, velo prm_velo_vz_mv02);

    /**
     * Z�������ړ������x�ݒ� .
     * @param prm_acce_vz_mv Z�������ړ������x
     */
    void setVzMvAcce(acce prm_acce_vz_mv);

    /**
     * Z�������ړ������x���Z .
     * @param prm_acce_vz_mv Z�������ړ������x����
     */
    void addVzMvAcce(acce prm_acce_vz_mv);

    /**
     * Z�������ړ������x�̏������������ .
     * @param prm_acce_vz_mv01 �����x�P
     * @param prm_acce_vz_mv02 �����x�Q
     */
    void forceVzMvAcceRange(acce prm_acce_vz_mv01, acce prm_acce_vz_mv02);

    /**
     * X��Y��Z�������̈ړ����x�̏������������ .
     * @param prm_velo_vxyz_mv01 ���x1
     * @param prm_velo_vxyz_mv02 ���x2
     */
    void forceVxyzMvVeloRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02);

    /**
     * X��Y��Z�������̈ړ������x�̏������������ .
     * @param prm_acce_vxyz_mv01 �����x�P
     * @param prm_acce_vxyz_mv02 �����x�Q
     */
    void forceVxyzMvAcceRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02);

    /**
     * X��Y��Z�������̈ړ����x��ݒ肷��B
     * @param prm_velo_vx_mv X�������ړ����x
     * @param prm_velo_vy_mv Y�������ړ����x
     * @param prm_velo_vz_mv Z�������ړ����x
     */
    void setVxyzMvVelo(velo prm_velo_vx_mv, velo prm_velo_vy_mv, velo prm_velo_vz_mv);

    /**
     * X��Y��Z�������̈ړ����x��ڕW�p�x�ƈړ����x�Őݒ肷��B
     * @param prm_rz �ڕWZ����]�A���O���l
     * @param prm_ry �ڕWY����]�A���O���l
     * @param prm_velo �ړ����x
     */
    void setVxyzMvVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    /**
     * X��Y��Z�������̈ړ����x��ڕW���W�ƈړ����x�Őݒ肷��B
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_velo �ړ����x
     */
    void setVxyzMvVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    /**
     * X��Y��Z�������̈ړ����x��ڕW�A�N�^�[�ƈړ����x�Őݒ肷��B
     * @param prm_pTargetActor �ڕW�A�N�^�[
     * @param prm_velo �ړ����x
     */
    void setVxyzMvVeloTwd(const GeometricActor* prm_pTargetActor, velo prm_velo) {
        setVxyzMvVeloTwd(prm_pTargetActor->_x, prm_pTargetActor->_y, prm_pTargetActor->_z, prm_velo);
    }

    /**
     * X��Y��Z�������̈ړ������x��ݒ肷��B
     * @param prm_acce_vx_mv X�������ړ������x
     * @param prm_acce_vy_mv Y�������ړ������x
     * @param prm_acce_vz_mv Z�������ړ������x
     */
    void setVxyzMvAcce(acce prm_acce_vx_mv, acce prm_acce_vy_mv, acce prm_acce_vz_mv);



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
    coord setVxAcceByT(frame prm_target_frames, velo prm_target_velo);
    coord setVyAcceByT(frame prm_target_frames, velo prm_target_velo);
    coord setVzAcceByT(frame prm_target_frames, velo prm_target_velo);
    void setVxyzAcceByT(frame prm_target_frames, velo prm_target_velo) {
        setVxAcceByT(prm_target_frames, prm_target_velo);
        setVyAcceByT(prm_target_frames, prm_target_velo);
        setVzAcceByT(prm_target_frames, prm_target_velo);
    }


    /**
     * X��Y��Z�������̈ړ����x�� 0 �ɐݒ肷��B
     */
    void setZeroVxyzMvVelo() {
        _velo_vx_mv = _velo_vy_mv = _velo_vz_mv = 0;
    }

    /**
     * X��Y��Z�������̈ړ������x�� 0 �ɐݒ肷��B
     */
    void setZeroVxyzMvAcce() {
        _acce_vx_mv = _acce_vy_mv = _acce_vz_mv = 0;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̂���߂� .
     */
    void stopGravitationMvSequence() {
        _grv_mv_flg = false;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̍Œ����ǂ���
     * @return true:�Œ�/false:�����łȂ�
     */
    bool isGravitationMvSequence() {
        return _grv_mv_flg;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̂����s .
     * �y�A���S���Y���T�v�z<BR>
     * X,Y,Z�̊e���̍��W���ꂼ��ɁA�ڕW�̍��W�ƃA�N�^�[�̍��W���������A<BR>
     * ���̐����ɂ��A�����x�����Z���Z�����ĖڕW�ɋ߂Â����Ƃ��܂��B<BR>
     * �A���A���̂܂܂ł���ƁA�q�������񂷂邪�@���A�i���ɖڕW�̍��W�ɓ��B���܂���B<BR>
     * �����ŁA�ڕW�̍��WX,Y,Z�̊e���ƁA�A�N�^�[�̍��W����<BR>
     * -1*prm_stop_renge �` prm_stop_renge<BR>
     * �͈͓̔��ɂȂ����ꍇ�A���x���ɘa(����)���A�ڕW�̍��W�ɍX�ɋ߂Â������܂��B<BR>
     * �e�����ꂼ��A�ڕW�ɋ߂Â��Ǝ����x��0�ɋ߂Â��A�Ƃ�����ŏd�͂Ƃ͕����I�ɓ������قȂ�܂��B<BR>
     * �ł��A�d�͂ň����t���邩�̂悤�Ȍ��ʂ����ҏo���܂��B<BR>
     * ���w�I�ɂ́A�ڕW�̍��W�Ɍ���Ȃ��߂Â������ŁA�ڕW���W�ƈ�v���邱�Ƃ͂���܂���B<BR>
     * @param prm_tx �����񂹂��ē��B����ڕW��X���W(��΍��W)
     * @param prm_ty �����񂹂��ē��B����ڕW��Y���W(��΍��W)
     * @param prm_tz �����񂹂��ē��B����ڕW��Z���W(��΍��W)
     * @param prm_max_velo �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ����x����l
     * @param prm_acce �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ������x����l
     * @param prm_stop_renge ���x���}������ڕW���W����̊e���̋���
     */
    void execGravitationMvSequenceTwd(coord prm_tx, coord prm_ty, coord prm_tz,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̖ڕW���W���X�V�ݒ� .
     * @param prm_tx �����񂹂��ē��B����ڕW��X���W
     * @param prm_ty �����񂹂��ē��B����ڕW��Y���W
     * @param prm_tz �����񂹂��ē��B����ڕW��Z���W
     */
    void setGravitationTwd(coord prm_tx, coord prm_ty, coord prm_tz) {
        _grv_mv_target_x = prm_tx;
        _grv_mv_target_y = prm_ty;
        _grv_mv_target_z = prm_tz;
        _grv_mv_pActor_target = nullptr;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̂����s .
     * �����́A
     * execGravitationMvSequenceTwd(coord,coord,coord,velo,acce,int)
     * ���Q�ƁB
     * @param prm_pActor_target �����񂹂��ē��B����ڕW���W�ƂȂ�A�N�^�[
     * @param prm_max_velo �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ����x����l
     * @param prm_acce �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ������x����l
     * @param prm_stop_renge ���x���}������ڕW���W����̊e���̋���
     */
    void execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);
    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̂����s .
     * �����́A
     * execGravitationMvSequenceTwd(coord,coord,coord,velo,acce,int)
     * ���Q�ƁB
     * @param prm_pActor_target �����񂹂��ē��B����ڕW���W�ƂȂ�A�N�^�[
     * @param prm_local_offset_tx �ڕWX���W�ʒu�̕␳�Bprm_pActor_target����̑��΍��W��ݒ肷��B
     * @param prm_local_offset_ty �ڕWY���W�ʒu�̕␳�Bprm_pActor_target����̑��΍��W��ݒ肷��B
     * @param prm_local_offset_tz �ڕWZ���W�ʒu�̕␳�Bprm_pActor_target����̑��΍��W��ݒ肷��B
     * @param prm_max_velo �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ����x����l
     * @param prm_acce �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ������x����l
     * @param prm_stop_renge ���x���}������ڕW���W����̊e���̋���
     */
    void execGravitationMvSequenceTwd(const GeometricActor* prm_pActor_target,
                                      coord prm_local_offset_tx, coord prm_local_offset_ty, coord prm_local_offset_tz,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);


    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̖ڕW���W���X�V�ݒ� .
     * @param prm_pActor_target �����񂹂��ē��B����ڕW���W�ƂȂ�A�N�^�[
     */
    void setGravitationTwd(const GeometricActor* prm_pActor_target) {
        _grv_mv_target_x = 0;
        _grv_mv_target_y = 0;
        _grv_mv_target_z = 0;
        _grv_mv_pActor_target = prm_pActor_target;
    }

    /**
     * ����(���s�ړ��x��)�̎d�������p�� .
     * ���� GeoDriver �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pAxsMver ���p��
     */
    void takeoverMvFrom(GeoDriver* const prm_pAxsMver);

    /**
     * GeoDriver�ɂ��A�N�^�[�ړ����~����B
     */
    void stopMv();

    /**
     * ���x�A�����x�����Z�b�g�A�e��������������ݒ�B
     */
    void resetMv();

    /**
     * ����(���s�ړ��x��)���U�镑�� .
     * ����(���s�ړ��x��)�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɉ���(���s�ړ��x��)��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GeoDriver();
};

}
#endif /*GGAF_DX_GEODRIVER_H_*/

