#ifndef GGAFDX9TEXTUREBLINKER_H_
#define GGAFDX9TEXTUREBLINKER_H_
namespace GgafDx9Core {

/**
 * ����J���[�_�Ŏx���N���X.
 * GgafDx9Model �̃����o�� _fPowerBlink <BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �ŏI�I�Ƀs�N�Z���V�F�[�_�[�ŐF(float4)�ɏ悸��l�ƂȂ�B
 * �F���x 1.0 �͐F���x�����A
 * �F���x 2.0 �͐F���x�Q�{�B���邭�Ȃ�B
 * �F���x 0.5 �͐F���x1/�Q�{�B�Â��Ȃ�B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureBlinker : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ ����֘A //////////////////////////////////////////////
    /** �ΏۃA�N�^�[ */
    GgafDx9Model* _pModel;

    /** �F���x(0.0 �` 100.0) */
    float _fPowerBlink;
    /** �ڕW�̐F���x */
    float _target_fPowerBlink;
    /** �F���x��� */
    float _top_fPowerBlink;
    /** �F���x���� */
    float _bottom_fPowerBlink;
    /** ���t���[���̐F���x�̑��� */
    float _velo_fPowerBlink;
    /** ���t���[���̐F���x�̑����̑��� */
    float _acce_fPowerBlink;
    /** �O�p�g�̔g�`�œ_�ł̃A�^�b�N�t���[�� */
    UINT32 _beat_attack_frame;
    /** �O�p�g�̔g�`�œ_�ł̃��X�g�t���[�� */
    UINT32 _beat_rest_frame;
    /** �_�łɔ�₷�t���[���� */
    UINT32 _beat_spend_frame;
    /** �_�ł��J�n�����t���[�� */
    UINT32 _beat_begin_frame;
    /** ���[�v�J�E���g�i2�œ_�Ń����Z�b�g�A1�Ȃ�Ίg��or�k���̕Г��j */
    int _one_way_cnt;
    /** �X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num;
    /** �_�ŕ��@ */
    GgafDx9BlinkerMethod _method;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pModel  �K�p�Ώۂ�Model
     */
    GgafDx9TextureBlinker(GgafDx9Model* prm_pModel);

    /**
     * �F���x�𑊑Ύw��
     * @param prm_fPowerBlink_diff �F���x�l����
     */
    void addBlink(float prm_fPowerBlink_diff) {
        setBlink(_fPowerBlink + prm_fPowerBlink_diff);
    }

    /**
     * �F���x���Ύw��
     * @param prm_fPowerBlink �F���x�l
     */
    void setBlink(float prm_fPowerBlink) {
        //_TRACE_("setBlink ["<<prm_<<"]prm_fPowerBlink="<<prm_fPowerBlink);
        //_TRACE_("setBlink _bottom_fPowerBlink["<<prm_<<"]="<<_bottom_fPowerBlink<<"/_top_fPowerBlink["<<prm_<<"]="<<_top_fPowerBlink<<"");
        if (_top_fPowerBlink < prm_fPowerBlink) {
            _fPowerBlink = _top_fPowerBlink;
        } else if (_bottom_fPowerBlink > prm_fPowerBlink) {
            _fPowerBlink = _bottom_fPowerBlink;
        } else {
            _fPowerBlink = prm_fPowerBlink;
        }
        //_TRACE_("setBlink _fPowerBlink ["<<prm_<<"] _fPowerBlink="<<prm_fPowerBlink);
    }
    /**
     * �F���x�̏��������ݒ�
     * @param prm_fPowerBlink1 �F���x�l1
     * @param prm_fPowerBlink2 �F���x�l2
     */
    void forceBlinkRange(float prm_fPowerBlink1, float prm_fPowerBlink2) {
        if (prm_fPowerBlink1 < prm_fPowerBlink2) {
            _bottom_fPowerBlink = prm_fPowerBlink1;
            _top_fPowerBlink = prm_fPowerBlink2;
        } else {
            _bottom_fPowerBlink = prm_fPowerBlink2;
            _top_fPowerBlink = prm_fPowerBlink1;
        }
        //_TRACE_("forceBlinkRange _bottom_fPowerBlink["<<prm_<<"]="<<_bottom_fPowerBlink<<"/_top_fPowerBlink["<<prm_<<"]="<<_top_fPowerBlink<<"");
    }
    /**
     * �F���x�����Z�b�g
     * �{�I�u�W�F�N�g(GgafDx9TextureBlinker)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     */
    void setBlinkToBottom() {
        _fPowerBlink = _bottom_fPowerBlink;
    }

    void setBlinkToTop() {
        _fPowerBlink = _top_fPowerBlink;
    }

    /**
     * �_�ł��~������B  .
     */
    void stopImmediately();

    /**
     * �Г������_�Łi�S���E�����t���[�����w��j .
     * �ڕW�̐F���x�ֈ�葬�x�œ_�ł���
     * @param prm_target_fPowerBlink �ڕW�F���x
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetBlinkLinerUntil(float prm_target_fPowerBlink, UINT32 prm_spend_frame);

    /**
     * �Г������_�Łi�S���E�F���x���x�w��j .
     * �ڕW�̐F���x�ֈ�葬�x�œ_�ł���
     * @param prm_target_fPowerBlink �ڕW�F���x
     * @param prm_velo_fPowerBlink ���t���[�����Z����F���x����(>0.0)�B���̐F���x�������w�肷�鎖�B
     *                             �F���x�̉��Z�����Z���͌��݂̐F���x���ڕW�F���x���������Ⴂ���Ŏ������f����B
     */
    void intoTargetBlinkLinerStep(float prm_target_fPowerBlink, float prm_velo_fPowerBlink);

    /**
     * �Г������_�Łi�S���E�F���x���x�E�F���x�����x�w��j .
     * �ڕW�̐F���x�։����w��œ_�ł���
     * �F���x�����x��0�Ɏw�肷��� intoTargetBlinkLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetBlinkLinerStep �̑�Q�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��̂Œ��ӂ��Đݒ肹��B
     * @param prm_target_fPowerBlink �ڕW�F���x
     * @param prm_velo_fPowerBlink �����F���x���x
     * @param prm_acce_fPowerBlink �F���x�����x
     */
    void intoTargetBlinkAcceStep(float prm_target_fPowerBlink, float prm_velo_fPowerBlink, float prm_acce_fPowerBlink);

    /**
     * ���������_�� .
     * �ڕW�̐F���x����i_top_fPowerBlink�j�ֈ�葬�x�Ō���A��葬�x�ŐF���x�����i_bottom_fPowerBlink�j���ɖ߂�B
     * ������P���[�v�Ƃ��A��₷�t���[�������w�肷��B
     * @param prm_beat_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(UINT32 prm_beat_spend_frame, float prm_beat_num);

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
     * �C �F���x���(_top_fPowerBlink���ێ�)<BR>
     * �D �F���x����(_bottom_fPowerBlink���ێ�)<BR>
     * <BR>
     * @param prm_beat_spend_frame ��}�Ň@�̃t���[����
     * @param prm_attack_frame ��}�ŇA�̃t���[����
     * @param prm_rest_frame ��}�ŇB�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(UINT32 prm_beat_spend_frame,
              UINT32 prm_attack_frame,
              UINT32 prm_rest_frame,
              float prm_beat_num);


    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     */
    virtual void behave();

    virtual ~GgafDx9TextureBlinker();
};

}
#endif /*GGAFDX9TEXTUREBLINKER_H_*/

