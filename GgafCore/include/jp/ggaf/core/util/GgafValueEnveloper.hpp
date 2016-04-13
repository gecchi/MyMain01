#ifndef GGAFCORE_GGAFVALUEENVELOPER_H_
#define GGAFCORE_GGAFVALUEENVELOPER_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/util/GgafUtil.h"

namespace GgafCore {

/**
 * �l�̑J�ڃw���p�[ .
 * �I�ɔO��̋��ʉ��B
 * @tparam VAL_TYPE �J�ڒl�̃f�[�^�^
 * @tparam N �C���f�b�N�X(����)�̐�
 * @version 1.00
 * @since 2014/02/19
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE, int N>
class GgafValueEnveloper : public GgafObject {

public:
    enum TransitionMethod {
        NO_TRANSITION,
        TARGET_LINER_TO,
        TARGET_LINER_STEP,
        BEAT_LINER,
        BEAT_TRIANGLEWAVE,
        R_BEAT_TRIANGLEWAVE,
        BEAT_TRIGONOMETRIC,
        TARGET_ACCELERATION_STEP,
    };

    struct Parameter {
        /** [r/w]�e�ΏۃC���f�b�N�X�̖ڕW�̑J�� */
        VAL_TYPE _target;
        /** [r/w]�e�ΏۃC���f�b�N�X�̑J�ڏ�� */
        VAL_TYPE _top;
        /** [r/w]�e�ΏۃC���f�b�N�X�̑J�ډ��� */
        VAL_TYPE _bottom;
        /** [r/w]�e�ΏۃC���f�b�N�X�̖��t���[���̑J�ڂ̑��� */
        VAL_TYPE _velo;
        /** [r/w]�e�ΏۃC���f�b�N�X�̖��t���[���̑J�ڂ̑����̑��� */
        VAL_TYPE _acce;
        /** [r]�e�ΏۃC���f�b�N�X�̒l�J�ڕ��@ */
        TransitionMethod _method;
        /** [r]�r�[�g���A�e�ΏۃC���f�b�N�X�̑�`�g�̃A�^�b�N�I�����̃t���[�� */
        frame _beat_frame_of_attack_finish;
        /** [r]�r�[�g���A�e�ΏۃC���f�b�N�X�̑�`�g�̈ێ��I�����̃t���[�� */
        frame _beat_frame_of_sustain_finish;
        /** [r]�r�[�g���A�e�ΏۃC���f�b�N�X�̑�`�g�̌���(�]�C)�I�����̃t���[�� */
        frame _beat_frame_of_release_finish;
        /** [r]�r�[�g���A�e�ΏۃC���f�b�N�X�̑�`�g�̔g�`�ł̂P�����̃t���[���� */
        frame _beat_cycle_frames;
        /** [r]�r�[�g���A�e�ΏۃC���f�b�N�X�̒l�J�ڂɔ�₷�t���[���� */
        frame _beat_target_frames;
        /** [r]�r�[�g���A�����J�E���^�[ */
        frame _beat_frame_count_in_roop;
        /** [r]�r�[�g���A�����J�E���^�[ */
        frame _beat_frame_count;
    };
    Parameter _parameter[N];

public:
    /**
     * �l���擾����i�v�����j .
     * @param idx �C���f�b�N�X
     * @return �l
     */
    virtual VAL_TYPE getValue(int idx) = 0;

    /**
     * �l��ݒ肷��i�v�����j .
     * @param idx �C���f�b�N�X
     * @param value �l
     */
    virtual void setValue(int idx, VAL_TYPE value) = 0;

public:
    /**
     * �R���X�g���N�^<BR>
     */
    GgafValueEnveloper() : GgafObject() {
        Parameter* p = _parameter;
        for (int i = 0; i < N; i++) {
            p->_velo = 0;
            p->_acce = 0;
            p->_target = 0;
            p->_top = 0;
            p->_bottom = 0;
            p->_beat_frame_of_attack_finish = 0;
            p->_beat_frame_of_sustain_finish = 0;
            p->_beat_frame_of_release_finish = 0;
            p->_beat_cycle_frames = 0;
            p->_beat_target_frames = 0;
            p->_beat_frame_count_in_roop = 0;
            p->_beat_frame_count = 0;
            p->_method = NO_TRANSITION;
            ++p;
        }
    }

    /**
     * �l�J�ڂ̏��������ݒ�i�S�ΏۃC���f�b�N�X�w��j .
     * �����̑召�͋C�ɂ����n����(�����Ŏ�������)
     * @param prm1 �J�ڒl1
     * @param prm2 �J�ڒl2
     */
    virtual void setRange(VAL_TYPE prm1, VAL_TYPE prm2) {
        for (int i = 0; i < N; i++) {
            setRange(i, prm1, prm2);
        }
    }

    /**
     * �l�J�ڂ̏�������l��ݒ�i�ΏۃC���f�b�N�X�P�ʂŎw��j .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm1 �J�ڒl1
     * @param prm2 �J�ڒl2
     */
    virtual void setRange(int prm_idx, VAL_TYPE prm1, VAL_TYPE prm2) {
        if (prm1 < prm2) {
            setBottom(prm_idx, prm1);
            setTop(prm_idx, prm2);
        } else {
            setBottom(prm_idx, prm2);
            setTop(prm_idx, prm1);
        }
    }

    /**
     * ����l��ݒ�i�ΏۃC���f�b�N�X�P�ʂŎw��j .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_top ����l
     */
    virtual void setTop(int prm_idx, VAL_TYPE prm_top) {
        _parameter[prm_idx]._top = prm_top;
    }

    /**
     * �����l��ݒ�i�ΏۃC���f�b�N�X�P�ʂŎw��j .
     * @param prm_bottom �����l
     */
    virtual void setBottom(int prm_idx, VAL_TYPE prm_bottom) {
        _parameter[prm_idx]._bottom = prm_bottom;
    }

    /**
     * ����l��ݒ�i�S�ΏۃC���f�b�N�X�w��j .
     * @param prm_top ����l
     */
    virtual void setTop(VAL_TYPE prm_top) {
        for (int i = 0; i < N; i++) {
            setTop(i, prm_top);
        }
    }

    /**
     * �����l��ݒ�i�S�ΏۃC���f�b�N�X�w��j .
     * @param prm_bottom �����l
     */
    virtual void setBottom(VAL_TYPE prm_bottom) {
        for (int i = 0; i < N; i++) {
            setBottom(i, prm_bottom);
        }
    }

    /**
     * �l�J�ڂ̏���l���擾 .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @return ����l
     */
    virtual VAL_TYPE getTop(int prm_idx) const {
        return _parameter[prm_idx]._top;
    }

    /**
     * �l�J�ڂ̉����l���擾 .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @return
     */
    virtual VAL_TYPE getBottom(int prm_idx) const {
        return _parameter[prm_idx]._bottom;
    }

    /**
     * �l�J�ڂ̏���l���擾 .
     * �ΏۃC���f�b�N�X���Q�ȏ�̏ꍇ�A�S����l�̒��ōŏ���Ԃ��B
     * @return ����l
     */
    virtual VAL_TYPE getTop() const {
        //_top�̍ŏ��l��Ԃ�
        if (N == 1) {
            return _parameter[0]._top;
        } else {
            VAL_TYPE minv = _parameter[0]._top;
            const Parameter* p = &_parameter[1];
            for (int i = 1; i < N; i++) {
                if (minv > p->_top) {
                    minv = p->_top;
                }
                ++p;
            }
            return minv;
        }
    }

    /**
     * �l�J�ڂ̉����l���擾 .
     * �ΏۃC���f�b�N�X���Q�ȏ�̏ꍇ�A�S�����l�̒��ōő��Ԃ��B
     * @return ����l
     */
    virtual VAL_TYPE getBottom() const {
        //_bottom�̍ő�l��Ԃ�
        if (N == 1) {
            return _parameter[0]._bottom;
        } else {
            VAL_TYPE maxv = _parameter[0]._bottom;
            const Parameter* p = &_parameter[1];
            for (int i = 1; i < N; i++) {
                if (maxv > p->_bottom) {
                    maxv = p->_bottom;
                }
                ++p;
            }
            return maxv;
        }
    }

    /**
     * �l�J�ڂ��~������B�i�S�ΏۃC���f�b�N�X�w��j .
     */
    virtual void stop() {
        for (int i = 0; i < N; i++) {
            stop(i);
        }
    }

    /**
     * �l�J�ڂ��~������B �i�ΏۃC���f�b�N�X�P�ʂŎw��j.
     * @param prm_idx �C���f�b�N�X
     */
    virtual void stop(int prm_idx) {
        Parameter* p = &_parameter[prm_idx];
        p->_velo = 0;
        p->_acce = 0;
        p->_method = NO_TRANSITION;
    }

    /**
     * �Г������l�J�ځi�S�ΏۃC���f�b�N�X�E�����t���[�����w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���
     * @param prm_target_T �J�ږڕW�l
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        for (int i = 0; i < N; i++) {
            transitionLinerUntil(i, prm_target, prm_spend_frame);
        }
    }

    /**
     * �Г������l�J�ځi�ΏۃC���f�b�N�X�P�ʁE�����t���[�����w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���B
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_target_T �J�ږڕW�l
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerUntil(int prm_idx, VAL_TYPE prm_target, frame prm_spend_frame) {
        Parameter* p = &_parameter[prm_idx];
        p->_beat_frame_count = 0;
        p->_beat_target_frames = prm_spend_frame;
        p->_target = prm_target;
        p->_method = TARGET_LINER_TO;
        //�ŏ��̃A�^�b�N�܂ł̑��x
        const VAL_TYPE val = getValue(prm_idx);
        if (p->_beat_target_frames > 0 ) {
            p->_velo = (VAL_TYPE)( ((double)(p->_target - val)) / ((double)(p->_beat_target_frames)) );
        } else if (p->_beat_target_frames == 0 ) {
            p->_velo = p->_target - val;
        }
    }

    /**
     * ����J�ڂ֕Г������l�J�ځi�S�ΏۃC���f�b�N�X�E�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerToTop(frame prm_spend_frame) {
        transitionLinerUntil(getTop(), prm_spend_frame);
    }

    /**
     * �����J�ڂ֕Г������l�J�ځi�S�ΏۃC���f�b�N�X�E�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerToBottom(frame prm_spend_frame) {
        transitionLinerUntil(getBottom(), prm_spend_frame);
    }

    /**
     * �Г������l�J�ځi�S�ΏۃC���f�b�N�X�E�J�ڑ��x�w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���
     * @param prm_target_T �J�ږڕW�l
     * @param prm_velo_T ���t���[�����Z����J�ڍ���(>0.0)�B���̑J�ڂ��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    virtual void transitionLinerStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        for (int i = 0; i < N; i++) {
            transitionLinerStep(i, prm_target, prm_velo);
        }
    }

    /**
     * �Г������l�J�ځi�ΏۃC���f�b�N�X�P�ʁE�J�ڑ��x�w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���i�J�ڍ����w��j .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_target_T �J�ږڕW�l
     * @param prm_velo_T ���t���[�����Z����J�ڍ���(>0.0)�B���̑J�ڂ��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    virtual void transitionLinerStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = TARGET_LINER_STEP;
        p->_velo = prm_velo;
        p->_target = prm_target;
        p->_beat_frame_count = 0;
        p->_beat_target_frames = MAX_FRAME;
    }

    /**
     * �Г������l�J�ځi�S�ΏۃC���f�b�N�X�E�J�ڑ��x�E�J�ډ����x�w��j .
     * �ڕW�̑J�ڂ։����w��Œl�J�ڂ���
     * �J�ډ����x��0�Ɏw�肷��� transitionLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * transitionLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * �J�ډ����x�����̏ꍇ�A�J�ږڕW�l�𒴂���ƒl�J�ڏI���B
     * �J�ډ����x�����̏ꍇ�A�J�ږڕW�l�������ƒl�J�ڏI���B
     * @param prm_target_T �J�ږڕW�l
     * @param prm_velo_T �����J�ڑ��x
     * @param prm_acce_T �J�ډ����x
     */
    virtual void transitionAcceStep(VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        for (int i = 0; i < N; i++) {
            transitionAcceStep(i, prm_target, prm_velo, prm_acce);
        }
    }

    /**
     * �Г������l�J�ځi�ΏۃC���f�b�N�X�P�ʁE�J�ڑ��x�E�J�ډ����x�w��j .
     * �ڕW�̑J�ڂ։����w��Œl�J�ڂ���i�J�ڑ��x�A�J�ډ����x���w��j .
     * �J�ډ����x��0�Ɏw�肷��� transitionLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * transitionLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_target_T �J�ږڕW�l
     * @param prm_velo_T �����J�ڑ��x
     * @param prm_acce_T �J�ډ����x
     */
    virtual void transitionAcceStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = TARGET_ACCELERATION_STEP;
        p->_target = prm_target;
        p->_velo = prm_velo;
        p->_acce = prm_acce;
        p->_beat_frame_count = 0;
        p->_beat_target_frames = MAX_FRAME;
    }

    /**
     * ���������l�J�ځi�S�ΏۃC���f�b�N�X�E�t���[�����w��j .
     * ����J�ڂֈ�葬�x�Œl�J�ڂ��A��葬�x�ŉ��J�ڂ֖߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_cycle_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(1.2��ȂǏ����Ŏw��\�A-1 �łقږ������[�v)
     * @param prm_is_to_top true:���߂�TOP�ɑJ�ڂ���^false:���߂�BOTTOM�ɑJ��
     */
    void transitionLinerLoop(frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        for (int i = 0; i < N; i++) {
            transitionLinerLoop(i, prm_cycle_frames, prm_beat_num, prm_is_to_top);
        }
    }

    /**
     * ���������l�J�ځi�ΏۃC���f�b�N�X�P�ʁE�t���[�����w��j
     * ����J�ڂֈ�葬�x�Œl�J�ڂ��A��葬�x�ŉ��J�ڂ֖߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_cycle_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(1.2��ȂǏ����Ŏw��\�A-1 �łقږ������[�v)
     * @param prm_is_to_top true:���߂�TOP�ɑJ�ڂ���^false:���߂�BOTTOM�ɑJ��
     */
    virtual void transitionLinerLoop(int prm_idx, frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        Parameter* p = &_parameter[prm_idx];
        const VAL_TYPE val = getValue(prm_idx);
        p->_method = BEAT_LINER;
        p->_beat_frame_count = 0;
        p->_beat_frame_count_in_roop = 0;
        p->_beat_cycle_frames = prm_cycle_frames;
        if (prm_beat_num < 0) {
            p->_beat_target_frames = MAX_FRAME;
        } else {
            p->_beat_target_frames = prm_cycle_frames * prm_beat_num;
        }
        if (prm_is_to_top) {
            p->_velo = 1.0*(p->_top - val) / ((int)prm_cycle_frames / 2.0);
            if (ZEROd_EQ(p->_velo)) {
                p->_velo = 1; //���ł���΂悢
            }
        } else {
            p->_velo = 1.0*(p->_bottom - val) / ((int)prm_cycle_frames / 2.0);
            if (ZEROd_EQ(p->_velo)) {
                p->_velo = -1; //���ł���΂悢
            }
        }
    }

    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B�i�S�ΏۃC���f�b�N�X�w��j.
     * <PRE>
     * �D  _ _ _   �Q�Q�Q   _ _ _ _ _ _ _ _ _    �Q�Q�Q   _ _ _ _ _ _ _ _ _
     *            /:    :�_                     /      �_
     *           / :    :  �_                  /         �_
     *          /  :    :    �_               /            �_
     *         /   :    :      �_            /               �_
     *        /    :    :        �_         /                  �_
     * �E�Q�Q/  _ _:_ _ : _ _ _ _  �_�Q�Q�Q/  _ _ _ _ _ _ _ _ _  �_�Q�Q�Q/
     *       �������@����������������������
     *       ���A�����B���������C����
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[����<BR>
     * �A �A�^�b�N�܂ł̃t���[����<BR>
     * �B �ێ��t���[����<BR>
     * �C ����(�]�C)�t���[����<BR>
     * �D �J�ڏ��(_top[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * �E �J�ډ���(_bottom[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * ���̓� �@�`�C�������Őݒ�A�D�E��setRange()�̐ݒ�l���g�p�����B<BR>
     * @param prm_cycle_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_sustain_frames ��}�ŇB�̃t���[����
     * @param prm_release_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    virtual void beat(frame prm_cycle_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_release_frames,
                      double prm_beat_num) {
        for (int i = 0; i < N; i++) {
            beat(i, prm_cycle_frames, prm_attack_frames, prm_sustain_frames, prm_release_frames, prm_beat_num);
        }
    }

    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B�i�ΏۃC���f�b�N�X�ʎw��j.
     * <PRE>
     * �D  _ _ _   �Q�Q�Q   _ _ _ _ _ _ _ _ _    �Q�Q�Q   _ _ _ _ _ _ _ _ _
     *            /:    :�_                     /      �_
     *           / :    :  �_                  /         �_
     *          /  :    :    �_               /            �_
     *         /   :    :      �_            /               �_
     *        /    :    :        �_         /                  �_
     * �E�Q�Q/  _ _:_ _ : _ _ _ _  �_�Q�Q�Q/  _ _ _ _ _ _ _ _ _  �_�Q�Q�Q/
     *       �������@����������������������
     *       ���A�����B���������C����
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P����(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[����<BR>
     * �A �A�^�b�N�܂ł̃t���[����<BR>
     * �B �ێ��t���[����<BR>
     * �C ����(�]�C)�t���[����<BR>
     * �D �J�ڏ��(_top[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * �E �J�ډ���(_bottom[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * ���̓� �@�`�C�������Őݒ�A�D�E��setRange()�̐ݒ�l���g�p�����B<BR>
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_cycle_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_sustain_frames ��}�ŇB�̃t���[����
     * @param prm_release_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    virtual void beat(int prm_idx,
                      frame prm_cycle_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_release_frames,
                      double prm_beat_num) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = BEAT_TRIANGLEWAVE;
        p->_beat_frame_count = 0;
        p->_beat_frame_count_in_roop = 0;
        p->_beat_frame_of_attack_finish = prm_attack_frames;
        p->_beat_frame_of_sustain_finish = p->_beat_frame_of_attack_finish + prm_sustain_frames;
        p->_beat_frame_of_release_finish = p->_beat_frame_of_sustain_finish + prm_release_frames;
        p->_beat_cycle_frames = prm_cycle_frames; //����
        if (prm_beat_num < 0) {
            p->_beat_target_frames = MAX_FRAME;
        } else {
            p->_beat_target_frames = p->_beat_cycle_frames * prm_beat_num;
        }
        //�ŏ��̃A�^�b�N�܂ł̑��x
        const VAL_TYPE val = getValue(prm_idx);
        if (p->_beat_frame_of_attack_finish > 0 ) {
            p->_velo = (VAL_TYPE)( ((double)(p->_top - val)) / ((double)(p->_beat_frame_of_attack_finish)) );
        } else if (p->_beat_frame_of_attack_finish == 0 ) {
            p->_velo = p->_top - val;
        }
    }



    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B�i�S�ΏۃC���f�b�N�X�w��j.
     * <PRE>
     * �D  �Q�Q _ _ _ _ _ _ _ _ _ _ _  �Q�Q�Q _ _ _ _ _ _ _ _ _ _ _  �Q�Q�Q
     *        :�_                     /:    :�_                     /:
     *        :  �_                  / :    :  �_                  / :
     *        :    �_               /  :    :    �_               /  :
     *        :      �_            /   :    :      �_            /   :
     *        :        �_         /    :    :        �_         /    :
     * �E  _ _:_ _ _ _ _ �_�Q�Q�Q/  _ _:_ _ :_ _ _ _ _ �_�Q�Q�Q/  _ _:_ _
     *         �������@����������������������
     *         �������A�������B�����A��
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P����(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[����<BR>
     * �A �A�^�b�N(����)�܂ł̃t���[����<BR>
     * �B �����ێ��t���[����<BR>
     * �C ���A�t���[����<BR>
     * �D �J�ڏ��(_top[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * �E �J�ډ���(_bottom[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * ���̓� �@�`�C�������Őݒ�A�D�E��setRange()�̐ݒ�l���g�p�����B<BR>
     * @param prm_cycle_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_sustain_frames ��}�ŇB�̃t���[����
     * @param prm_release_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    virtual void rbeat(frame prm_cycle_frames,
                       frame prm_attack_frames,
                       frame prm_sustain_frames,
                       frame prm_release_frames,
                       double prm_beat_num) {
        for (int i = 0; i < N; i++) {
            rbeat(i, prm_cycle_frames, prm_attack_frames, prm_sustain_frames, prm_release_frames, prm_beat_num);
        }
    }


    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B�i�ΏۃC���f�b�N�X�ʎw��j.
     * <PRE>
     * �D  �Q�Q _ _ _ _ _ _ _ _ _ _ _  �Q�Q�Q _ _ _ _ _ _ _ _ _ _ _  �Q�Q�Q
     *        :�_                     /:    :�_                     /:
     *        :  �_                  / :    :  �_                  / :
     *        :    �_               /  :    :    �_               /  :
     *        :      �_            /   :    :      �_            /   :
     *        :        �_         /    :    :        �_         /    :
     * �E  _ _:_ _ _ _ _ �_�Q�Q�Q/  _ _:_ _ :_ _ _ _ _ �_�Q�Q�Q/  _ _:_ _
     *         �������@����������������������
     *         �������A�������B�����A��
     * </PRE>
     * ���K�v�Ȑݒ�l��<BR>
     * �@ �P����(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[����<BR>
     * �A �A�^�b�N(����)�܂ł̃t���[����<BR>
     * �B �����ێ��t���[����<BR>
     * �C ���A�t���[����<BR>
     * �D �J�ڏ��(_top[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * �E �J�ډ���(_bottom[�ΏۃC���f�b�N�X] �z�񂪕ێ�)<BR>
     * ���̓� �@�`�C�������Őݒ�A�D�E��setRange()�̐ݒ�l���g�p�����B<BR>
     * @param prm_idx �ΏۃC���f�b�N�X
     * @param prm_cycle_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_sustain_frames ��}�ŇB�̃t���[����
     * @param prm_release_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    virtual void rbeat(int prm_idx,
                       frame prm_cycle_frames,
                       frame prm_attack_frames,
                       frame prm_sustain_frames,
                       frame prm_release_frames,
                       double prm_beat_num) {
        Parameter* p = &_parameter[prm_idx];
        p->_method = R_BEAT_TRIANGLEWAVE;
        p->_beat_frame_count = 0;
        p->_beat_frame_count_in_roop = 0;
        p->_beat_frame_of_attack_finish = prm_attack_frames;
        p->_beat_frame_of_sustain_finish = p->_beat_frame_of_attack_finish + prm_sustain_frames;
        p->_beat_frame_of_release_finish = p->_beat_frame_of_sustain_finish + prm_release_frames;
        p->_beat_cycle_frames = prm_cycle_frames; //����
        if (prm_beat_num < 0) {
            p->_beat_target_frames = MAX_FRAME;
        } else {
            p->_beat_target_frames = p->_beat_cycle_frames * prm_beat_num;
        }
        //�ŏ��̃A�^�b�N�܂ł̑��x
        const VAL_TYPE val = getValue(prm_idx);
        if (p->_beat_frame_of_attack_finish > 0 ) {
            p->_velo = (VAL_TYPE)( ((double)(p->_bottom - val)) / ((double)(p->_beat_frame_of_attack_finish)) );
        } else if (p->_beat_frame_of_attack_finish == 0 ) {
            p->_velo = p->_bottom - val;
        }
    }

    /**
     * �l�J�ڒ����ǂ������ׂ� .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @return true/false
     */
    virtual bool isTransitioning(int prm_idx) const {
        if (_parameter[prm_idx]._method == NO_TRANSITION) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * �l�J�ڒ����ǂ������ׂ� .
     * @return true/false
     */
    virtual bool isTransitioning() const {
        for (int i = 0; i < N; i++) {
            if (isTransitioning(i)) {
                return true;
            }
        }
        return false;
    }

    virtual void reset() {
        Parameter* p = _parameter;
        for (int i = 0; i < N; i++) {
            p->_velo = 0;
            p->_acce = 0;
            p->_target = 0;
            p->_top = 0;
            p->_bottom = 1;
            p->_beat_frame_of_attack_finish = 0;
            p->_beat_frame_of_sustain_finish = 0;
            p->_beat_frame_of_release_finish = 0;
            p->_beat_cycle_frames = 0;
            p->_beat_target_frames = 0;
            p->_beat_frame_count_in_roop = 0;
            p->_beat_frame_count = 0;
            p->_method = NO_TRANSITION;
            ++p;
        }
    }

    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     * @param s �K�p�J�n�C���f�b�N�X
     * @param n �K�p�C���f�b�N�X��
     */
    virtual void behave(int s = 0, int n = N) {
        Parameter* p = &_parameter[s];
        for (int i = s; i < s+n; i++) {
            const TransitionMethod method = p->_method;
            VAL_TYPE val = getValue(i);
            const VAL_TYPE top = p->_top;
            const VAL_TYPE bottom = p->_bottom;
            p->_beat_frame_count++;
            p->_velo += p->_acce;
            val += p->_velo;

            if (method == NO_TRANSITION) {
                //�������Ȃ�
            } else {
                if (method == TARGET_LINER_TO) {
                    if (p->_beat_frame_count >= p->_beat_target_frames) {
                        val = p->_target;
                        stop(i);//�I��
                    }
                } else if (method == TARGET_LINER_STEP || method == TARGET_ACCELERATION_STEP) {
                    if ((p->_velo > 0  && val >= p->_target) || (p->_velo < 0  && val <= p->_target)) {
                        val = p->_target;
                        stop(i);//�I��
                    }
                } else if (method == BEAT_LINER) {
                    p->_beat_frame_count_in_roop++;
                    const frame cnt = p->_beat_frame_count_in_roop;
                    const frame beat_cycle_frames = p->_beat_cycle_frames;
                    if (cnt == beat_cycle_frames/2) {
                        //�܂�Ԃ�
                        if (p->_velo > 0) { //�R
                            val = top;
                            p->_velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //����̑��x
                        } else if (p->_velo < 0) { //�J
                            val = bottom;
                            p->_velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //���̑��x
                        }
                    }
                    if (cnt == beat_cycle_frames) {
                        //�P���[�v�I��
                        if (p->_velo > 0) { //�R
                            val = top;
                            p->_velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //����̑��x
                        } else if (p->_velo < 0) { //�J
                            val = bottom;
                            p->_velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //���̑��x
                        }
                        p->_beat_frame_count_in_roop = 0;
                    }
                } else if (method == BEAT_TRIANGLEWAVE) {
                    p->_beat_frame_count_in_roop++;
                    const frame cnt = p->_beat_frame_count_in_roop;
                    const frame beat_frame_of_attack_finish = p->_beat_frame_of_attack_finish;
                    //�A�^�b�N�I����
                    if (cnt == beat_frame_of_attack_finish) {
                        val = top;
                        p->_velo = 0;
                    }
                    //�ێ��I��
                    if (cnt == p->_beat_frame_of_sustain_finish) {
                        val = top;
                        frame attenuate_frames = p->_beat_frame_of_release_finish - p->_beat_frame_of_sustain_finish; //����(�]�C)����
                        //�����܂ł̌���(�]�C)���x�ݒ�
                        if (attenuate_frames > 0)  {
                            p->_velo = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                        } else {
                            p->_velo = bottom-top;
                        }
                    }
                    //����(�]�C)�I��
                    if (cnt == p->_beat_frame_of_release_finish) {
                        val = bottom;
                        p->_velo = 0;
                    }
                    //�x�e�I��
                    if (cnt == p->_beat_cycle_frames) {
                        val = bottom;
                        p->_beat_frame_count_in_roop = 0;
                        //���̃A�^�b�N�ւ̑��x�ݒ�
                        if (beat_frame_of_attack_finish > 0 ) {
                            p->_velo = (VAL_TYPE)( ((double)(top - val)) / ((double)beat_frame_of_attack_finish) );
                        } else if (beat_frame_of_attack_finish == 0 ) {
                            p->_velo = top - val;
                        }
                    }
                } else if (method == R_BEAT_TRIANGLEWAVE) { //�t�r�[�g
                    p->_beat_frame_count_in_roop++;
                    const frame cnt = p->_beat_frame_count_in_roop;
                    const frame beat_frame_of_attack_finish = p->_beat_frame_of_attack_finish;
                    //�A�^�b�N�I����
                    if (cnt == beat_frame_of_attack_finish) {
                        val = bottom;
                        p->_velo = 0;
                    }
                    //�ێ�(����)�I��
                    if (cnt == p->_beat_frame_of_sustain_finish) {
                        val = bottom;
                        frame attenuate_frames = p->_beat_frame_of_release_finish - p->_beat_frame_of_sustain_finish; //���A����
                        //����܂ł̕��A���x�ݒ�
                        if (attenuate_frames > 0)  {
                            p->_velo = (VAL_TYPE)( (double)(top - bottom) / ((double)attenuate_frames) );
                        } else {
                            p->_velo = top - bottom;
                        }
                    }
                    //���A�I��
                    if (cnt == p->_beat_frame_of_release_finish) {
                        val = top;
                        p->_velo = 0;
                    }
                    //�x�e�I��
                    if (cnt == p->_beat_cycle_frames) {
                        val = top;
                        p->_beat_frame_count_in_roop = 0;
                        //���̃A�^�b�N�ւ̑��x�ݒ�
                        if (beat_frame_of_attack_finish > 0 ) {
                            p->_velo = (VAL_TYPE)( ((double)(bottom - val)) / ((double)beat_frame_of_attack_finish) );
                        } else if (beat_frame_of_attack_finish == 0 ) {
                            p->_velo = bottom - val;
                        }
                    }
                }
            }


            if (top < val) {
                val = top;
            } else if (bottom > val) {
                val = bottom;
            }

            setValue(i, val); //���f

            if (p->_beat_frame_count >= p->_beat_target_frames) {
                stop(i);//�I��
            }

            ++p;
        }
    }

    virtual ~GgafValueEnveloper() {
    }
};

}

#endif /*GGAFCORE_GGAFVALUEENVELOPER_H_*/

