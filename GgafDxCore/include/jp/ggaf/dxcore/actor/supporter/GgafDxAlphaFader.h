#ifndef GGAFDXCORE_GGAFDXALPHAFADER_H_
#define GGAFDXCORE_GGAFDXALPHAFADER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �t�F�[�f�B���O�x���N���X .
 * GgafDxDrawableActor �̃����o��
 * _alpha(�A�N�^�[�̃����x)���Ȃ߂炩�ɕω������A<BR>
 * �t�F�[�f�B���O���s�����Ƃ���ȖړI<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaFader : public GgafCore::GgafObject {

public:
    /** [r]�ΏۃA�N�^�[ */
    GgafDxDrawableActor* const _pActor;

    /** [r/w]���̋��x(0:�����`1.0:�s����) */
    float _alpha;
    /** [r/w]���̖ڕW�̋��x */
    float _target_alpha;
    /** [r/w]���̋��x��� */
    float _top_alpha;
    /** [r/w]���̋��x���� */
    float _bottom_alpha;
    /** [r/w]���̖��t���[���̋��x�̑��� */
    float _velo_alpha;
    /** [r/w]���̖��t���[���̋��x�̑����̑��� */
    float _acce_alpha;
    /** [r]���̃��[�v�J�E���g�A2�łP���[�v�i1�̓A���t�@���x���偨�I��(�Г�)�A2�̓A���t�@���x����`������1���[�v�j */
    int _one_way_cnt;
    /** [r]���̃X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num;
    /** [r]���̃t�F�[�f�B���O���@ */
    GgafDxAlphaFadingMethod _method;

    /** [r]�r�[�g���A���̑�`�g�̔g�`�Ńt�F�[�f�B���O�̃A�^�b�N�t���[���� */
    frame _beat_attack_frames;
    /** [r]�r�[�g���A���̑�`�g�̔g�`�Ńt�F�[�f�B���O�̃��X�g�t���[���� */
    frame _beat_rest_frames;
    /** [r]�r�[�g���A���̑�`�g�̔g�`�ŃA�^�b�N����̎����t���[���� */
    frame _beat_duration_frames;
    /** [r]�r�[�g���A���̃t�F�[�f�B���O�ɔ�₷�t���[���� */
    frame _beat_target_frames;
    /** [r]�r�[�g���A���̃A�^�b�N���牺���܂ł̃t���[���� */
    frame _beat_down_frames;
    /** [r]�r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count;
    /** [r]�r�[�g���A�����i���ԍ� */
    int _beat_progres;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafDxAlphaFader(GgafDxDrawableActor* prm_pActor);

    /**
     * ���x�𑊑Ύw�� .
     * @param prm_alpha_diff ���x�l����
     */
    inline void addAlpha(float prm_alpha_diff) {
        setAlpha(_alpha+prm_alpha_diff);
    }

    /**
     * ���x���Ύw��
     * @param prm_alpha ���x�l
     */
    inline void setAlpha(float prm_alpha) {
        if (_top_alpha < prm_alpha) {
            _alpha = _top_alpha;
        } else if (_bottom_alpha > prm_alpha) {
            _alpha = _bottom_alpha;
        } else {
            _alpha = prm_alpha;
        }
    }

    /**
     * ���x�̏��������ݒ�
     * @param prm_alpha1 ���x�l1
     * @param prm_alpha2 ���x�l2
     */
    inline void forceRange(float prm_alpha1, float prm_alpha2) {
        if (prm_alpha1 < prm_alpha2) {
            _bottom_alpha = prm_alpha1;
            _top_alpha = prm_alpha2;
        } else {
            _bottom_alpha = prm_alpha2;
            _top_alpha = prm_alpha1;
        }
    }

    /**
     * ���x�����Z�b�g
     * �{�I�u�W�F�N�g(GgafDxAlphaFader)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     */
    inline void setToBottom() {
        _alpha = _bottom_alpha;
    }

    inline void setToTop() {
        _alpha = _top_alpha;
    }

    /**
     * �t�F�[�f�B���O���~������B
     */
    inline void stopImmed() {
        _method = NO_ALPHAFADE;
    }

    /**
     * ��Ԃ����Z�b�g���� .
     * �t�F�[�h���̏ꍇ�͒�~����B
     * ���ӁF�A���A�����A���t�@�l�͕ύX����܂���B
     */
    void reset();

    /**
     * ���݃t�F�[�f�B���O�����ǂ��� .
     * @return
     */
    inline bool isFading() {
        if (_method == NO_ALPHAFADE) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * �Г������t�F�[�f�B���O�i�����t���[�����w��j .
     * �ڕW�̋��x�ֈ�葬�x�Ńt�F�[�f�B���O����B
     * @param prm_target_alpha �ڕW���x
     * @param prm_spend_frame ��₷�t���[����
     */
    void fadeLinerUntil(float prm_target_alpha, frame prm_spend_frame);

    /**
     * �Г������t�F�[�f�B���O�i���x���x�w��j .
     * �ڕW�̋��x�ֈ�葬�x�Ńt�F�[�f�B���O����i���x�����w��j .
     * @param prm_target_alpha �ڕW���x
     * @param prm_velo_alpha ���t���[�����Z���鋭�x����(>0.0)�B���̋��x���w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void fadeLinerStep(float prm_target_alpha, float prm_velo_alpha);

    /**
     * �Г������t�F�[�f�B���O�i���x���x�E���x�����x�w��j .
     * �ڕW�̋��x�։����w��Ńt�F�[�f�B���O����i���x���x�A���x�����x���w��j .
     * ���x�����x��0�Ɏw�肷��� fadeLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * fadeLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_target_alpha �ڕW���x
     * @param prm_velo_alpha �������x���x
     * @param prm_acce_alpha ���x�����x
     */
    void fadeAcceStep(float prm_target_alpha, float prm_velo_alpha, float prm_acce_alpha);

    /**
     * ���������t�F�[�f�B���O�i�t���[�����w��j
     * �ڕW�̋��x�ֈ�葬�x�Ńt�F�[�f�B���O���A��葬�x�Ō��ɖ߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_beat_target_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * ��`�g�Ńt�F�[�f�B���O����B .
     * <PRE>
     *             ���B��
     * �D  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
     *            /      �_                     /      �_
     *           /         �_                  /         �_
     *          /            �_               /            �_
     *         /               �_            /               �_
     *        /                  �_         /                  �_
     * �E  �Q/                     �_�Q�Q�Q/                     �_�Q
     *
     *       ���A��                  ���C��
     *       ������������������ �@ ����������
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P���[�v�̃t���[����<BR>
     * �A �A�^�b�N�܂ł̃t���[����<BR>
     * �B �����t���[����<BR>
     * �C �x�e�t���[����<BR>
     * �D ���x���(_top_alpha�A�ێ����郿�̋��x���)<BR>
     * �E ���x����(_bottom_alpha�A�ێ����郿�̋��x����)<BR>
     * @param prm_beat_target_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_duration_frames ��}�ŇB�̃t���[����
     * @param prm_rest_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_duration_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     */
    virtual void behave();

    virtual ~GgafDxAlphaFader();
};

}
#endif /*GGAFDXCORE_GGAFDXALPHAFADER_H_*/

