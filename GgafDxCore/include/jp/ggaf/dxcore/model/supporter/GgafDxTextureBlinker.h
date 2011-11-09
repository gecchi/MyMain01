#ifndef GGAFDXTEXTUREBLINKER_H_
#define GGAFDXTEXTUREBLINKER_H_
namespace GgafDxCore {

/**
 * ����J���[�_�Ŏx���N���X.
 * GgafDxModel �̃����o�� _power_blink <BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �ŏI�I�Ƀs�N�Z���V�F�[�_�[�ŐF(float4)�ɏ悸��l�ƂȂ�B
 * �F���x 1.0 �͐F���x�����A
 * �F���x 2.0 �͐F���x�Q�{�B���邭�Ȃ�B
 * �F���x 0.5 �͐F���x1/�Q�{�B�Â��Ȃ�B
 * TODO:GgafDxScaler,GgafDxMorpher,GgafDxTextureBlinker �����ʉ�����B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDxTextureBlinker : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxModel* _pModel;

    /** �F���x(0.0 �` 100.0) */
    float _power_blink;
    /** �ڕW�̐F���x */
    float _target_power_blink;
    /** �F���x��� */
    float _top_power_blink;
    /** �F���x���� */
    float _bottom_power_blink;
    /** ���t���[���̐F���x�̑��� */
    float _velo_power_blink;
    /** ���t���[���̐F���x�̑����̑��� */
    float _acce_power_blink;
    /** �O�p�g�̔g�`�œ_�ł̃A�^�b�N�t���[�� */
    frame _beat_attack_frames;
    /** �O�p�g�̔g�`�œ_�ł̃��X�g�t���[�� */
    frame _beat_rest_frames;
    /** �_�łɔ�₷�t���[���� */
    frame _beat_target_frames;
    /** �_�ł��J�n�����t���[�� */
    frame _frame_of_beat_begin;
    /** �r�[�g���A�e���̃A�^�b�N���牺���܂ł̃t���[���� */
    frame _beat_down_frames;
    /** �r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count;
    /** �r�[�g���A�����i���ԍ� */
    int _beat_progres;
    /** ���[�v�J�E���g�i2�œ_�Ń����Z�b�g�A1�Ȃ�Γ_��o�����̕Г��j */
    int _one_way_cnt;
    /** �X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num;
    /** �_�ŕ��@ */
    GgafDxBlinkingMethod _method;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pModel  �K�p�Ώۂ�Model
     */
    GgafDxTextureBlinker(GgafDxModel* prm_pModel);

    /**
     * �F���x�𑊑Ύw��
     * @param prm_power_blink_diff �F���x�l����
     */
    void addBlink(float prm_power_blink_diff) {
        setBlink(_power_blink + prm_power_blink_diff);
    }

    /**
     * �F���x���Ύw��
     * @param prm_power_blink �F���x�l
     */
    void setBlink(float prm_power_blink) {
        //_TRACE_("setBlink ["<<prm_<<"]prm_power_blink="<<prm_power_blink);
        //_TRACE_("setBlink _bottom_power_blink["<<prm_<<"]="<<_bottom_power_blink<<"/_top_power_blink["<<prm_<<"]="<<_top_power_blink<<"");
        if (_top_power_blink < prm_power_blink) {
            _power_blink = _top_power_blink;
        } else if (_bottom_power_blink > prm_power_blink) {
            _power_blink = _bottom_power_blink;
        } else {
            _power_blink = prm_power_blink;
        }
        //_TRACE_("setBlink _power_blink ["<<prm_<<"] _power_blink="<<prm_power_blink);
    }
    /**
     * �F���x�̏��������ݒ�
     * @param prm_power_blink1 �F���x�l1
     * @param prm_power_blink2 �F���x�l2
     */

    /**
     * �ΏېF�������l�ƁA�F���x�̏��������ݒ�
     * @param prm_blink_threshold �_�őΏۂ������l
     * @param prm_power_blink1 �F���x�l1 (���̐� �` 0:�� �` 1.0:���{���x �` )
     * @param prm_power_blink2 �F���x�l2 (���̐� �` 0:�� �` 1.0:���{���x �` )
     */
    void forceBlinkRange(float prm_blink_threshold, float prm_power_blink1, float prm_power_blink2) {
        _pModel->_blink_threshold = prm_blink_threshold;
        if (prm_power_blink1 < prm_power_blink2) {
            _bottom_power_blink = prm_power_blink1;
            _top_power_blink = prm_power_blink2;
        } else {
            _bottom_power_blink = prm_power_blink2;
            _top_power_blink = prm_power_blink1;
        }
        //_TRACE_("forceBlinkRange _bottom_power_blink["<<prm_<<"]="<<_bottom_power_blink<<"/_top_power_blink["<<prm_<<"]="<<_top_power_blink<<"");
    }

    /**
     * �F���x�������Ƀ��Z�b�g
     */
    void setBlinkToBottom() {
        _power_blink = _bottom_power_blink;
    }

    /**
     * �F���x������Ƀ��Z�b�g
     */
    void setBlinkToTop() {
        _power_blink = _top_power_blink;
    }

    /**
     * �_�ł��~������B.
     */
    void stopImmediately();

    /**
     * �Г������_���i�S���E�����t���[�����w��j .
     * �ڕW�̐F���x�ֈ�葬�x�łP��_���i�����j����
     * @param prm_target_power_blink �ڕW�F���x
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetBlinkLinerUntil(float prm_target_power_blink, frame prm_spend_frame);

    /**
     * �Г������_���i�S���E�F���x���x�w��j .
     * �ڕW�̐F���x�ֈ�葬�x�łP��_���i�����j����
     * @param prm_target_power_blink �ڕW�F���x
     * @param prm_velo_power_blink ���t���[�����Z����F���x����(>0.0)�B���̐F���x�������w�肷�鎖�B
     *                             �F���x�̉��Z�����Z���͌��݂̐F���x���ڕW�F���x���������Ⴂ���Ŏ������f����B
     */
    void intoTargetBlinkLinerStep(float prm_target_power_blink, float prm_velo_power_blink);

    /**
     * �Г������_���i�S���E�F���x���x�E�F���x�����x�w��j .
     * �ڕW�̐F���x�։����w��łP��_���i�����j����
     * �F���x�����x��0�Ɏw�肷��� intoTargetBlinkLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetBlinkLinerStep �̑�Q�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��̂Œ��ӂ��Đݒ肹��B
     * @param prm_target_power_blink �ڕW�F���x
     * @param prm_velo_power_blink �����F���x���x
     * @param prm_acce_power_blink �F���x�����x
     */
    void intoTargetBlinkAcceStep(float prm_target_power_blink, float prm_velo_power_blink, float prm_acce_power_blink);

    /**
     * ���������_�� .
     * �ڕW�̐F���x����i_top_power_blink�j�ֈ�葬�x�Ō���A��葬�x�ŐF���x�����i_bottom_power_blink�j���ɖ߂�B
     * ������P���[�v�Ƃ��A��₷�t���[�������w�肷��B
     * @param prm_beat_target_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * �O�p�g�̔g�`�œ_�ł���B.
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
     * �C �F���x���(_top_power_blink���ێ�)<BR>
     * �D �F���x����(_bottom_power_blink���ێ�)<BR>
     * <BR>
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
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     */
    virtual void behave();

    virtual ~GgafDxTextureBlinker();
};

}
#endif /*GGAFDXTEXTUREBLINKER_H_*/
