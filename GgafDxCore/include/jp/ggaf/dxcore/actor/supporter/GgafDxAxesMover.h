#ifndef GGAFDXCORE_GGAFDXAXESMOVER_H_
#define GGAFDXCORE_GGAFDXAXESMOVER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * ���s�ړ��x�� .
 * GgafDxGeometricActor �̃����o��<BR>
 *  _x, _y, _z  �E�E�E �A�N�^�[�̍��W<BR>
 * ���A�e�������ɊȒP�ɑ��삷�邽�߂ɍ쐬�B<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxAxesMover : public GgafCore::GgafObject {

public:
    /** [r]�ΏۃA�N�^�[ */
    GgafDxGeometricActor* const _pActor;
    /** [r/w]X�������ړ����x */
    velo _veloVxMv;
    /** [r/w]X�������ړ����x��� */
    velo _veloTopVxMv;
    /** [r/w]X�������ړ����x���� */
    velo _veloBottomVxMv;
    /** [r/w]X�������ړ������x */
    acce _acceVxMv;
    /** [r/w]X�������ړ������x���*/
    acce _acceTopVxMv;
    /** [r/w]X�������ړ������x����*/
    acce _acceBottomVxMv;
    /** [r/w]Y�������ړ����x */
    velo _veloVyMv;
    /** [r/w]Y�������ړ����x��� */
    velo _veloTopVyMv;
    /** [r/w]Y�������ړ����x���� */
    velo _veloBottomVyMv;
    /** [r/w]Y�������ړ������x */
    acce _acceVyMv;
    /** [r/w]Y�������ړ������x���*/
    acce _acceTopVyMv;
    /** [r/w]Y�������ړ������x����*/
    acce _acceBottomVyMv;
    /** [r/w]Z�������ړ����x */
    velo _veloVzMv;
    /** [r/w]Z�������ړ����x��� */
    velo _veloTopVzMv;
    /** [r/w]Z�������ړ����x���� */
    velo _veloBottomVzMv;
    /** [r/w]Z�������ړ������x */
    acce _acceVzMv;
    /** [r/w]Z�������ړ������x���*/
    acce _acceTopVzMv;
    /** [r/w]Z�������ړ������x����*/
    acce _acceBottomVzMv;

    coord _grv_mv_target_x;
    coord _grv_mv_target_y;
    coord _grv_mv_target_z;
    GgafDxGeometricActor* _grv_mv_pActor_target;
    velo _grv_mv_max_velo;
    acce _grv_mv_acce;
    coord _grv_mv_stop_renge;
    bool _grv_mv_flg;
    /** [r]����B�̏���A */
    GgafDxAxesMoverAssistantA* _pHlprA;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDxAxesMover(GgafDxGeometricActor* prm_pActor);

    /**
     * ����B�̏���(���炩�ړ��S��)���擾 .
     * @return ����B�̏���
     */
    GgafDxAxesMoverAssistantA* asst();

    int dot(int prm_vX, int prm_vY, int prm_vZ);
    /**
     * X�������ړ����x�ݒ� .
     * @param prm_veloVxMv X�������ړ����x
     */
    void setVxMvVelo(velo prm_veloVxMv);

    /**
     * X�������ړ����x���Z .
     * @param prm_veloVxMv X�������ړ����x����
     */
    void addVxMvVelo(velo prm_veloVxMv);

    /**
     * X�������ړ����x�̏������������ .
     * @param prm_veloVxMv01 ���x�P
     * @param prm_veloVxMv02 ���x�Q
     */
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);

    /**
     * X�������ړ������x�ݒ� .
     * @param prm_acceVxMv X�������ړ������x
     */
    void setVxMvAcce(acce prm_acceVxMv);

    /**
     * X�������ړ������x���Z .
     * @param prm_acceVxMv X�������ړ������x����
     */
    void addVxMvAcce(acce prm_acceVxMv);

    /**
     * X�������ړ������x�̏������������ .
     * @param prm_acceVxMv01 �����x�P
     * @param prm_acceVxMv02 �����x�Q
     */
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);

    /**
     * Y�������ړ����x�ݒ� .
     * @param prm_veloVyMv Y�������ړ����x
     */
    void setVyMvVelo(velo prm_veloVyMv);

    /**
     * Y�������ړ����x���Z .
     * @param prm_veloVyMv Y�������ړ����x����
     */
    void addVyMvVelo(velo prm_veloVyMv);

    /**
     * Y�������ړ����x�̏������������ .
     * @param prm_veloVyMv01 ���x�P
     * @param prm_veloVyMv02 ���x�Q
     */
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);

    /**
     * Y�������ړ������x�ݒ� .
     * @param prm_acceVyMv Y�������ړ������x
     */
    void setVyMvAcce(acce prm_acceVyMv);

    /**
     * Y�������ړ������x���Z .
     * @param prm_acceVyMv Y�������ړ������x����
     */
    void addVyMvAcce(acce prm_acceVyMv);

    /**
     * Y�������ړ������x�̏������������ .
     * @param prm_acceVyMv01 �����x�P
     * @param prm_acceVyMv02 �����x�Q
     */
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);

    /**
     * Z�������ړ����x�ݒ� .
     * @param prm_veloVzMv Z�������ړ����x
     */
    void setVzMvVelo(velo prm_veloVzMv);

    /**
     * Z�������ړ����x���Z .
     * @param prm_veloVzMv Z�������ړ����x����
     */
    void addVzMvVelo(velo prm_veloVzMv);

    /**
     * Z�������ړ����x�̏������������ .
     * @param prm_veloVzMv01 ���x�P
     * @param prm_veloVzMv02 ���x�Q
     */
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);

    /**
     * Z�������ړ������x�ݒ� .
     * @param prm_acceVzMv Z�������ړ������x
     */
    void setVzMvAcce(acce prm_acceVzMv);

    /**
     * Z�������ړ������x���Z .
     * @param prm_acceVzMv Z�������ړ������x����
     */
    void addVzMvAcce(acce prm_acceVzMv);

    /**
     * Z�������ړ������x�̏������������ .
     * @param prm_acceVzMv01 �����x�P
     * @param prm_acceVzMv02 �����x�Q
     */
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    /**
     * X��Y��Z�������̈ړ����x�̏������������ .
     * @param prm_veloVxyzMv01 ���x1
     * @param prm_veloVxyzMv02 ���x2
     */
    void forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02);

    /**
     * X��Y��Z�������̈ړ������x�̏������������ .
     * @param prm_acceVxyzMv01 �����x�P
     * @param prm_acceVxyzMv02 �����x�Q
     */
    void forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02);

    /**
     * X��Y��Z�������̈ړ����x��ݒ肷��B
     * @param prm_veloVxMv X�������ړ����x
     * @param prm_veloVyMv Y�������ړ����x
     * @param prm_veloVzMv Z�������ړ����x
     */
    void setVxyzMvVelo(velo prm_veloVxMv, velo prm_veloVyMv, velo prm_veloVzMv);

    /**
     * X��Y��Z�������̈ړ������x��ݒ肷��B
     * @param prm_acceVxMv X�������ړ������x
     * @param prm_acceVyMv Y�������ړ������x
     * @param prm_acceVzMv Z�������ړ������x
     */
    void setVxyzMvAcce(acce prm_acceVxMv, acce prm_acceVyMv, acce prm_acceVzMv);



    /**
     * �ړ������x���A�u�ڕW���B���x�v�u��₷���ԁv�ɂ��ݒ� .
     * <pre><code>
     *
     *    ���x(v)
     *     ^        a:�����x�i_accMv �ɐݒ肳���)
     *     |        D:�ړ����� �i�߂�l�j
     *     |       V0:�����_�̑��x�i= ���݂� _veloMv ���g�p�����j
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
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    /**
     * X��Y��Z�������̈ړ������x�� 0 �ɐݒ肷��B
     */
    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
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
     * @param prm_tx �����񂹂��ē��B����ڕW��X���W
     * @param prm_ty �����񂹂��ē��B����ڕW��Y���W
     * @param prm_tz �����񂹂��ē��B����ڕW��Z���W
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
    void execGravitationMvSequenceTwd(GgafDxGeometricActor* prm_pActor_target,
                                      velo prm_max_velo,
                                      acce prm_acce,
                                      coord prm_stop_renge);

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ������ۂ��̖ڕW���W���X�V�ݒ� .
     * @param prm_pActor_target �����񂹂��ē��B����ڕW���W�ƂȂ�A�N�^�[
     */
    void setGravitationTwd(GgafDxGeometricActor* prm_pActor_target) {
        _grv_mv_target_x = 0;
        _grv_mv_target_y = 0;
        _grv_mv_target_z = 0;
        _grv_mv_pActor_target = prm_pActor_target;
    }

    /**
     * ���s�ړ��x���̎d�������p�� .
     * ���� GgafDxAxesMover �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prmpAxsMver_ ���p��
     */
    void takeoverMvFrom(GgafDxAxesMover* const prmpAxsMver_);

    /**
     * GgafDxAxesMover�ɂ��A�N�^�[�ړ����~����B
     */
    void stopMv();

    /**
     * ���x�A�����x�����Z�b�g�A�e��������������ݒ�B
     */
    void resetMv();

    /**
     * ���s�ړ��x�����U�镑�� .
     * ���s�ړ��x���@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɕ��s�ړ��x����K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GgafDxAxesMover();
};

}
#endif /*GGAFDXCORE_GGAFDXAXESMOVER_H_*/

