#ifndef GGAFDX9GEOMETRYSCALER_H_
#define GGAFDX9GEOMETRYSCALER_H_
namespace GgafDx9Core {

enum Method {
    NOSCALE,
    TARGET_SCALE_LINER,
    BEAT_SCALE_LINER,
    BEAT_SCALE_TRIANGLEWAVE,
    TARGET_SCALE_SIN,
    BEAT_SCALE_SIN,
    TARGET_SCALE_ACCELERATION,
    BEAT_SCALE_PARABOLA,
    TARGET_SCALE_PARABOLA_REV,
    BEAT_SCALE_PARABOLA_REV
};

/**
 * �g��k���x���N���X.
 * GgafDx9UntransformedActor �̃����o��<BR>
 * _SX , _SY, _SZ  ��� �A�N�^�[�̃X�P�[��<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɐ݌v�����B<BR>
 */
class GgafDx9GeometryScaler : public GgafCore::GgafObject {

public: //_SX , _SY, _SZ ����֘A //////////////////////////////////////////////
    /** �ΏۃA�N�^�[ */
    GgafDx9UntransformedActor* _pActor;

    /** �X�P�[��(1000 �� 1�{) */
    int _scale[3]; //[0]:X���X�P�[���A[1]:Y���X�P�[���A[1]:Z���X�P�[��
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
    /** ���[�v�J�E���g�i2�Ŋg��k�������Z�b�g�A1�Ȃ�Ίg��or�k���̕Г��j */
    int _one_way_cnt[3];
    /** �X�g�b�v����\��̃��[�v�J�E���g */
    int _stop_one_way_num[3];
    /** �X�P�[�����O���@ */
    Method _method[3];

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDx9GeometryScaler(GgafDx9UntransformedActor* prm_pActor);

    void increaseScale(int prm_scale_diff) {
        for (int axis = 0; axis < 3; axis++) {
            increaseScale(axis, prm_scale_diff);
        }
    }

    void increaseScale(int prm_axis, int prm_scale_diff) {
        setScale(prm_axis, _scale[prm_axis] + prm_scale_diff);
    }


    void setScale(int prm_scale) {
        for (int axis = 0; axis < 3; axis++) {
            setScale(axis, prm_scale);
        }
   }

    void setScale(int prm_axis, int prm_scale) {
        if (_top_scale[prm_axis] < prm_scale) {
            _scale[prm_axis] = _top_scale[prm_axis];
        } else if (_bottom_scale[prm_axis] > prm_scale) {
            _scale[prm_axis] = _bottom_scale[prm_axis];
        } else {
            _scale[prm_axis] = prm_scale;
        }
    }
    /**
     * �X�P�[�����O�̏��������ݒ�i�S���w��j
     * @param prm_scale1
     * @param prm_scale2
     */
    void setScaleRange(int prm_scale1, int prm_scale2) {
        for (int axis = 0; axis < 3; axis++) {
            setScaleRange(axis, prm_scale1, prm_scale2);
        }
    }
    /**
     * �X�P�[�����O�̏��������ݒ�i�����ƂɎw��j
     * @param prm_axis ��
     * @param prm_scale1
     * @param prm_scale2
     */
    void setScaleRange(int prm_axis, int prm_scale1, int prm_scale2) {
        if (prm_scale1 < prm_scale2) {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        } else {
            _bottom_scale[prm_axis] = prm_scale1;
            _top_scale[prm_axis] = prm_scale2;
        }
    }

    void resetScale() {
        for (int axis = 0; axis < 3; axis++) {
            resetScale(axis);
        }
    }
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


    void stopImmediately();
    void stopImmediately(int prm_axis);

    /**
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����i�t���[�����w��j .
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetScaleLinerUntil(int prm_target_scale, DWORD prm_spend_frame);

    /**
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����i�t���[�����w��j .
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_spend_frame ��₷�t���[����
     */
    void intoTargetScaleLinerUntil(int prm_axis, int prm_target_scale, DWORD prm_spend_frame);

    /**
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����i�X�P�[�������w��j .
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale ���t���[�����Z����X�P�[������(>0.0)�B���̃X�P�[�����w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetScaleLinerStep(int prm_target_scale, int prm_velo_scale);

    /**
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O����i�X�P�[�������w��j .
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale ���t���[�����Z����X�P�[������(>0.0)�B���̃X�P�[�����w�肷�鎖�B���Z�����Z���͎������f����B
     */
    void intoTargetScaleLinerStep(int prm_axis, int prm_target_scale, int prm_velo_scale);

    /**
     * �ڕW�̃X�P�[���։����w��ŃX�P�[�����O����i�X�P�[�����x�A�X�P�[�������x���w��j .
     * �X�P�[�������x��0�Ɏw�肷��� intoTargetScaleLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetScaleLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale �����X�P�[�����x
     * @param prm_acce_scale �X�P�[�������x
     */
    void intoTargetScaleAccelerationStep(int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * �ڕW�̃X�P�[���։����w��ŃX�P�[�����O����i�X�P�[�����x�A�X�P�[�������x���w��j .
     * �X�P�[�������x��0�Ɏw�肷��� intoTargetScaleLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * intoTargetScaleLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_axis ��
     * @param prm_target_scale �ڕW�X�P�[��
     * @param prm_velo_scale �����X�P�[�����x
     * @param prm_acce_scale �X�P�[�������x
     */
    void intoTargetScaleAccelerationStep(int prm_axis, int prm_target_scale, int prm_velo_scale, int prm_acce_scale);

    /**
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_beat_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void beatLiner(DWORD prm_beat_spend_frame, float prm_beat_num);

    /**
     * �ڕW�̃X�P�[���ֈ�葬�x�ŃX�P�[�����O���A��葬�x�Ō��ɖ߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_axis ��
     * @param prm_beat_spend_frame �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(0.5 ��P�ʂŎw��\)
     */
    void beatLiner(int prm_axis, DWORD prm_beat_spend_frame, float prm_beat_num);

    /**
     * �O�p�g�̔g�`�ŃX�P�[�����O����B.
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
     * �C �X�P�[�����(_top_scale[prm_axis] ���ێ�)<BR>
     * �D �X�P�[������(_bottom_scale[prm_axis] ���ێ�)<BR>
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
     * �O�p�g�̔g�`�ŃX�P�[�����O����B.
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
     * ���t���[����Actor�̐U�镑���B<BR>
     * �{�N���X�𗘗p����ꍇ�́A����behave() �𖈃t���[�����s���܂��B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9GeometryScaler();
};

}
#endif /*GGAFDX9GEOMETRYSCALER_H_*/

