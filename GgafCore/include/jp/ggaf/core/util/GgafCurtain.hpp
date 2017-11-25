#ifndef GGAFCORE_GGAFCURTAIN_H_
#define GGAFCORE_GGAFCURTAIN_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

enum GgafCurtainState {
    OPEN,
    OPENING,
    OPENED,
    CLOSE,
    CLOSING,
    CLOSED
};

/**
 * �J�[�e�� .
 * �J�[�e�����J���A����̊Ǘ����܂��B<BR>
 * <pre>
 *
 *           |             |         <-- �J�[�e�����[���~�߂��h�����Ă���ʒu
 *           v             v
 *     +-----+------+------+----+    <-- �J�[�e�����[��
 *           +------+
 *           |  �J  |
 *           |  �b  |
 *           |  �e  |
 *           |  ��  |
 *           |      |
 *           +------+
 *
 *
 *     <---------- 1 ----------->
 *     <- 2 ->
 *     <------- 3 --------->
 *     <---- 4 ----->
 *           <----- 5 ----->
 *
 *  1. _curtain_rail_length �i�J�[�e�����[���S�̂̒����j
 *  2. _min_position  (�J�[�e����100% �J�����Ɣ��肳���ʒu�j
 *  3. _max_position  (�J�[�e����100% �������肳���ʒu�j
 *  4. _curtain_position �i���݂̃J�[�e���ʒu�j
 *  5. _moveable_length   (�J�[�e�����͈�(����) = 3 - 2 )
 * </pre>
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafCurtain : public GgafObject {

public:
    /** [r]���݂̃J�[�e���̏�� */
    GgafCurtainState _state;
    /** [r]�J�[�e�����[���̒��� */
    const T _curtain_rail_length;
    /** [r]�J�[�e����100% �J�����Ɣ��肳���ʒu */
    const T _min_position;
    /** [r]�J�[�e����100% �������肳���ʒu */
    const T _max_position;
    /** [r]�J�[�e�����͈�(����) */
    const T _moveable_length;
    /** [r]���݂̃J�[�e���̕܂��Ă��钷�� */
    T _curtain_position;
    /** [r]�J�[�e�����J���ۂ̑��x */
    T _opening_velocity;
    /** [r]�J�[�e����߂�ۂ̑��x */
    T _closing_velocity;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_curtain_rail_length �J�[�e�����[���̒���
     * @param prm_min_position �J�[�e����100% �J�����Ɣ��肳���ʒu
     * @param prm_max_position �J�[�e����100% �������肳���ʒu
     */
    GgafCurtain(T prm_curtain_rail_length,
                T prm_min_position,
                T prm_max_position) : GgafObject(),
    _curtain_rail_length(prm_curtain_rail_length),
    _min_position(prm_min_position),
    _max_position(prm_max_position),
    _moveable_length(_max_position - _min_position)
    {
        _curtain_position = _min_position; //�ŏ���100%�J���Ă��܂�
        _state = OPENED;
        _opening_velocity = 0.0f;
        _closing_velocity = 0.0f;
    }

    /**
     * �J�[�e�������X�ɊJ���� .
     * �{���\�b�h�����s����ƁAbehave() ���Ăяo����邲�Ƃ�
     * prm_opening_velocity �ÂJ�[�e�����J���܂��i�������Z���Ȃ�܂��j�B
     * �J�[�e���̂͒����� 0.0 �܂ł��B���� 0.0  �ɒB����ƁAprocessCloseDone() ��
     * �R�[���o�b�N�� open �͏I�����܂��B
     * @param prm_opening_velocity �J�[�e�����J���鑬�x
     */
    virtual void openV(T prm_opening_velocity) {
        _opening_velocity = prm_opening_velocity;
        _state = OPEN;
    }
    virtual void openT(frame prm_opening_frames) {
        T length = _curtain_position - _min_position;
        openV((T)(length / prm_opening_frames));
    }

    /**
     * �J�[�e���𑦍��ɍő�ɊJ���� .
     * �{���\�b�h�����s����� �J�[�e�����[���̒����� 0.0 �ɂȂ�܂��B
     * processOpenDone() ���P��R�[���o�b�N���܂��B
     */
    virtual void open() {
        _curtain_position = _min_position;
        _state = OPENED;
        processOpenDone();
    }

    /**
     * �J�[�e�������X�ɕ߂� .
     * �{���\�b�h�����s����ƁAbehave() ���Ăяo����邲�Ƃ�
     * prm_closing_velocity �ÂJ�[�e��������Ă䂫�܂��i�����������Ȃ�܂��j�B<BR>
     * �J�[�e�����[���̒����̍ő�̓f�t�H���g�� 1.0 �ł��B
     * �f�t�H���g�ł͒��� 1.0 �ɒB����ƁAprocessCloseDone() ���P��
     * �R�[���o�b�N���Aclose �͏I�����܂��B
     * @param prm_closing_velocity �J�[�e����߂鑬�x
     */
    virtual void closeV(T prm_closing_velocity) {
        _closing_velocity = prm_closing_velocity;
        _state = CLOSE;
    }
    virtual void closeT(frame prm_closing_frames) {
        T length = _moveable_length - (_curtain_position - _min_position);
        closeV((T)(length / prm_closing_frames));
    }

    /**
     * �J�[�e���𑦍��ɕ߂��� .
     * �{���\�b�h�����s����� �J�[�e�����[���̒����� 1.0 �ɂȂ�܂��B
     * processOpenDone() ���P��R�[���o�b�N���܂��B
     */
    virtual void close() {
        _curtain_position = _max_position;
        _state = CLOSED;
        processCloseDone();
    }

    /**
     * �J�[�e���𓮂��� .
     * �{�N���X���@�\������ɂɂ́A���t���[�����̃��\�b�h�����s���Ă��������B
     * ���t���[�� behave() ���邱�ƂŎ��̃��\�b�h���K�X�Ăяo�����悤�ɂȂ�܂��B
     * <code>
     * processOpenBegin()
     * processOpening()
     * processOpenDone()
     * processCloseBegin()
     * processClosing()
     * processCloseDone()
     * </code>
     */
    virtual void behave() {
        if (_state == OPEN) {
            processOpenBegin();
            _state = OPENING;
        } else if (_state == OPENING) {
            _curtain_position -= _opening_velocity;
            if (_curtain_position < _min_position) {
                _curtain_position = _min_position;
                _state = OPENED;
                processOpenDone();
            } else {
                processOpening();
            }

        } else if (_state == CLOSE) {
            processCloseBegin();
            _state = CLOSING;
        } else if (_state == CLOSING) {
            _curtain_position += _closing_velocity;
            if (_curtain_position > _max_position) {
                _curtain_position = _max_position;
                _state = CLOSED;
                processCloseDone();
            } else {
                processClosing();
            }
        }
    }

    /**
     * �J�[�e���̈ʒu�i�܂��Ă������j���擾 .
     * @return �J�[�e���̈ʒu
     */
    virtual T getCurtainPosition() {
        return _curtain_position;
    }

    /**
     * �J�[�e���̕܂��Ă��銄�����擾 .
     * @return �J�[�e���̕܂��Ă��銄��(0.0�F100%�J���Ă��� �` 1.0�F100%�܂��Ă���j
     */
    virtual T getClosingRatio() {
        return (_curtain_position - _min_position) / _moveable_length;
    }

    /**
     * �J�[�e�����J���n�߂�u�Ԃ̏��� .
     * open() ���ɂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpenBegin() {};

    /**
     * �J�[�e�����J���Ă����r���̏��� .
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpening() {};

    /**
     * �J�[�e�����J�����������̏��� .
     * _curtain_position �� 0.0 �ɂȂ����ۂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpenDone() {};

    /**
     * �J�[�e�����܂�n�߂�u�Ԃ̏��� .
     * close() ���ɂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processCloseBegin() {};

    /**
     * �J�[�e�����܂��Ă����r���̏��� .
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processClosing() {};

    /**
     * �J�[�e�����܂������̏��� .
     * _curtain_position �� _curtain_rail_length �ɂȂ����ۂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processCloseDone() {};




    virtual ~GgafCurtain() {

    }
};

}
#endif /*GGAFCORE_GGAFCURTAIN_H_*/
