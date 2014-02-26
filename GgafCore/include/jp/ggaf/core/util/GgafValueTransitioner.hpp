#ifndef GGAFCORE_GGAFVALUETRANSITIONER_H_
#define GGAFCORE_GGAFVALUETRANSITIONER_H_
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "GgafCommonHeader.h"

namespace GgafCore {

/**
 * �l�̑J�ڃw���p�[ .
 * @version 1.00
 * @since 2014/02/19
 * @author Masatoshi Tsuge
 */
template <class VAL_TYPE, int N>
class GgafValueTransitioner : public GgafObject {
    enum TransitionMethod {
        NO_TRANSITION,
        TARGET_LINER_TO,
        TARGET_LINER_STEP,
        BEAT_LINER,
        BEAT_TRIANGLEWAVE,
        BEAT_TRIGONOMETRIC,
        TARGET_ACCELERATION_STEP,
    };
public:
    /** [r/w]�e���̖ڕW�̑J�� */
    VAL_TYPE _target[N];
    /** [r/w]�e���̑J�ڏ�� */
    VAL_TYPE _top[N];
    /** [r/w]�e���̑J�ډ��� */
    VAL_TYPE _bottom[N];
    /** [r/w]�e���̖��t���[���̑J�ڂ̑��� */
    VAL_TYPE _velo[N];
    /** [r/w]�e���̖��t���[���̑J�ڂ̑����̑��� */
    VAL_TYPE _acce[N];
    /** [r]�e���̒l�J�ڕ��@ */
    TransitionMethod _method[N];
    /** [r]�r�[�g���A�e���̎O�p�g�̔g�`�Œl�J�ڂ̃A�^�b�N�t���[���� */
    frame _beat_frame_of_attack_finish[N];
    frame _beat_frame_of_sustain_finish[N];
    /** [r]�r�[�g���A�e���̃A�^�b�N���牺���܂ł̃t���[���� */
    frame _beat_frame_of_attenuate_finish[N];
    /** [r]�r�[�g���A�e���̎O�p�g�̔g�`�Œl�J�ڂ̃��X�g�t���[���� */
    frame _beat_roop_frames[N];
    /** [r]�r�[�g���A�e���̒l�J�ڂɔ�₷�t���[���� */
    frame _beat_target_frames[N];
    /** [r]�r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count_in_roop[N];
    /** [r]�r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count[N];

protected:
    /**
     * �l���擾����i�v�����j .
     * @param idx
     * @return
     */
    virtual VAL_TYPE getValue(int idx) = 0;

    /**
     * �l��ݒ肷��i�v�����j .
     * @param idx
     * @param value
     */
    virtual void setValue(int idx, VAL_TYPE value) = 0;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�p�Ώۂ�Actor
     */
    GgafValueTransitioner() : GgafObject() {
        for (int i = 0; i < N; i++) {
            _velo[i] = 0;
            _acce[i] = 0;
            _target[i] = 0;
            _top[i] = 0;
            _bottom[i] = 0;
            _beat_frame_of_attack_finish[i] = 0;
            _beat_frame_of_sustain_finish[i] = 0;
            _beat_frame_of_attenuate_finish[i] = 0;
            _beat_roop_frames[i] = 0;
            _beat_target_frames[i] = 0;
            _beat_frame_count_in_roop[i] = 0;
            _beat_frame_count[i] = 0;
            _method[i] = NO_TRANSITION;
        }
    }

    /**
     * �X�P�[���[�ɂ��J�ڂ̏��������ݒ�i�S���w��j .
     * �����̑召�͋C�ɂ����n����(�����Ŏ�������)
     * @param prm1 �J�ڒl1
     * @param prm2 �J�ڒl2
     */
    void forceRange(VAL_TYPE prm1, VAL_TYPE prm2) {
        for (int i = 0; i < N; i++) {
            forceRange(i, prm1, prm2);
        }
    }

    /**
     * �X�P�[���[�ɂ��J�ڂ̏��������ݒ�i���P�ʂŎw��j
     * @param prm_idx ��
     * @param prm1 �J�ڒl1
     * @param prm2 �J�ڒl2
     */
    void forceRange(int prm_idx, VAL_TYPE prm1, VAL_TYPE prm2) {
        if (prm1 < prm2) {
            _bottom[prm_idx] = prm1;
            _top[prm_idx] = prm2;
        } else {
            _bottom[prm_idx] = prm2;
            _top[prm_idx] = prm1;
        }
    }

    virtual VAL_TYPE getTop(int prm_idx)  {
        return _top[prm_idx];
    }
    virtual VAL_TYPE getBottom(int prm_idx)  {
        return _bottom[prm_idx];
    }

    virtual VAL_TYPE getTop() {
        return MIN3(_top[0], _top[1], _top[2]);
    }
    virtual VAL_TYPE getBottom() {
        return MAX3(_bottom[0],_bottom[1],_bottom[2]);
    }
    /**
     * �l�J�ڂ��~������B �i�S���w��j .
     */
    virtual void stop() {
        for (int i = 0; i < N; i++) {
            stop(i);
        }
    }

    /**
     * �l�J�ڂ��~������B �i���P�ʂŎw��j.
     * @param prm_idx
     */
    virtual void stop(int prm_idx) {
        _velo[prm_idx] = 0;
        _acce[prm_idx] = 0;
        _method[prm_idx] = NO_TRANSITION;
    }

    /**
     * �Г������l�J�ځi�S���E�����t���[�����w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���
     * @param prm_target_T �ڕW�J��
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        for (int i = 0; i < N; i++) {
            transitionLinerUntil(i, prm_target, prm_spend_frame);
        }
    }

    /**
     * �Г������l�J�ځi���P�ʁE�����t���[�����w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���B
     * @param prm_idx ��
     * @param prm_target_T �ڕW�J��
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerUntil(int prm_idx, VAL_TYPE prm_target, frame prm_spend_frame) {
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = prm_spend_frame;
        _target[prm_idx] = prm_target;
        _method[prm_idx] = TARGET_LINER_TO;
        //�ŏ��̃A�^�b�N�܂ł̑��x
        VAL_TYPE val = getValue(prm_idx);
        if (_beat_target_frames[prm_idx] > 0 ) {
            _velo[prm_idx] = (VAL_TYPE)( ((double)(_target[prm_idx] - val)) / ((double)(_beat_target_frames[prm_idx])) );
        } else if (_beat_target_frames[prm_idx] == 0 ) {
            _velo[prm_idx] = _target[prm_idx] - val;
        }
    }

    /**
     * ����J�ڂ֕Г������l�J�ځi�S���E�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerToTop(frame prm_spend_frame) {
        transitionLinerUntil(MIN3(_top[0],_top[1],_top[2]), prm_spend_frame);
    }

    /**
     * �����J�ڂ֕Г������l�J�ځi�S���E�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinerToBottom(frame prm_spend_frame) {
        transitionLinerUntil(MAX3(_bottom[0],_bottom[1],_bottom[2]), prm_spend_frame);
    }


    /**
     * �Г������l�J�ځi�S���E�J�ڑ��x�w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���
     * @param prm_target_T �ڕW�J��
     * @param prm_velo_T ���t���[�����Z����J�ڍ���(>0.0)�B���̑J�ڂ��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    virtual void transitionLinerStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        for (int i = 0; i < N; i++) {
            transitionLinerStep(i, prm_target, prm_velo);
        }
    }

    /**
     * �Г������l�J�ځi���P�ʁE�J�ڑ��x�w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���i�J�ڍ����w��j .
     * @param prm_idx ��
     * @param prm_target_T �ڕW�J��
     * @param prm_velo_T ���t���[�����Z����J�ڍ���(>0.0)�B���̑J�ڂ��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    virtual void transitionLinerStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        _method[prm_idx] = TARGET_LINER_STEP;
        _velo[prm_idx] = prm_velo;
        _target[prm_idx] = prm_target;
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = MAX_FRAME;
    }

    /**
     * �Г������l�J�ځi�S���E�J�ڑ��x�E�J�ډ����x�w��j .
     * �ڕW�̑J�ڂ։����w��Œl�J�ڂ���
     * �J�ډ����x��0�Ɏw�肷��� transitionLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * transitionLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * �J�ډ����x�����̏ꍇ�A�ڕW�J�ڂ𒴂���ƒl�J�ڏI���B
     * �J�ډ����x�����̏ꍇ�A�ڕW�J�ڂ������ƒl�J�ڏI���B
     * @param prm_target_T �ڕW�J��
     * @param prm_velo_T �����J�ڑ��x
     * @param prm_acce_T �J�ډ����x
     */
    virtual void transitionAcceStep(VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        for (int i = 0; i < N; i++) {
            transitionAcceStep(i, prm_target, prm_velo, prm_acce);
        }
    }

    /**
     * �Г������l�J�ځi���P�ʁE�J�ڑ��x�E�J�ډ����x�w��j .
     * �ڕW�̑J�ڂ։����w��Œl�J�ڂ���i�J�ڑ��x�A�J�ډ����x���w��j .
     * �J�ډ����x��0�Ɏw�肷��� transitionLinerStep �Ƃقړ����Ӗ��ɂȂ�B
     * transitionLinerStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * @param prm_idx ��
     * @param prm_target_T �ڕW�J��
     * @param prm_velo_T �����J�ڑ��x
     * @param prm_acce_T �J�ډ����x
     */
    virtual void transitionAcceStep(int prm_idx, VAL_TYPE prm_target, VAL_TYPE prm_velo, VAL_TYPE prm_acce) {
        _method[prm_idx] = TARGET_ACCELERATION_STEP;
        _target[prm_idx] = prm_target;
        _velo[prm_idx] = prm_velo;
        _acce[prm_idx] = prm_acce;
        _beat_frame_count[prm_idx] = 0;
        _beat_target_frames[prm_idx] = MAX_FRAME;
    }

    /**
     * ���������l�J�ځi�S���E�t���[�����w��j .
     * ����J�ڂֈ�葬�x�Œl�J�ڂ��A��葬�x�ŉ��J�ڂ֖߂�B��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_roop_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(1.2��ȂǏ����Ŏw��\�A-1 �łقږ������[�v)
     * @param prm_is_to_top true:���߂�TOP�ɑJ�ڂ���^false:���߂�BOTTOM�ɑJ��
     */
    void transitionLinerLoop(frame prm_roop_frames, double prm_beat_num, bool prm_is_to_top) {
        for (int i = 0; i < N; i++) {
            transitionLinerLoop(i, prm_roop_frames, prm_beat_num, prm_is_to_top);
        }
    }

    /**
     * ���������l�J�ځi���P�ʁE�t���[�����w��j
     * ����J�ڂֈ�葬�x�Œl�J�ڂ��A��葬�x�ŉ��J�ڂ֖߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_idx ��
     * @param prm_roop_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(1.2��ȂǏ����Ŏw��\�A-1 �łقږ������[�v)
     * @param prm_is_to_top true:���߂�TOP�ɑJ�ڂ���^false:���߂�BOTTOM�ɑJ��
     */
    virtual void transitionLinerLoop(int prm_idx, frame prm_roop_frames, double prm_beat_num, bool prm_is_to_top) {
        VAL_TYPE val = getValue(prm_idx);
        _method[prm_idx] = BEAT_LINER;
        _beat_frame_count[prm_idx] = 0;
        _beat_frame_count_in_roop[prm_idx] = 0;
        _beat_roop_frames[prm_idx] = prm_roop_frames;
        if (prm_beat_num < 0) {
            _beat_target_frames[prm_idx] = MAX_FRAME;
        } else {
            _beat_target_frames[prm_idx] = prm_roop_frames * prm_beat_num;
        }
        if (prm_is_to_top) {
            _velo[prm_idx] = 1.0*(_top[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
            if (ZEROd_EQ(_velo[prm_idx])) {
                _velo[prm_idx] = 1; //���ł���΂悢
            }
        } else {
            _velo[prm_idx] = 1.0*(_bottom[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
            if (ZEROd_EQ(_velo[prm_idx])) {
                _velo[prm_idx] = -1; //���ł���΂悢
            }
        }
    }


//    virtual void transitionTrigonometricLoop(int prm_idx, frame prm_roop_frames, double prm_beat_num, bool prm_is_to_top) {
//        VAL_TYPE val = getValue(prm_idx);
//        _method[prm_idx] = BEAT_TRIGONOMETRIC;
//        _beat_frame_count[prm_idx] = 0;
//        _beat_frame_count_in_roop[prm_idx] = 0;
//        _beat_roop_frames[prm_idx] = prm_roop_frames;
//        if (prm_beat_num < 0) {
//            _beat_target_frames[prm_idx] = MAX_FRAME;
//        } else {
//            _beat_target_frames[prm_idx] = prm_roop_frames * prm_beat_num;
//        }
//        if (prm_is_to_top) {
//            _velo[prm_idx] = 1.0*(_top[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
//            if (ZEROd_EQ(_velo[prm_idx])) {
//                _velo[prm_idx] = 1; //���ł���΂悢
//            }
//        } else {
//            _velo[prm_idx] = 1.0*(_bottom[prm_idx] - val) / ((int)prm_roop_frames / 2.0);
//            if (ZEROd_EQ(_velo[prm_idx])) {
//                _velo[prm_idx] = -1; //���ł���΂悢
//            }
//        }
//    }

    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B�i�S���w��j.
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
     * �C �����t���[����<BR>
     * �D �J�ڏ��(_top[��] �z�񂪕ێ�)<BR>
     * �E �J�ډ���(_bottom[��] �z�񂪕ێ�)<BR>
     * ���̓� �@�`�C�������Őݒ�A�D�E��forceRange()�̐ݒ�l���g�p�����B<BR>
     * @param prm_roop_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_sustain_frames ��}�ŇB�̃t���[����
     * @param prm_attenuate_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    virtual void beat(frame prm_roop_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_attenuate_frames,
                      double prm_beat_num) {
        for (int i = 0; i < N; i++) {
            beat(i, prm_roop_frames, prm_attack_frames, prm_sustain_frames, prm_attenuate_frames, prm_beat_num);
        }
    }

    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B�i���ʎw��j.
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
     * �C �����t���[����<BR>
     * �D �J�ڏ��(_top[��] �z�񂪕ێ�)<BR>
     * �E �J�ډ���(_bottom[��] �z�񂪕ێ�)<BR>
     * ���̓� �@�`�C�������Őݒ�A�D�E��forceRange()�̐ݒ�l���g�p�����B<BR>
     * @param prm_idx ��
     * @param prm_roop_frames ��}�Ň@�̃t���[����
     * @param prm_attack_frames ��}�ŇA�̃t���[����
     * @param prm_sustain_frames ��}�ŇB�̃t���[����
     * @param prm_attenuate_frames ��}�ŇC�̃t���[����
     * @param prm_beat_num ���[�v��(-1�Ŗ���)
     */
    virtual void beat(int prm_idx,
                      frame prm_roop_frames,
                      frame prm_attack_frames,
                      frame prm_sustain_frames,
                      frame prm_attenuate_frames,
                      double prm_beat_num) {
        _method[prm_idx] = BEAT_TRIANGLEWAVE;
        _beat_frame_count[prm_idx] = 0;
        _beat_frame_count_in_roop[prm_idx] = 0;
        _beat_frame_of_attack_finish[prm_idx] = prm_attack_frames;
        _beat_frame_of_sustain_finish[prm_idx] = _beat_frame_of_attack_finish[prm_idx] + prm_sustain_frames;
        _beat_frame_of_attenuate_finish[prm_idx] = _beat_frame_of_sustain_finish[prm_idx] + prm_attenuate_frames;
        _beat_roop_frames[prm_idx] = prm_roop_frames; //����
        if (prm_beat_num < 0) {
            _beat_target_frames[prm_idx] = MAX_FRAME;
        } else {
            _beat_target_frames[prm_idx] = _beat_roop_frames[prm_idx] * prm_beat_num;
        }
        //�ŏ��̃A�^�b�N�܂ł̑��x
        VAL_TYPE val = getValue(prm_idx);
        if (_beat_frame_of_attack_finish[prm_idx] > 0 ) {
            _velo[prm_idx] = (VAL_TYPE)( ((double)(_top[prm_idx] - val)) / ((double)(_beat_frame_of_attack_finish[prm_idx])) );
        } else if (_beat_frame_of_attack_finish[prm_idx] == 0 ) {
            _velo[prm_idx] = _top[prm_idx] - val;
        }
    }

    /**
     * �l�J�ڒ����ǂ������ׂ� .
     * @param prm_idx ��
     * @return true/false
     */
    virtual bool isTransitioning(int prm_idx) {
        if (_method[prm_idx] == NO_TRANSITION) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * �l�J�ڒ����ǂ������ׂ� .
     * @return true/false
     */
    virtual bool isTransitioning() {
        for (int i = 0; i < N; i++) {
            if (_method[i] != NO_TRANSITION) {
                return true;
            }
        }
        return false;
    }

    virtual void reset() {
        for (int i = 0; i < N; i++) {
            _velo[i] = 0;
            _acce[i] = 0;
            _target[i] = 0;
            _top[i] = 0;
            _bottom[i] = 1;
            _beat_frame_of_attack_finish[i] = 0;
            _beat_frame_of_sustain_finish[i] = 0;
            _beat_frame_of_attenuate_finish[i] = 0;
            _beat_roop_frames[i] = 0;
            _beat_target_frames[i] = 0;
            _beat_frame_count_in_roop[i] = 0;
            _beat_frame_count[i] = 0;
            _method[i] = NO_TRANSITION;
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

        for (int i = s; i < s+n; i++) {
            TransitionMethod method = _method[i];
            VAL_TYPE val = getValue(i);
            VAL_TYPE top = _top[i];
            VAL_TYPE bottom = _bottom[i];
            _beat_frame_count[i]++;
            _velo[i] += _acce[i];
            val += _velo[i];

            if (method == NO_TRANSITION) {
                //�������Ȃ�
            } else {
                if (method == TARGET_LINER_TO) {
                    if (_beat_frame_count[i] == _beat_target_frames[i]) {
                        val = _target[i];
                        stop(i);//�I��
                    }
                } else if (method == TARGET_LINER_STEP || method == TARGET_ACCELERATION_STEP) {
                    if ((_velo[i] > 0  && val >= _target[i]) || (_velo[i] < 0  && val <= _target[i])) {
                        val = _target[i];
                        stop(i);//�I��
                    }
                } else if (method == BEAT_LINER) {
                    _beat_frame_count_in_roop[i]++;
                    frame cnt = _beat_frame_count_in_roop[i];
                    if (cnt == _beat_roop_frames[i]/2) {
                        //�܂�Ԃ�
                        if (_velo[i] > 0) { //�R
                            val = top;
                            _velo[i] = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)_beat_roop_frames[i]) ); //����̑��x
                        } else if (_velo[i] < 0) { //�J
                            val = bottom;
                            _velo[i] = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)_beat_roop_frames[i]) ); //���̑��x
                        }
                    }
                    if (cnt == _beat_roop_frames[i]) {
                        //�P���[�v�I��
                        if (_velo[i] > 0) { //�R
                            val = top;
                            _velo[i] = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)_beat_roop_frames[i]) ); //����̑��x
                        } else if (_velo[i] < 0) { //�J
                            val = bottom;
                            _velo[i] = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)_beat_roop_frames[i]) ); //���̑��x
                        }
                        _beat_frame_count_in_roop[i] = 0;
                    }
                } else if (method == BEAT_TRIGONOMETRIC) {
//                    _beat_frame_count_in_roop[i]++;
//                    frame cnt = _beat_frame_count_in_roop[i];
//                    angle p = (double)cnt / (double)_beat_roop_frames[i]
//                    val =(-ANG_COS(p) + 1.0) * (top-bottom)
                } else if (method == BEAT_TRIANGLEWAVE) {
                    _beat_frame_count_in_roop[i]++;
                    frame cnt = _beat_frame_count_in_roop[i];
                    //�A�^�b�N�I����
                    if (cnt == _beat_frame_of_attack_finish[i]) {
                        val = top;
                        _velo[i] = 0;
                    }
                    //�ێ��I��
                    if (cnt == _beat_frame_of_sustain_finish[i]) {
                        val = top;
                        frame attenuate_frames = _beat_frame_of_attenuate_finish[i] - _beat_frame_of_sustain_finish[i]; //��������
                        //�����܂ł̌������x�ݒ�
                        if (attenuate_frames > 0)  {
                            _velo[i] = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                        } else {
                            _velo[i] = bottom-top;
                        }
                    }
                    //�����I��
                    if (cnt == _beat_frame_of_attenuate_finish[i]) {
                        val = bottom;
                        _velo[i] = 0;
                    }
                    //�x�e�I��
                    if (cnt == _beat_roop_frames[i]) {
                        val = bottom;
                        _beat_frame_count_in_roop[i] = 0;
                        //���̃A�^�b�N�ւ̑��x�ݒ�
                        if (_beat_frame_of_attack_finish[i] > 0 ) {
                            _velo[i] = (VAL_TYPE)( ((double)(top - val)) / ((double)_beat_frame_of_attack_finish[i]) );
                        } else if (_beat_frame_of_attack_finish[i] == 0 ) {
                            _velo[i] = 0;
                            val = top;
                        }
                    }
                }
            }

            if (top < val) {
                val = top;
            } else if (bottom >  val) {
                val =  bottom;
            }

            setValue(i, val); //���f

            if (_beat_frame_count[i] == _beat_target_frames[i]) {
                stop(i);//�I��
            }
        }

    }

    virtual ~GgafValueTransitioner() {

    }
};


}
#endif /*GGAFCORE_GGAFVALUETRANSITIONER_H_*/

