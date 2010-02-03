#ifndef GGAFDX9TEXTUREBLINKER_H_
#define GGAFDX9TEXTUREBLINKER_H_
namespace GgafDx9Core {

/**
 * �_�Ŏx���N���X.
 * GgafDx9GeometricActor �̃����o��<BR>
 * _SX , _SY, _SZ  ��� �A�N�^�[�̃X�P�[��<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 * �_��1.0�{�i�X�P�[�������j�́A�{�N���X�ł̃X�P�[���l1000��
 * ��������B�ȉ���
 * [���{��]     �� [�{�N���X�̃X�P�[���l]
 * ���{         �� 1000
 * �g�嗦2.5�{  �� 2500
 * �����̑傫�� �� 500
 * �k����80%    �� 800
 * �{�N���X�ł́A�X�P�[���ƃX�P�[�����O�Ƃ����P������̈Ӗ��Ŏg�p���Ă���ӏ�������B
 * �X�P�[��������݁i�̃t���[���j�̓_�ŏ��
 * �X�P�[�����O����t���[���Ԃ̓_�ŏ�Ԃ̑J��
 * 2009/05/22 GgafDx9GeometryMover ���番�������B
 * @version 1.00
 * @since 2009/05/22
 * @author Masatoshi Tsuge
 */
class GgafDx9TextureBlinker : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ ����֘A //////////////////////////////////////////////
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;

    /** �X�P�[��(1000 �� 1�{) */
    int _scale[3]; //[0]:X���A[1]:Y���A[2]:Z���B�ȍ~���l��  [3]���X���AY���AZ���̈�
    /** �ڕW�̃X�P�[�� */
    int _target_scale[3];
    /** �X�P�[����� */
    int _top_scale[3];
    /** �X�P�[������ */
    int _bottom_scale[3];
    /** ���t���[���̃X�P�[���̑��� */
    int _velo_scale[3];
    /** ���t���[���̃X�P�[���̑����̑��� */
    int _acce_scale[3];
    /** �O�p�g�̔g�`�ŃX�P�[�����O�̃A�^�b�N�t���[�� */
    DWORD _beat_attack_frame[3];
    /** �O�p�g�̔g�`�ŃX�P�[�����O�̃��X�g�t���[�� */
    DWORD _beat_rest_frame[3];
    /** �X�P�[�����O�ɔ�₷�t���[���� */
    DWORD _beat_spend_frame[3];
    /** �X�P�[�����O���J�n�����t���[�� */
    DWORD _beat_begin_frame[3];
    /** ���[�v�J�E���g�i2�œ_�Ń����Z�b�g�A1�Ȃ�Ίg��or�k���̕Г��j */
    int _one_way_cnt[3];
    /** �X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num[3];
    /** �X�P�[�����O���@ */
    GgafDx9BlinkerMethod _method[3];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafDx9TextureBlinker(GgafDx9GeometricActor* prm_pActor);

    /**
     * �X�P�[���𑊑Ύw��i�S���w��j
     * @param prm_scale_diff �X�P�[���l����
     */
    void addScale(int prm_scale_diff) {
        for (int axis = 0; axis < 3; axis++) {
            addScale(axis, prm_scale_diff);
        }
    }
    /**
     * �X�P�[���𑊑Ύw��i���P�ʂŎw��j
     * @param prm_axis ��
     * @param prm_scale_diff �X�P�[���l����
     */
    void addScale(int prm_axis, int prm_scale_diff) {
        setScale(prm_axis, _scale[prm_axis] + prm_scale_diff);
    }

    /**
     * �X�P�[�����Ύw��i�S���w��j
     * @param prm_scale �X�P�[���l
     */
    void setScale(int prm_scale) {
        for (int axis = 0; axis < 3; axis++) {
            setScale(axis, prm_scale);
        }
    }

    /**
     * �X�P�[�����Ύw��i���P�ʂŎw��j
     * @param prm_axis ��
     * @param prm_scale �X�P�[���l
     */
    void setScale(int prm_axis, int prm_scale) {
        //_TRACE_("setScale ["<<prm_axis<<"]prm_scale="<<prm_scale);
        //_TRACE_("setScale _bottom_scale["<<prm_axis<<"]="<<_bottom_scale[prm_axis]<<"/_top_scale["<<prm_axis<<"]="<<_top_scale[prm_axis]<<"");
        if (_top_scale[prm_axis] < prm_scale) {
            _scale[prm_axis] = _top_scale[prm_axis];
        } else if (_bottom_scale[prm_axis] > prm_scale) {
            _scale[prm_axis] = _bottom_scale[prm_axis];
        } else {
            _scale[prm_axis] = prm_scale;
        }
        //_TRACE_("setScale _scale ["<<prm_axis<<"] _scale[prm_axis]="<<prm_scale);
    }
    /**
     * �X�P�[���̏��������ݒ�i�S���w��j .
     * �����̑召�͋C�ɂ����n����(�����Ŏ�������)
     * @param prm_scale1 �X�P�[���l1
     * @param prm_scale2 �X�P�[���l2
     */
    void setScaleRange(int prm_scale1, int prm_scale2) {
        for (int axis = 0; axis < 3; axis++) {
            setScaleRange(axis, prm_scale1, prm_scale2);
        }
    }
    /**
     * �X�P�[���̏��������ݒ�i���P�ʂŎw��j
     * @param prm_axis ��
     * @param prm_scale1 �X�P�[���l1
     * @param prm_scale2 �X�P�[���l2
     */
    void setScaleRange(int prm_axis, int prm_scale1, int prm_scale2) {
        if (prm_scale1 < prm_scale2) {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        } else {
            _bottom_scale[prm_axis] = prm_scale2;
            _top_scale[prm_axis] = prm_scale1;
        }
        //_TRACE_("setScaleRange _bottom_scale["<<prm_axis<<"]="<<_bottom_scale[prm_axis]<<"/_top_scale["<<prm_axis<<"]="<<_top_scale[prm_axis]<<"");
    }
    /**
     * �X�P�[�������Z�b�g �i�S���w��j .
     * �{�I�u�W�F�N�g(GgafDx9TextureBlinker)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     */
    void resetScale() {
        for (int axis = 0; axis < 3; axis++) {
            resetScale(axis);
        }
    }
    /**
     * �X�P�[�������Z�b�g �i���P�ʂŎw��j
     * �{�I�u�W�F�N�g(GgafDx9TextureBlinker)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     * @param prm_axis ��
     */
    void resetScale(int prm_axis) {
        _scale[prm_axis] = _bottom_scale[prm_axis];
    }

    void resetScaleTop() {
        for (int axis = 0; axis < 3; axis++) {
            resetScaleTop(axis);
        }
    }
    void resetScaleTop(int prm_axis) {
        _scale[prm_axis] = _top_scale[prm_axis];
    }

    /**
     * �X�P�[�����O���~������B �i�S���w��j .
     */
    void stopImmediately();
    /**
     * �X�P�[�����O���~������B �i���P�ʂŎw��j.
     * @param prm_axis
     */
    void stopImmediately(int prm_axis);

    /**
     * �Г������X�P�[�����O�i�S���E�����t���[�����w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetScaleLinerUntil(int prm_target_scale, DWORD prm_spend_frame);

    /**
     * �Г������X�P�[�����O�i���P�ʁE�����t���[�����w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����B
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetScaleLinerUntil(int prm_axis, int prm_target_scale, DWORD prm_spend_frame);

    /**
     * �Г������X�P�[�����O�i�S���E�X�P�[�����x�w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale ���t���[�����Z����X�P�[������(>0.0)�B���̃X�P�[�����w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetScaleLinerStep(int prm_target_scale, int prm_velo_scale);

    /**
     * �Г������X�P�[�����O�i���P�ʁE�X�P�[�����x�w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����i�X�P�[�������w��j .
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale ���t���[�����Z����X�P�[������(>0.0)�B���̃X�P�[�����w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetScaleLinerStep(int prm_axis, int prm_target_scale, int prm_velo_scale);

    /**
     * �Г������X�P�[�����O�i�S���E�X�P�[�����x�E�X�P�[�������x�w��j .
     * �ڕW�̃X�P�[���։����w��ŃX�P�[�����O����
     * �X�P�[�������x��0�Ɏw�肷��� intoTargetScaleLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetScaleLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale �����X�P�[�����x
     * @param prm_acce_scale �X�P�[�������x
     */
    void intoTargetScaleAcceStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * �Г������X�P�[�����O�i���P�ʁE�X�P�[�����x�E�X�P�[�������x�w��j .
     * �ڕW�̃X�P�[���։����w��ŃX�P�[�����O����i�X�P�[�����x�A�X�P�[�������x���w��j .
     * �X�P�[�������x��0�Ɏw�肷��� intoTargetScaleLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetScaleLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale �����X�P�[�����x
     * @param prm_acce_scale �X�P�[�������x
     */
    void intoTargetScaleAcceStep(int prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * ���������X�P�[�����O�i�S���E�t���[�����w��j .
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_beat_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(DWORD prm_beat_spend_frame, float prm_beat_num);

    /**
     * ���������X�P�[�����O�i���P�ʁE�t���[�����w��j
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_axis ��
     * @param prm_beat_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(int prm_axis, DWORD prm_beat_spend_frame, float prm_beat_num);

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
     * <BR>
     * @param prm_beat_spend_frame ��}�Ň@�̃t���[����
     * @param prm_attack_frame ��}�ŇA�̃t���[����
     * @param prm_rest_frame ��}�ŇB�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(DWORD prm_beat_spend_frame,
              DWORD prm_attack_frame,
              DWORD prm_rest_frame,
              float prm_beat_num);
    /**
     * �O�p�g�̔g�`�ŃX�P�[�����O����B�i���w��j.
     * @param prm_axis ��
     * @param prm_beat_spend_frame ��}�Ň@�̃t���[����
     * @param prm_attack_frame ��}�ŇA�̃t���[����
     * @param prm_rest_frame ��}�ŇB�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(int prm_axis,
              DWORD prm_beat_spend_frame,
              DWORD prm_attack_frame,
              DWORD prm_rest_frame,
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

