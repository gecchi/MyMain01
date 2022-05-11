#ifndef GGAF_DX_AXISVEHICLE_H_
#define GGAF_DX_AXISVEHICLE_H_
#include "GgafDxCommonHeader.h"
#include "ActorVehicle.h"

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
class AxisVehicle : public ActorVehicle {

public:
    /** [r]�ΏۃA�N�^�[ */
    //GeometricActor* const _pActor;
    /** [r/w]X�������ړ����x */
    velo _velo_x;
    /** [r/w]X�������ړ����x��� */
    velo _top_velo_x;
    /** [r/w]X�������ړ����x���� */
    velo _bottom_velo_x;
    /** [r/w]X�������ړ������x */
    acce _acce_x;
    /** [r/w]X�������ړ������x���*/
    acce _top_acce_x;
    /** [r/w]X�������ړ������x����*/
    acce _bottom_acce_x;
    /** [r/w]Y�������ړ����x */
    velo _velo_y;
    /** [r/w]Y�������ړ����x��� */
    velo _top_velo_y;
    /** [r/w]Y�������ړ����x���� */
    velo _bottom_velo_y;
    /** [r/w]Y�������ړ������x */
    acce _acce_y;
    /** [r/w]Y�������ړ������x���*/
    acce _top_acce_y;
    /** [r/w]Y�������ړ������x����*/
    acce _bottom_acce_y;
    /** [r/w]Z�������ړ����x */
    velo _velo_z;
    /** [r/w]Z�������ړ����x��� */
    velo _top_velo_z;
    /** [r/w]Z�������ړ����x���� */
    velo _bottom_velo_z;
    /** [r/w]Z�������ړ������x */
    acce _acce_z;
    /** [r/w]Z�������ړ������x���*/
    acce _top_acce_z;
    /** [r/w]Z�������ړ������x����*/
    acce _bottom_acce_z;

    coord _grv_mv_target_x;
    coord _grv_mv_target_y;
    coord _grv_mv_target_z;
    const GeometricActor* _grv_mv_pActor_target;
    velo _grv_mv_max_velo;
    acce _grv_mv_acce;
    coord _grv_mv_stop_renge;
    bool _grv_mv_flg;
    /** [r]���Ă̏���A */
    AxisVehicleAssistantA* _pAsstMv;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  ���Ăɏ��Actor
     */
    explicit AxisVehicle(GeometricActor* prm_pActor);

    /**
     * ���Ă̏���(���炩�ړ��S��)���擾 .
     * @return ���Ă̏���
     */
    AxisVehicleAssistantA* asst();

    int dot(int prm_vX, int prm_vY, int prm_vZ);

    /**
     * X�������ړ����x�ݒ� .
     * @param prm_velo_x X�������ړ����x
     */
    void setVeloX(velo prm_velo_x);

    /**
     * X�������ړ����x���Z .
     * @param prm_velo_x X�������ړ����x����
     */
    void addVeloX(velo prm_velo_x);

    /**
     * X�������ړ����x�̏������������ .
     * @param prm_velo_x01 ���x�P
     * @param prm_velo_x02 ���x�Q
     */
    void forceVeloXRange(velo prm_velo_x01, velo prm_velo_x02);

    /**
     * X�������ړ������x�ݒ� .
     * @param prm_acce_x X�������ړ������x
     */
    void setAcceX(acce prm_acce_x);

    /**
     * X�������ړ������x���Z .
     * @param prm_acce_x X�������ړ������x����
     */
    void addAcceX(acce prm_acce_x);

    /**
     * X�������ړ������x�̏������������ .
     * @param prm_acce_x01 �����x�P
     * @param prm_acce_x02 �����x�Q
     */
    void forceAcceXRange(acce prm_acce_x01, acce prm_acce_x02);

    /**
     * Y�������ړ����x�ݒ� .
     * @param prm_velo_y Y�������ړ����x
     */
    void setVeloY(velo prm_velo_y);

    /**
     * Y�������ړ����x���Z .
     * @param prm_velo_y Y�������ړ����x����
     */
    void addVeloY(velo prm_velo_y);

    /**
     * Y�������ړ����x�̏������������ .
     * @param prm_velo_y01 ���x�P
     * @param prm_velo_y02 ���x�Q
     */
    void forceVeloYRange(velo prm_velo_y01, velo prm_velo_y02);

    /**
     * Y�������ړ������x�ݒ� .
     * @param prm_acce_y Y�������ړ������x
     */
    void setAcceY(acce prm_acce_y);

    /**
     * Y�������ړ������x���Z .
     * @param prm_acce_y Y�������ړ������x����
     */
    void addAcceY(acce prm_acce_y);

    /**
     * Y�������ړ������x�̏������������ .
     * @param prm_acce_y01 �����x�P
     * @param prm_acce_y02 �����x�Q
     */
    void forceAcceYRange(acce prm_acce_y01, acce prm_acce_y02);

    /**
     * Z�������ړ����x�ݒ� .
     * @param prm_velo_z Z�������ړ����x
     */
    void setVeloZ(velo prm_velo_z);

    /**
     * Z�������ړ����x���Z .
     * @param prm_velo_z Z�������ړ����x����
     */
    void addVeloZ(velo prm_velo_z);

    /**
     * Z�������ړ����x�̏������������ .
     * @param prm_velo_z01 ���x�P
     * @param prm_velo_z02 ���x�Q
     */
    void forceVeloZRange(velo prm_velo_z01, velo prm_velo_z02);

    /**
     * Z�������ړ������x�ݒ� .
     * @param prm_acce_z Z�������ړ������x
     */
    void setAcceZ(acce prm_acce_z);

    /**
     * Z�������ړ������x���Z .
     * @param prm_acce_z Z�������ړ������x����
     */
    void addAcceZ(acce prm_acce_z);

    /**
     * Z�������ړ������x�̏������������ .
     * @param prm_acce_z01 �����x�P
     * @param prm_acce_z02 �����x�Q
     */
    void forceAcceZRange(acce prm_acce_z01, acce prm_acce_z02);

    /**
     * X��Y��Z�������̈ړ����x�̏������������ .
     * @param prm_velo_vxyz_mv01 ���x1
     * @param prm_velo_vxyz_mv02 ���x2
     */
    void forceVeloXYZRange(velo prm_velo_vxyz_mv01, velo prm_velo_vxyz_mv02);

    /**
     * X��Y��Z�������̈ړ������x�̏������������ .
     * @param prm_acce_vxyz_mv01 �����x�P
     * @param prm_acce_vxyz_mv02 �����x�Q
     */
    void forceAcceXYZRange(acce prm_acce_vxyz_mv01, acce prm_acce_vxyz_mv02);

    /**
     * X��Y��Z�������̈ړ����x��ݒ肷��B
     * @param prm_velo_x X�������ړ����x
     * @param prm_velo_y Y�������ړ����x
     * @param prm_velo_z Z�������ړ����x
     */
    void setVeloXYZ(velo prm_velo_x, velo prm_velo_y, velo prm_velo_z);

    /**
     * X��Y��Z�������̈ړ����x��ڕW�p�x�ƈړ����x�Őݒ肷��B
     * @param prm_rz �ڕWZ����]�A���O���l
     * @param prm_ry �ڕWY����]�A���O���l
     * @param prm_velo �ړ����x
     */
    void setVeloXYZTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    /**
     * X��Y��Z�������̈ړ����x��ڕW���W�ƈړ����x�Őݒ肷��B
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_velo �ړ����x
     */
    void setVeloXYZTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    /**
     * X��Y��Z�������̈ړ����x��ڕW�A�N�^�[�ƈړ����x�Őݒ肷��B
     * @param prm_pTargetActor �ڕW�A�N�^�[
     * @param prm_velo �ړ����x
     */
    void setVeloXYZTwd(const GeometricActor* prm_pTargetActor, velo prm_velo) {
        setVeloXYZTwd(prm_pTargetActor->_x, prm_pTargetActor->_y, prm_pTargetActor->_z, prm_velo);
    }

    /**
     * X��Y��Z�������̈ړ������x��ݒ肷��B
     * @param prm_acce_x X�������ړ������x
     * @param prm_acce_y Y�������ړ������x
     * @param prm_acce_z Z�������ړ������x
     */
    void setAcceXYZ(acce prm_acce_x, acce prm_acce_y, acce prm_acce_z);

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
    coord setAcceXByT(frame prm_target_frames, velo prm_target_velo);
    coord setAcceYByT(frame prm_target_frames, velo prm_target_velo);
    coord setAcceZByT(frame prm_target_frames, velo prm_target_velo);
    void setAcceXYZByT(frame prm_target_frames, velo prm_target_velo) {
        setAcceXByT(prm_target_frames, prm_target_velo);
        setAcceYByT(prm_target_frames, prm_target_velo);
        setAcceZByT(prm_target_frames, prm_target_velo);
    }


    /**
     * X��Y��Z�������̈ړ����x�� 0 �ɐݒ肷��B
     */
    void setXYZZero() {
        _velo_x = _velo_y = _velo_z = 0;
    }

    /**
     * X��Y��Z�������̈ړ������x�� 0 �ɐݒ肷��B
     */
    void setAcceXYZZero() {
        _acce_x = _acce_y = _acce_z = 0;
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
     * ���� AxisVehicle �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pAxsMver ���p��
     */
    void takeoverFrom(AxisVehicle* const prm_pAxsMver);

    /**
     * AxisVehicle�ɂ��A�N�^�[�ړ����~����B
     */
    void stop();

    /**
     * ���x�A�����x�����Z�b�g�A�e��������������ݒ�B
     */
    void reset();

    /**
     * ����(���s�ړ��x��)���U�镑�� .
     * ����(���s�ړ��x��)�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɉ���(���s�ړ��x��)��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~AxisVehicle();
};

}
#endif /*GGAF_DX_AXISVEHICLE_H_*/

