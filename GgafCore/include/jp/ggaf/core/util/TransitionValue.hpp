#ifndef GGAF_CORE_TRANSITIONVALUE_H_
#define GGAF_CORE_TRANSITIONVALUE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/Util.h"

namespace GgafCore {

/**
 * �J�ڂ���l�^ .
 * �I�ɔO��̋��ʉ��B
 * @tparam VAL_TYPE �J�ڒl�̃f�[�^�^
 * @version 1.00
 * @since 2021/12/07
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class TransitionValue : public Object {

public:

    /**
     * �J�ڕ��@
     */
    enum TransitionMethod {
        NO_TRANSITION,                 //!< �l�J�ڂȂ�
        TARGET_LINEAR_UNTIL,           //!< �ڕW�l�܂ŕГ������őJ�ځi�t���[�����w��j
        TARGET_LINEAR_STEP,            //!< �ڕW�l�܂ŕГ������őJ�ځi���x�w��j
        BEAT_LINEAR,                   //!< �����l�J�ڂŖڕW�l�܂œ��B�����A�܂����ɖ߂�i�t���[�����w��j
        BEAT_TRIANGLEWAVE,             //!< ��`�g�̔g�`�Œl��J��
        R_BEAT_TRIANGLEWAVE,           //!< �t��`�g�̔g�`�Œl��J��
        TARGET_ACCELERATION_UNTIL,     //!< �Г������l�J�ځi�J�ږڕW�l�w��j
        TARGET_ACCELERATION_UNTIL_VELO,//!< �Г������l�J�ځi�ڕW���x�l�w��j
    };
    /** [r/w]�l */
    VAL_TYPE _t_value;
    /** [r/w]�ڕW�̑J�� */
    VAL_TYPE _target;
    /** [r/w]�J�ڏ���l */
    VAL_TYPE _top;
    /** [r/w]�J�ډ����l */
    VAL_TYPE _bottom;
    /** [r/w]���t���[���̑J�ڂ̑��� */
    VAL_TYPE _velo;
    /** [r/w]���t���[���̑J�ڂ̑����̑��� */
    VAL_TYPE _acce;
    /** [r]�l�J�ڕ��@ */
    TransitionMethod _method;
    /** [r]�r�[�g���A��`�g�̃A�^�b�N�I�����̃t���[�� */
    frame _beat_frame_of_attack_finish;
    /** [r]�r�[�g���A��`�g�̈ێ��I�����̃t���[�� */
    frame _beat_frame_of_sustain_finish;
    /** [r]�r�[�g���A��`�g�̌���(�]�C)�I�����̃t���[�� */
    frame _beat_frame_of_release_finish;
    /** [r]�r�[�g���A��`�g�̔g�`�ł̂P�����̃t���[���� */
    frame _beat_cycle_frames;
    /** [r]�r�[�g���A�l�J�ڂɔ�₷�t���[���� */
    frame _beat_target_frames;
    /** [r]�r�[�g���A�������[�v���J�E���^�[ */
    frame _beat_frame_count_in_roop;
    /** [r]�r�[�g���A�����J�E���^�[ */
    frame _beat_frame_count;

public:
    /**
     * �R���X�g���N�^<BR>
     */
    TransitionValue() : Object() {
        _velo = 0;
        _acce = 0;
        _target = 0;
        _top = 0;
        _bottom = 0;
        _beat_frame_of_attack_finish = 0;
        _beat_frame_of_sustain_finish = 0;
        _beat_frame_of_release_finish = 0;
        _beat_cycle_frames = 0;
        _beat_target_frames = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_count = 0;
        _method = NO_TRANSITION;
    }

    /**
     * �l�J�ڂ̏�������l��ݒ� .
     * @param prm1 �J�ڒl1
     * @param prm2 �J�ڒl2
     */
    virtual void setRange(VAL_TYPE prm1, VAL_TYPE prm2) {
        if (prm1 < prm2) {
            setBottom(prm1);
            setTop(prm2);
        } else {
            setBottom(prm2);
            setTop(prm1);
        }
    }

    /**
     * ����l��ݒ� .
     * @param prm_top ����l
     */
    virtual void setTop(VAL_TYPE prm_top) {
        _top = prm_top;
    }

    /**
     * �����l��ݒ� .
     * @param prm_bottom �����l
     */
    virtual void setBottom(VAL_TYPE prm_bottom) {
        _bottom = prm_bottom;
    }

    /**
     * �l�ɏ���l��ݒ� .
     */
    virtual void setValueTop() {
        _t_value = _top;
    }

    /**
     * �l�ɉ����l��ݒ� .
     */
    virtual void setValueBottom() {
        _t_value = _bottom;
    }

    /**
     * �l�J�ڂ̏���l���擾 .
     * @param prm_idx �ΏۃC���f�b�N�X
     * @return ����l
     */
    virtual VAL_TYPE getTop() const {
        return _top;
    }

    /**
     * �l�J�ڂ̉����l���擾 .
     * @return
     */
    virtual VAL_TYPE getBottom() const {
        return _bottom;
    }

    /**
     * �l�J�ڂ��~������ .
     */
    virtual void stop() {
        _velo = 0;
        _acce = 0;
        _method = NO_TRANSITION;
    }

    /**
     * �Г������l�J�ځi�����t���[�����w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���B
     * @param prm_target_T �J�ږڕW�l
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinearUntil(VAL_TYPE prm_target, frame prm_spend_frame) {
        _beat_frame_count = 0;
        _beat_target_frames = prm_spend_frame;
        _target = prm_target;
        _method = TARGET_LINEAR_UNTIL;
        //�ŏ��̃A�^�b�N�܂ł̑��x
        if (_beat_target_frames > 0 ) {
            _velo = (VAL_TYPE)( ((double)(_target - _t_value)) / ((double)(_beat_target_frames)) );
        } else if (_beat_target_frames == 0 ) {
            _velo = _target - _t_value;
        }
    }

    /**
     * ����J�ڂ֕Г������l�J�ځi�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinearToTop(frame prm_spend_frame) {
        transitionLinearUntil(getTop(), prm_spend_frame);
    }

    /**
     * �����J�ڂ֕Г������l�J�ځi�����t���[�����w��j .
     * @param prm_spend_frame ��₷�t���[����
     */
    virtual void transitionLinearToBottom(frame prm_spend_frame) {
        transitionLinearUntil(getBottom(), prm_spend_frame);
    }

    /**
     * �Г������l�J�ځi�J�ڑ��x�w��j .
     * �ڕW�̑J�ڂֈ�葬�x�Œl�J�ڂ���i�J�ڍ����w��j .
     * @param prm_target �J�ږڕW�l
     * @param prm_velo ���t���[�����Z����J�ڍ���(>0.0)�B���̑J�ڂ��w�肷�鎖�B���Z�����Z���͎������f����B
     */
    virtual void transitionLinearStep(VAL_TYPE prm_target, VAL_TYPE prm_velo) {
        _method = TARGET_LINEAR_STEP;
        _velo = prm_velo;
        _target = prm_target;
        _beat_frame_count = 0;
        _beat_target_frames = MAX_FRAME;
    }

    /**
     * �Г������l�J�ځi�J�ږڕW�l�w��j .
     * �ڕW�̑J�ڂ։����w��Œl�J�ڂ���B
     * �J�ډ����x��0�Ɏw�肷��� transitionLinearStep �Ƃقړ����Ӗ��ɂȂ�B
     * transitionLinearStep �̑�R�����͐������C�ɂ��邱�Ɩ������A�{���\�b�h�͐����̎�������͂��Ȃ��i�ł��Ȃ��j�B
     * �J�ڑ��x�����̏ꍇ�A�J�ږڕW�l�𒴂���ƒl�J�ڏI���B
     * �J�ڑ��x�����̏ꍇ�A�J�ږڕW�l�������ƒl�J�ڏI���B
     * �J�ږڕW�l�ɓ��B����O�ɁA���x�̐������t�]����ƁA���Ԃ�i���ɓ��B�ł��Ȃ��̂Œ��ӁB
     * @param prm_target �J�ږڕW�l
     * @param prm_init_velo �����J�ڑ��x
     * @param prm_acce �J�ډ����x
     */
    virtual void transitionAcceUntil(VAL_TYPE prm_target, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        _method = TARGET_ACCELERATION_UNTIL;
        _target = prm_target;
        _velo = prm_init_velo;
        _acce = prm_acce;
        _beat_frame_count = 0;
        _beat_target_frames = MAX_FRAME;
    }

    /**
     * �Г������l�J�ځi�ڕW���x�l�w��j .
     * �ڕW���x�ɂȂ�܂ł։����w��Œl�J�ڂ��܂��B
     * �ڕW���x�ɓ��B����ƒ�~���܂��B
     * �����x�����̏ꍇ�A���x���^�[�Q�b�g���x���傫���Ȃ�ΏI��
     * �����x�����̏ꍇ�A���x���^�[�Q�b�g���x��菬�����Ȃ�ΏI��
     * �J�ډ����x��0�Ɏw�肷��� �i���ɏI���Ȃ��̂Œ��ӁB
     * @param prm_target_velo  �ڕW���x
     * @param prm_init_velo  �������x
     * @param prm_acce   �����x
     */
    virtual void transitionAcceUntilVelo(VAL_TYPE prm_target_velo, VAL_TYPE prm_init_velo, VAL_TYPE prm_acce) {
        _method = TARGET_ACCELERATION_UNTIL_VELO;
        _target = prm_target_velo;
        _velo = prm_init_velo;
        _acce = prm_acce;
        _beat_frame_count = 0;
        _beat_target_frames = MAX_FRAME;
    }

    /**
     * ���������l�J�ځi�t���[�����w��j
     * ����J�ڂֈ�葬�x�Œl�J�ڂ��A��葬�x�ŉ��J�ڂ֖߂�B
     * ��������[�v�w�肷��B�i�P���[�v�̃t���[�����w��j .
     * @param prm_cycle_frames �P���[�v(�ω����Č��ɖ߂�܂�)�ɔ�₷�t���[��
     * @param prm_beat_num ���[�v�����(1.2��ȂǏ����Ŏw��\�A-1 �łقږ������[�v)
     * @param prm_is_to_top true:���߂�TOP�ɑJ�ڂ���^false:���߂�BOTTOM�ɑJ��
     */
    virtual void transitionLinearLoop(frame prm_cycle_frames, double prm_beat_num, bool prm_is_to_top) {
        _method = BEAT_LINEAR;
        _beat_frame_count = 0;
        _beat_frame_count_in_roop = 0;
        _beat_cycle_frames = prm_cycle_frames;
        if (prm_beat_num < 0) {
            _beat_target_frames = MAX_FRAME;
        } else {
            _beat_target_frames = (frame)(prm_cycle_frames * prm_beat_num);
        }
        if (prm_is_to_top) {
            _velo = (VAL_TYPE)(1.0*(_top - _t_value) / ((int)prm_cycle_frames * 0.5));
            if (ZEROd_EQ(_velo)) {
                _velo = 1; //���ł���΂悢
            }
        } else {
            _velo = (VAL_TYPE)(1.0*(_bottom - _t_value) / ((int)prm_cycle_frames * 0.5));
            if (ZEROd_EQ(_velo)) {
                _velo = -1; //���ł���΂悢
            }
        }
    }

    /**
     * ��`�g�̔g�`�Œl��J�ڂ���B .
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
        _method = BEAT_TRIANGLEWAVE;
        _beat_frame_count = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_of_attack_finish = prm_attack_frames;
        _beat_frame_of_sustain_finish = _beat_frame_of_attack_finish + prm_sustain_frames;
        _beat_frame_of_release_finish = _beat_frame_of_sustain_finish + prm_release_frames;
        _beat_cycle_frames = prm_cycle_frames; //����
        if (prm_beat_num < 0) {
            _beat_target_frames = MAX_FRAME;
        } else {
            _beat_target_frames = (frame)(_beat_cycle_frames * prm_beat_num);
        }
        //�ŏ��̃A�^�b�N�܂ł̑��x
        if (_beat_frame_of_attack_finish > 0 ) {
            _velo = (VAL_TYPE)( ((double)(_top - _t_value)) / ((double)(_beat_frame_of_attack_finish)) );
        } else if (_beat_frame_of_attack_finish == 0 ) {
            _velo = _top - _t_value;
        }
    }

    /**
     * ��`�g�̔g�`�Œl��J�ڂ��� .
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
        _method = R_BEAT_TRIANGLEWAVE;
        _beat_frame_count = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_of_attack_finish = prm_attack_frames;
        _beat_frame_of_sustain_finish = _beat_frame_of_attack_finish + prm_sustain_frames;
        _beat_frame_of_release_finish = _beat_frame_of_sustain_finish + prm_release_frames;
        _beat_cycle_frames = prm_cycle_frames; //����
        if (prm_beat_num < 0) {
            _beat_target_frames = MAX_FRAME;
        } else {
            _beat_target_frames = (frame)(_beat_cycle_frames * prm_beat_num);
        }
        //�ŏ��̃A�^�b�N�܂ł̑��x
        if (_beat_frame_of_attack_finish > 0 ) {
            _velo = (VAL_TYPE)( ((double)(_bottom - _t_value)) / ((double)(_beat_frame_of_attack_finish)) );
        } else if (_beat_frame_of_attack_finish == 0 ) {
            _velo = _bottom - _t_value;
        }
    }

    /**
     * �l�J�ڒ����ǂ������ׂ� .
     * @return true/false
     */
    virtual bool isTransitioning() const {
        if (_method == NO_TRANSITION) {
            return false;
        } else {
            return true;
        }
    }

    virtual void reset() {
        _velo = 0;
        _acce = 0;
        _target = 0;
        _top = 0;
        _bottom = 1;
        _beat_frame_of_attack_finish = 0;
        _beat_frame_of_sustain_finish = 0;
        _beat_frame_of_release_finish = 0;
        _beat_cycle_frames = 0;
        _beat_target_frames = 0;
        _beat_frame_count_in_roop = 0;
        _beat_frame_count = 0;
        _method = NO_TRANSITION;
    }

    /**
     * ���t���[���̐U�镑�����\�b�h�B<BR>
     * �{�N���X�̋@�\�𗘗p����ꍇ�́A���̃��\�b�h��<BR>
     * ���t���[�����s���邱�Ƃ��K�v�B
     */
    virtual void behave() {
        const TransitionMethod method = _method;
        VAL_TYPE val = _t_value;
        const VAL_TYPE top = _top;
        const VAL_TYPE bottom = _bottom;
        _beat_frame_count++;
        _velo += _acce;
        val += _velo;

        switch (method) {
            case NO_TRANSITION: {
                //�������Ȃ�
                break;
            }
            case TARGET_LINEAR_UNTIL: {
                if (_beat_frame_count >= _beat_target_frames) {
                    val = _target;
                    stop();//�I��
                }
                break;
            }
            case TARGET_LINEAR_STEP: {
                if ((_velo > 0  && val >= _target) || (_velo < 0  && val <= _target)) {
                    val = _target;
                    stop();//�I��
                }
                break;
            }
            case TARGET_ACCELERATION_UNTIL: {
                if ((_velo > 0  && val >= _target) || (_velo < 0  && val <= _target)) {
                    val = _target;
                    stop();//�I��
                }
                break;
            }
            case TARGET_ACCELERATION_UNTIL_VELO: {
                if ((_acce > 0  && _velo >= _target) || (_acce < 0  && _velo <= _target)) {
                   //�����x�����̏ꍇ�A���x���^�[�Q�b�g���x���傫���Ȃ�ΏI��
                   //�����x�����̏ꍇ�A���x���^�[�Q�b�g���x��菬�����Ȃ�ΏI��
                   val -= _velo;
                   _velo = _target;
                   val += _velo;
                   stop();//�I��
                }
                break;
            }
            case BEAT_LINEAR: {
                _beat_frame_count_in_roop++;
                const frame cnt = _beat_frame_count_in_roop;
                const frame beat_cycle_frames = _beat_cycle_frames;
                if (cnt == beat_cycle_frames/2) {
                    //�܂�Ԃ�
                    if (_velo > 0) { //�R
                        val = top;
                        _velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //����̑��x
                    } else if (_velo < 0) { //�J
                        val = bottom;
                        _velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //���̑��x
                    }
                }
                if (cnt == beat_cycle_frames) {
                    //�P���[�v�I��
                    if (_velo > 0) { //�R
                        val = top;
                        _velo = (VAL_TYPE)( (2.0*(bottom-top)) / ((double)beat_cycle_frames) ); //����̑��x
                    } else if (_velo < 0) { //�J
                        val = bottom;
                        _velo = (VAL_TYPE)( (2.0*(top-bottom)) / ((double)beat_cycle_frames) ); //���̑��x
                    }
                    _beat_frame_count_in_roop = 0;
                }
                break;
            }
            case BEAT_TRIANGLEWAVE: {
                _beat_frame_count_in_roop++;
                const frame cnt = _beat_frame_count_in_roop;
                const frame beat_frame_of_attack_finish = _beat_frame_of_attack_finish;
                //�A�^�b�N�I����
                if (cnt == beat_frame_of_attack_finish) {
                    val = top;
                    _velo = 0;
                }
                //�ێ��I��
                if (cnt == _beat_frame_of_sustain_finish) {
                    val = top;
                    int attenuate_frames = (int)_beat_frame_of_release_finish - (int)_beat_frame_of_sustain_finish; //����(�]�C)����
                    //�����܂ł̌���(�]�C)���x�ݒ�
                    if (attenuate_frames > 0)  {
                        _velo = (VAL_TYPE)( (double)(bottom-top) / ((double)attenuate_frames) );
                    } else {
                        _velo = bottom-top;
                    }
                }
                //����(�]�C)�I��
                if (cnt == _beat_frame_of_release_finish) {
                    val = bottom;
                    _velo = 0;
                }
                //�x�e�I��
                if (cnt == _beat_cycle_frames) {
                    val = bottom;
                    _beat_frame_count_in_roop = 0;
                    //���̃A�^�b�N�ւ̑��x�ݒ�
                    if (beat_frame_of_attack_finish > 0 ) {
                        _velo = (VAL_TYPE)( ((double)(top - val)) / ((double)beat_frame_of_attack_finish) );
                    } else if (beat_frame_of_attack_finish == 0 ) {
                        _velo = top - val;
                    }
                }
                break;
            }
            case R_BEAT_TRIANGLEWAVE: {
                _beat_frame_count_in_roop++;
                const frame cnt = _beat_frame_count_in_roop;
                const frame beat_frame_of_attack_finish = _beat_frame_of_attack_finish;
                //�A�^�b�N�I����
                if (cnt == beat_frame_of_attack_finish) {
                    val = bottom;
                    _velo = 0;
                }
                //�ێ�(����)�I��
                if (cnt == _beat_frame_of_sustain_finish) {
                    val = bottom;
                    int attenuate_frames = (int)_beat_frame_of_release_finish - (int)_beat_frame_of_sustain_finish; //���A����
                    //����܂ł̕��A���x�ݒ�
                    if (attenuate_frames > 0)  {
                        _velo = (VAL_TYPE)( (double)(top - bottom) / ((double)attenuate_frames) );
                    } else {
                        _velo = top - bottom;
                    }
                }
                //���A�I��
                if (cnt == _beat_frame_of_release_finish) {
                    val = top;
                    _velo = 0;
                }
                //�x�e�I��
                if (cnt == _beat_cycle_frames) {
                    val = top;
                    _beat_frame_count_in_roop = 0;
                    //���̃A�^�b�N�ւ̑��x�ݒ�
                    if (beat_frame_of_attack_finish > 0 ) {
                        _velo = (VAL_TYPE)( ((double)(bottom - val)) / ((double)beat_frame_of_attack_finish) );
                    } else if (beat_frame_of_attack_finish == 0 ) {
                        _velo = bottom - val;
                    }
                }
                break;
            }

            default:
                break;
        }

        if (top < val) {
            val = top;
        } else if (bottom > val) {
            val = bottom;
        }
        _t_value = val; //���f
        if (_beat_frame_count >= _beat_target_frames) {
            stop();//�I��
        }
    }

    virtual ~TransitionValue() {
    }
};

}

#endif /*GGAF_CORE_TRANSITIONVALUE_H_*/

