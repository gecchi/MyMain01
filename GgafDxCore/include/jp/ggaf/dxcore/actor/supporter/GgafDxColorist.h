#ifndef GGAFDXCOLORIST_H_
#define GGAFDXCOLORIST_H_
namespace GgafDxCore {

#define COLOR_R 0
#define COLOR_G 1
#define COLOR_B 2
#define COLOR_A 3;

/**
 * �J���[���X�g����.
 * TODO:���ݖ��g�p�B�쐬���B
 * @version 1.00
 * @since 2011/07/28
 * @author Masatoshi Tsuge
 */
class GgafDxColorist : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxDrawableActor* _pActor;

    /** �e�F�v�f�̋��x(1000 �� 1�{) */
    int _color[4]; //[0]:R�F�v�f�A[1]:G�F�v�f�A[2]:B�F�v�f
    /** �e�F�v�f�̖ڕW�̋��x */
    int _target_color[4];
    /** �e�F�v�f�̋��x��� */
    int _top_color[4];
    /** �e�F�v�f�̋��x���� */
    int _bottom_color[4];
    /** �e�F�v�f�̖��t���[���̋��x�̑��� */
    int _velo_color[4];
    /** �e�F�v�f�̖��t���[���̋��x�̑����̑��� */
    int _acce_color[4];
    /** �e�F�v�f�̃��[�v�J�E���g�i2�Ŋg��k�������Z�b�g�A1�Ȃ�Ίg��or�k���̕Г��j */
    int _one_way_cnt[4];
    /** �e�F�v�f�̃X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num[4];
    /** �e�F�v�f�̃X�P�[�����O���@ */
    GgafDxColoringMethod _method[4];

    /** �r�[�g���A�e�F�v�f�̎O�p�g�̔g�`�ŃX�P�[�����O�̃A�^�b�N�t���[���� */
    frame _beat_attack_frames[4];
    /** �r�[�g���A�e�F�v�f�̎O�p�g�̔g�`�ŃX�P�[�����O�̃��X�g�t���[���� */
    frame _beat_rest_frames[4];
    /** �r�[�g���A�e�F�v�f�̃X�P�[�����O�ɔ�₷�t���[���� */
    frame _beat_target_frames[4];
    /** �r�[�g���A�e�F�v�f�̃A�^�b�N���牺���܂ł̃t���[���� */
    frame _beat_down_frames[4];
    /** �r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count[4];
    /** �r�[�g���A�����i���ԍ� */
    int _beat_progres[4];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafDxColorist(GgafDxDrawableActor* prm_pActor);

    /**
     * ���x�𑊑Ύw��i�S�F�v�f�w��j
     * @param prm_color_diff ���x�l����
     */
    void addColor(int prm_color_diff) {
        for (int c = 0; c < 3; c++) {
            addColor(c, prm_color_diff);
        }
    }
    /**
     * ���x�𑊑Ύw��i�F�v�f�P�ʂŎw��j
     * @param prm_c �F�v�f
     * @param prm_color_diff ���x�l����
     */
    void addColor(int prm_c, int prm_color_diff) {
        setColor(prm_c, _color[prm_c] + prm_color_diff);
    }

    /**
     * ���x���Ύw��i�S�F�v�f�w��j
     * @param prm_color ���x�l
     */
    void setColor(int prm_color) {
        for (int c = 0; c < 3; c++) {
            setColor(c, prm_color);
        }
    }

    /**
     * ���x���Ύw��i�F�v�f�P�ʂŎw��j
     * @param prm_c �F�v�f
     * @param prm_color ���x�l
     */
    void setColor(int prm_c, int prm_color) {
        //_TRACE_("setColor ["<<prm_c<<"]prm_color="<<prm_color);
        //_TRACE_("setColor _bottom_color["<<prm_c<<"]="<<_bottom_color[prm_c]<<"/_top_color["<<prm_c<<"]="<<_top_color[prm_c]<<"");
        if (_top_color[prm_c] < prm_color) {
            _color[prm_c] = _top_color[prm_c];
        } else if (_bottom_color[prm_c] > prm_color) {
            _color[prm_c] = _bottom_color[prm_c];
        } else {
            _color[prm_c] = prm_color;
        }
        //_TRACE_("setColor _color ["<<prm_c<<"] _color[prm_c]="<<prm_color);
    }
    /**
     * ���x�̏��������ݒ�i�S�F�v�f�w��j .
     * �����̑召�͋C�ɂ����n����(�����Ŏ�������)
     * @param prm_color1 ���x�l1
     * @param prm_color2 ���x�l2
     */
    void forceColorRange(int prm_color1, int prm_color2) {
        for (int c = 0; c < 3; c++) {
            forceColorRange(c, prm_color1, prm_color2);
            setColor(c, _color[c]);
        }
    }
    /**
     * ���x�̏��������ݒ�i�F�v�f�P�ʂŎw��j
     * @param prm_c �F�v�f
     * @param prm_color1 ���x�l1
     * @param prm_color2 ���x�l2
     */
    void forceColorRange(int prm_c, int prm_color1, int prm_color2) {
        if (prm_color1 < prm_color2) {
            _bottom_color[prm_c] = prm_color1;
            _top_color[prm_c] = prm_color2;
        } else {
            _bottom_color[prm_c] = prm_color2;
            _top_color[prm_c] = prm_color1;
        }
        //_TRACE_("forceColorRange _bottom_color["<<prm_c<<"]="<<_bottom_color[prm_c]<<"/_top_color["<<prm_c<<"]="<<_top_color[prm_c]<<"");
    }
    /**
     * ���x�����Z�b�g �i�S�F�v�f�w��j .
     * �{�I�u�W�F�N�g(GgafDxColorist)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     */
    void setColorToBottom() {
        for (int c = 0; c < 3; c++) {
            setColorToBottom(c);
        }
    }
    /**
     * ���x�����Z�b�g �i�F�v�f�P�ʂŎw��j
     * �{�I�u�W�F�N�g(GgafDxColorist)�ɂ���ĕω�������O��
     * �����̑傫���ɖ߂��B
     * @param prm_c �F�v�f
     */
    void setColorToBottom(int prm_c) {
        _color[prm_c] = _bottom_color[prm_c];
    }

    void setColorToTop() {
        for (int c = 0; c < 3; c++) {
            setColorToTop(c);
        }
    }
    void setColorToTop(int prm_c) {
        _color[prm_c] = _top_color[prm_c];
    }

    /**
     * �X�P�[�����O���~������B �i�S�F�v�f�w��j .
     */
    void stopImmed();
    /**
     * �X�P�[�����O���~������B �i�F�v�f�P�ʂŎw��j.
     * @param prm_c
     */
    void stopImmed(int prm_c);

    /**
     * �Г������X�P�[�����O�i�S�F�v�f�E�����t���[�����w��j .
     * �ڕW�̋��x�ֈ�葬�x�ŃX�P�[�����O����
     * @param prm_target_color �ڕW���x
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetColorLinerUntil(int prm_target_color, frame prm_spend_frame);

    /**
     * �Г������X�P�[�����O�i�F�v�f�P�ʁE�����t���[�����w��j .
     * �ڕW�̋��x�ֈ�葬�x�ŃX�P�[�����O����B
     * @param prm_c �F�v�f
     * @param prm_target_color �ڕW���x
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetColorLinerUntil(int prm_c, int prm_target_color, frame prm_spend_frame);

    /**
     * �Г������X�P�[�����O�i�S�F�v�f�E���x���x�w��j .
     * �ڕW�̋��x�ֈ�葬�x�ŃX�P�[�����O����
     * @param prm_target_color �ڕW���x
     * @param prm_velo_color ���t���[�����Z���鋭�x����(>0.0)�B���̋��x���w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetColorLinerStep(int prm_target_color, int prm_velo_color);

    /**
     * �Г������X�P�[�����O�i�F�v�f�P�ʁE���x���x�w��j .
     * �ڕW�̋��x�ֈ�葬�x�ŃX�P�[�����O����i���x�����w��j .
     * @param prm_c �F�v�f
     * @param prm_target_color �ڕW���x
     * @param prm_velo_color ���t���[�����Z���鋭�x����(>0.0)�B���̋��x���w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetColorLinerStep(int prm_c, int prm_target_color, int prm_velo_color);

    /**
     * �Г������X�P�[�����O�i�S�F�v�f�E���x���x�E���x�����x�w��j .
     * �ڕW�̋��x�։����w��ŃX�P�[�����O����
     * ���x�����x��0�Ɏw�肷��� intoTargetColorLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetColorLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * ���x�����x�����̏ꍇ�A�ڕW���x�𒴂���ƃX�P�[�����O�I���B
     * ���x�����x�����̏ꍇ�A�ڕW���x�������ƃX�P�[�����O�I���B
     * @param prm_target_color �ڕW���x
     * @param prm_velo_color �������x���x
     * @param prm_acce_color ���x�����x
     */
    void intoTargetColorAcceStep(int prm_target_color, int prm_velo_color, int prm_acce_color);

    /**
     * �Г������X�P�[�����O�i�F�v�f�P�ʁE���x���x�E���x�����x�w��j .
     * �ڕW�̋��x�։����w��ŃX�P�[�����O����i���x���x�A���x�����x���w��j .
     * ���x�����x��0�Ɏw�肷��� intoTargetColorLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetColorLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_c �F�v�f
     * @param prm_target_color �ڕW���x
     * @param prm_velo_color �������x���x
     * @param prm_acce_color ���x�����x
     */
    void intoTargetColorAcceStep(int prm_c, int prm_target_color, int prm_velo_color, int prm_acce_color);

    /**
     * ���������X�P�[�����O�i�S�F�v�f�E�t���[�����w��j .
     * �ڕW�̋��x�ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_beat_target_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(frame prm_beat_target_frames, float prm_beat_num);

    /**
     * ���������X�P�[�����O�i�F�v�f�P�ʁE�t���[�����w��j
     * �ڕW�̋��x�ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_c �F�v�f
     * @param prm_beat_target_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void loopLiner(int prm_c, frame prm_beat_target_frames, float prm_beat_num);

    /**
     * �O�p�g�̔g�`�ŃX�P�[�����O����B�i�S�F�v�f�w��j.
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
     * �C ���x���(_top_color[�F�v�f] �z�񂪕ێ�)<BR>
     * �D ���x����(_bottom_color[�F�v�f] �z�񂪕ێ�)<BR>
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
     * �O�p�g�̔g�`�ŃX�P�[�����O����B�i�F�v�f�w��j.
     * @param prm_c �F�v�f
     * @param prm_beat_target_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_rest_frames ��}�ŇB�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    void beat(int prm_c,
              frame prm_beat_target_frames,
              frame prm_attack_frames,
              frame prm_rest_frames,
              float prm_beat_num);

    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     */
    virtual void behave();

    virtual ~GgafDxColorist();
};

}
#endif /*GGAFDXCOLORIST_H_*/

