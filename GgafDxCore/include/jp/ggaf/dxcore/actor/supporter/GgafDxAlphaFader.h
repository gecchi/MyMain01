#ifndef GGAFDXALPHAFADER_H_
#define GGAFDXALPHAFADER_H_
namespace GgafDxCore {


/**
 * �t�F�[�f�B���O�x���N���X .
 * GgafDxDrawableActor �̃����o��
 * _fAlpha(�A�N�^�[�̃����x)���Ȃ߂炩�ɕω������A<BR>
 * �t�F�[�f�B���O���s�����Ƃ���ȖړI<BR>
 * @version 1.00
 * @since 2010/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaFader : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxDrawableActor* _pActor;

    /** ���̋��x(0:�����`1.0:�s����) */
    float _alpha;
    /** ���̖ڕW�̋��x */
    float _target_alpha;
    /** ���̋��x��� */
    float _top_alpha;
    /** ���̋��x���� */
    float _bottom_alpha;
    /** ���̖��t���[���̋��x�̑��� */
    float _velo_alpha;
    /** ���̖��t���[���̋��x�̑����̑��� */
    float _acce_alpha;
    /** ���̃��[�v�J�E���g�i2�Ŋg��k�������Z�b�g�A1�Ȃ�Ίg��or�k���̕Г��j */
    int _one_way_cnt;
    /** ���̃X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num;
    /** ���̃t�F�[�f�B���O���@ */
    GgafDxAlphaFadingMethod _method;

    /** �r�[�g���A���̎O�p�g�̔g�`�Ńt�F�[�f�B���O�̃A�^�b�N�t���[���� */
    frame _beat_attack_frames;
    /** �r�[�g���A���̎O�p�g�̔g�`�Ńt�F�[�f�B���O�̃��X�g�t���[���� */
    frame _beat_rest_frames;
    frame _beat_duration_frames;
    /** �r�[�g���A���̃t�F�[�f�B���O�ɔ�₷�t���[���� */
    frame _beat_target_frames;
    /** �r�[�g���A���̃A�^�b�N���牺���܂ł̃t���[���� */
    frame _beat_down_frames;
    /** �r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count;
    /** �r�[�g���A�����i���ԍ� */
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
    void addAlpha(float prm_alpha_diff) {
        addAlpha(prm_alpha_diff);
    }


    /**
     * ���x���Ύw��
     * @param prm_c �F�v�f
     * @param prm_alpha ���x�l
     */
    void setAlpha(float prm_alpha) {
        //_TRACE_("setAlpha ["<<prm_c<<"]prm_alpha="<<prm_alpha);
        //_TRACE_("setAlpha _bottom_alpha["<<prm_c<<"]="<<_bottom_alpha<<"/_top_alpha["<<prm_c<<"]="<<_top_alpha<<"");
        if (_top_alpha < prm_alpha) {
            _alpha = _top_alpha;
        } else if (_bottom_alpha > prm_alpha) {
            _alpha = _bottom_alpha;
        } else {
            _alpha = prm_alpha;
        }
        //_TRACE_("setAlpha _alpha ["<<prm_c<<"] _alpha="<<prm_alpha);
    }
    /**
     * ���x�̏��������ݒ�
     * @param prm_alpha1 ���x�l1
     * @param prm_alpha2 ���x�l2
     */
    void forceAlphaRange(float prm_alpha1, float prm_alpha2) {
        if (prm_alpha1 < prm_alpha2) {
            _bottom_alpha = prm_alpha1;
            _top_alpha = prm_alpha2;
        } else {
            _bottom_alpha = prm_alpha2;
            _top_alpha = prm_alpha1;
        }
        //_TRACE_("forceAlphaRange _bottom_alpha["<<prm_c<<"]="<<_bottom_alpha<<"/_top_alpha["<<prm_c<<"]="<<_top_alpha<<"");
    }
    /**
     * ���x�����Z�b�g
     * �{�I�u�W�F�N�g(GgafDxAlphaFader)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     * @param prm_c �F�v�f
     */
    void setAlphaToBottom() {
        _alpha = _bottom_alpha;
    }

    void setAlphaToTop() {
        _alpha = _top_alpha;
    }

    /**
     * �t�F�[�f�B���O���~������B
     */
    void stopImmediately() {
        _method = NO_ALPHAFADE;
    }

    /**
     * ���݃t�F�[�f�B���O�����ǂ��� .
     * @return
     */
    bool isWorking() {
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
    void intoTargetAlphaLinerUntil(float prm_target_alpha, frame prm_spend_frame);


    /**
     * �Г������t�F�[�f�B���O�i���x���x�w��j .
     * �ڕW�̋��x�ֈ�葬�x�Ńt�F�[�f�B���O����i���x�����w��j .
     * @param prm_target_alpha �ڕW���x
     * @param prm_velo_alpha ���t���[�����Z���鋭�x����(>0.0)�B���̋��x���w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetAlphaLinerStep(float prm_target_alpha, float prm_velo_alpha);


    /**
     * �Г������t�F�[�f�B���O�i���x���x�E���x�����x�w��j .
     * �ڕW�̋��x�։����w��Ńt�F�[�f�B���O����i���x���x�A���x�����x���w��j .
     * ���x�����x��0�Ɏw�肷��� intoTargetAlphaLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetAlphaLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_target_alpha �ڕW���x
     * @param prm_velo_alpha �������x���x
     * @param prm_acce_alpha ���x�����x
     */
    void intoTargetAlphaAcceStep(float prm_target_alpha, float prm_velo_alpha, float prm_acce_alpha);


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
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P���[�v�̃t���[����<BR>
     * �A �A�^�b�N�܂ł̃t���[����<BR>
     * �B �����t���[����<BR>
     * �C �x�e�t���[����<BR>
     * �D ���x���(_top_alpha[�F�v�f] �z�񂪕ێ�)<BR>
     * �E ���x����(_bottom_alpha[�F�v�f] �z�񂪕ێ�)<BR>
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
#endif /*GGAFDXALPHAFADER_H_*/

