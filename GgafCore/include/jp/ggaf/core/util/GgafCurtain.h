#ifndef GGAFCURTAIN_H_
#define GGAFCURTAIN_H_
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
 * �V�[���̃J�[�e�� .
 * �J�[�e�����J���A����̊Ǘ����܂��B<BR>
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafCurtain : public GgafObject {

public:
    /** [r]���݂̃J�[�e���̏�� */
    GgafCurtainState _state;
    /** [r/w]�J�[�e���̒��� */
    float _curtain_length;
    /** [r]���݂̃J�[�e���̒���(�J���) */
    float _now_curtain_length;
    /** [r]�J�[�e�����J���ۂ̑��x */
    float _opening_velocity;
    /** [r]�J�[�e����߂�ۂ̑��x */
    float _closing_velocity;

    /**
     * �R���X�g���N�^ .
     * �J�[�e���̒����̓f�t�H���g�� 1.0 �ɐݒ肳��܂��B<BR>
     * �܂��A������Ԃ̓J�[�e���͊J���Ă��܂��B<BR>
     * @param prm_curtain_length �J�[�e���̒���(�f�t�H���g 1.0)
     */
    GgafCurtain(float prm_curtain_length = 1.0f);

    /**
     * �J�[�e�������X�ɊJ���� .
     * �{���\�b�h�����s����ƁAbehave() ���Ăяo����邲�Ƃ�
     * prm_opening_velocity �ÂJ�[�e�����J���܂��i�������Z���Ȃ�܂��j�B
     * �J�[�e���̂͒����� 0.0 �܂ł��B���� 0.0  �ɒB����ƁAprocessCloseDone() ��
     * �R�[���o�b�N�� open �͏I�����܂��B
     * @param prm_opening_velocity �J�[�e�����J���鑬�x
     */
    virtual void open(float prm_opening_velocity);

    /**
     * �J�[�e���𑦍��ɍő�ɊJ���� .
     * �{���\�b�h�����s����� �J�[�e���̒����� 0.0 �ɂȂ�܂��B
     * processOpenDone() ���P��R�[���o�b�N���܂��B
     */
    virtual void open();

    /**
     * �J�[�e�������X�ɕ߂� .
     * �{���\�b�h�����s����ƁAbehave() ���Ăяo����邲�Ƃ�
     * prm_closing_velocity �ÂJ�[�e��������Ă䂫�܂��i�����������Ȃ�܂��j�B<BR>
     * �J�[�e���̒����̍ő�̓f�t�H���g�� 1.0 �ł��B
     * �f�t�H���g�ł͒��� 1.0 �ɒB����ƁAprocessCloseDone() ���P��
     * �R�[���o�b�N���Aclose �͏I�����܂��B
     * @param prm_closing_velocity �J�[�e����߂鑬�x
     */
    virtual void close(float prm_closing_velocity);

    /**
     * �J�[�e���𑦍��ɕ߂��� .
     * �{���\�b�h�����s����� �J�[�e���̒����� 1.0 �ɂȂ�܂��B
     * processOpenDone() ���P��R�[���o�b�N���܂��B
     */
    virtual void close();

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
    virtual void behave();

    /**
     * �J�[�e�����J���n�߂�u�Ԃ̏��� .
     * open() ���ɂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpenBegin() = 0;

    /**
     * �J�[�e�����J���Ă����r���̏��� .
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpening() = 0;

    /**
     * �J�[�e�����J�����������̏��� .
     * _now_curtain_length �� 0.0 �ɂȂ����ۂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpenDone() = 0;

    /**
     * �J�[�e�����܂�n�߂�u�Ԃ̏��� .
     * close() ���ɂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processCloseBegin() = 0;

    /**
     * �J�[�e�����܂��Ă����r���̏��� .
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processClosing() = 0;

    /**
     * �J�[�e�����܂������̏��� .
     * _now_curtain_length �� _curtain_length �ɂȂ����ۂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processCloseDone() = 0;


    virtual ~GgafCurtain();
};

}
#endif /*GGAFCURTAIN_H_*/
