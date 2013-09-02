#ifndef GGAFDXCORE_GGAFDXSCALER_H_
#define GGAFDXCORE_GGAFDXSCALER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �g��k���x���N���X.
 * GgafDxGeometricActor �̃����o��<BR>
 * _SX , _SY, _SZ  �E�E�E �A�N�^�[�̃X�P�[��<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �g��k��1.0�{�i�X�P�[�������j�́A�{�N���X�ł̃X�P�[���l1000�ɑ�������B
 * [���{��]     �� [�{�N���X�̃X�P�[���l]
 * ���{         �� 1000
 * 2.5�{�g��    �� 2500
 * �����̑傫�� �� 500
 * �k����80%    �� 800
 * �{�N���X�ł́A�X�P�[���ƃX�P�[�����O�Ƃ����P������̈Ӗ��Ŏg�p���Ă���ӏ�������B
 * �X�P�[���E�E�E���݁i�̃t���[���j�̊g��k����ԁA�X�P�[���l
 * �X�P�[�����O�E�E�E�t���[���Ԃ̊g��k����Ԃ̑J��
 * 2009/05/22 GgafDxKurokoA ���番�������B
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker �����ʉ�����B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxScaler : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ ����֘A //////////////////////////////////////////////
    /** [r]�ΏۃA�N�^�[ */
    GgafDxGeometricActor* _pActor;
    /** [r/w]�e���̃X�P�[��(1000 �� 1�{) */
    int _scale[3]; //[0]:X���A[1]:Y���A[2]:Z���B�ȍ~���l��  [3]�E�E�EX���AY���AZ���̈�
    /** [r/w]�e���̖ڕW�̃X�P�[�� */
    int _target_scale[3];
    /** [r/w]�e���̃X�P�[����� */
    int _top_scale[3];
    /** [r/w]�e���̃X�P�[������ */
    int _bottom_scale[3];
    /** [r/w]�e���̖��t���[���̃X�P�[���̑��� */
    int _velo_scale[3];
    /** [r/w]�e���̖��t���[���̃X�P�[���̑����̑��� */
    int _acce_scale[3];
    /** [r]�e���̃��[�v�J�E���g�i2�Ŋg��k�������Z�b�g�A1�Ȃ�Ίg��or�k���̕Г��j */
    int _one_way_cnt[3];
    /** [r]�e���̃X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num[3];
    /** [r]�e���̃X�P�[�����O���@ */
    GgafDxScalingMethod _method[3];
    /** [r]�r�[�g���A�e���̎O�p�g�̔g�`�ŃX�P�[�����O�̃A�^�b�N�t���[���� */
    frame _beat_attack_frames[3];
    /** [r]�r�[�g���A�e���̎O�p�g�̔g�`�ŃX�P�[�����O�̃��X�g�t���[���� */
    frame _beat_rest_frames[3];
    /** [r]�r�[�g���A�e���̃X�P�[�����O�ɔ�₷�t���[���� */
    frame _beat_target_frames[3];
    /** [r]�r�[�g���A�e���̃A�^�b�N���牺���܂ł̃t���[���� */
    frame _beat_down_frames[3];
    /** [r]�r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count[3];
    /** [r]�r�[�g���A�����i���ԍ� */
    int _beat_progres[3];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafDxScaler(GgafDxGeometricActor* prm_pActor);

    /**
     * �X�P�[���𑊑Ύw��i�S���w��j
     * @param prm_scale_diff �X�P�[���l����
     */
    inline void addScale(int prm_scale_diff) {
        for (int a = 0; a < 3; a++) {
            addScale((axis)a, prm_scale_diff);
        }
    }

    /**
     * �X�P�[���𑊑Ύw��i���P�ʂŎw��j
     * @param prm_axis ��
     * @param prm_scale_diff �X�P�[���l����
     */
    inline void addScale(axis prm_axis, int prm_scale_diff) {
        setScale(prm_axis, _scale[prm_axis] + prm_scale_diff);
    }

    /**
     * �X�P�[�����Ύw��i�S���w��j
     * @param prm_scale �X�P�[���l
     */
    inline void setScale(int prm_scale) {
        for (int a = 0; a < 3; a++) {
            setScale((axis)a, prm_scale);
        }
    }

    /**
     * �X�P�[�����Ύw��i���P�ʂŎw��j
     * @param prm_axis ��
     * @param prm_scale �X�P�[���l
     */
    inline void setScale(axis prm_axis, int prm_scale) {
        if (_top_scale[prm_axis] < prm_scale) {
            _scale[prm_axis] = _top_scale[prm_axis];
        } else if (_bottom_scale[prm_axis] > prm_scale) {
            _scale[prm_axis] = _bottom_scale[prm_axis];
        } else {
            _scale[prm_axis] = prm_scale;
        }
    }

    /**
     * �X�P�[���̏��������ݒ�i�S���w��j .
     * �����̑召�͋C�ɂ����n����(�����Ŏ�������)
     * @param prm_scale1 �X�P�[���l1
     * @param prm_scale2 �X�P�[���l2
     */
    void forceRange(int prm_scale1, int prm_scale2) {
        for (int a = 0; a < 3; a++) {
            forceRange((axis)a, prm_scale1, prm_scale2);
            setScale((axis)a, _scale[a]);
        }
    }

    /**
     * �X�P�[���̏��������ݒ�i���P�ʂŎw��j
     * @param prm_axis ��
     * @param prm_scale1 �X�P�[���l1
     * @param prm_scale2 �X�P�[���l2
     */
    void forceRange(axis prm_axis, int prm_scale1, int prm_scale2) {
        if (prm_scale1 < prm_scale2) {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        } else {
            _bottom_scale[prm_axis] = prm_scale2;
            _top_scale[prm_axis] = prm_scale1;
        }
    }

    /**
     * �X�P�[�������Z�b�g �i�S���w��j .
     * �{�I�u�W�F�N�g(GgafDxScaler)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     */
    void setScaleToBottom() {
        for (int a = 0; a < 3; a++) {
            setScaleToBottom((axis)a);
        }
    }

    /**
     * �X�P�[�������Z�b�g �i���P�ʂŎw��j
     * �{�I�u�W�F�N�g(GgafDxScaler)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     * @param prm_axis ��
     */
    void setScaleToBottom(axis prm_axis) {
        _scale[prm_axis] = _bottom_scale[prm_axis];
    }

    void setScaleToTop() {
        for (int a = 0; a < 3; a++) {
            setScaleToTop((axis)a);
        }
    }
    void setScaleToTop(axis prm_axis) {
        _scale[prm_axis] = _top_scale[prm_axis];
    }

    /**
     * �X�P�[�����O���~������B �i�S���w��j .
     */
    void stopImmed();

    /**
     * �X�P�[�����O���~������B �i���P�ʂŎw��j.
     * @param prm_axis
     */
    void stopImmed(axis prm_axis);

    /**
     * �Г������X�P�[�����O�i�S���E�����t���[�����w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_spend_frame ��₷�t���[����
     */
    void scaleLinerUntil(int prm_target_scale, frame prm_spend_frame);

    /**
     * ����X�P�[���֕Г������X�P�[�����O�i�S���E�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    void scaleLinerTop(frame prm_spend_frame);

    /**
     * �����X�P�[���֕Г������X�P�[�����O�i�S���E�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    void scaleLinerBottom(frame prm_spend_frame);

    /**
     * �Г������X�P�[�����O�i���P�ʁE�����t���[�����w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����B
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_spend_frame ��₷�t���[����
     */
    void scaleLinerUntil(axis prm_axis, int prm_target_scale, frame prm_spend_frame);

    /**
     * �Г������X�P�[�����O�i�S���E�X�P�[�����x�w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale ���t���[�����Z����X�P�[������(>0.0)�B���̃X�P�[�����w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void scaleLinerStep(int prm_target_scale, int prm_velo_scale);

    /**
     * �Г������X�P�[�����O�i���P�ʁE�X�P�[�����x�w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����i�X�P�[�������w��j .
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale ���t���[�����Z����X�P�[������(>0.0)�B���̃X�P�[�����w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void scaleLinerStep(axis prm_axis, int prm_target_scale, int prm_velo_scale);

    /**
     * �Г������X�P�[�����O�i�S���E�X�P�[�����x�E�X�P�[�������x�w��j .
     * �ڕW�̃X�P�[���։����w��ŃX�P�[�����O����
     * �X�P�[�������x��0�Ɏw�肷��� scaleLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * scaleLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * �X�P�[�������x�����̏ꍇ�A�ڕW�X�P�[���𒴂���ƃX�P�[�����O�I���B
     * �X�P�[�������x�����̏ꍇ�A�ڕW�X�P�[���������ƃX�P�[�����O�I���B
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale �����X�P�[�����x
     * @param prm_acce_scale �X�P�[�������x
     */
    void scaleAcceStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * �Г������X�P�[�����O�i���P�ʁE�X�P�[�����x�E�X�P�[�������x�w��j .
     * �ڕW�̃X�P�[���։����w��ŃX�P�[�����O����i�X�P�[�����x�A�X�P�[�������x���w��j .
     * �X�P�[�������x��0�Ɏw�肷��� scaleLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * scaleLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale �����X�P�[�����x
     * @param prm_acce_scale �X�P�[�������x
     */
    void scaleAcceStep(axis prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * ���������X�P�[�����O�i�S���E�t���[�����w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_beat_target_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * ���������X�P�[�����O�i���P�ʁE�t���[�����w��j
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_axis ��
     * @param prm_beat_target_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(axis prm_axis, frame prm_beat_target_frames, float prm_beat_num);

    /**
     * �O�p�g�̔g�`�ŃX�P�[�����O����B�i�S���w��j.
     * <PRE>
     * �C  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /�_                     /�_
     *           /   �_                  /   �_
     *          /      �_               /      �_
     *         /         �_            /         �_
     *        /            �_         /            �_
     * �D  �Q/               �_�Q�Q�Q/               �_�Q
     *
     *       ���A��            ���B��
     *       ���������� �@ ����������
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P���[�v�̃t���[����<BR>
     * �A �A�^�b�N�܂ł̃t���[����<BR>
     * �B �x�e�t���[����<BR>
     * �C �X�P�[�����(_top_scale[��] �z�񂪕ێ�)<BR>
     * �D �X�P�[������(_bottom_scale[��] �z�񂪕ێ�)<BR>
     * @param prm_beat_target_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_rest_frames ��}�ŇB�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * �O�p�g�̔g�`�ŃX�P�[�����O����B�i���w��j.
     * @param prm_axis ��
     * @param prm_beat_target_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_rest_frames ��}�ŇB�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(axis prm_axis,
              frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * �X�P�[�����O�����ǂ������ׂ� .
     * @param prm_axis ��
     * @return true/false
     */
    bool isScaling(axis prm_axis);

    /**
     * �X�P�[�����O�����ǂ������ׂ� .
     * @return true/false
     */
    bool isScaling();

    void reset();

    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     */
    virtual void behave();

    virtual ~GgafDxScaler();
};

}
#endif /*GGAFDXCORE_GGAFDXSCALER_H_*/

