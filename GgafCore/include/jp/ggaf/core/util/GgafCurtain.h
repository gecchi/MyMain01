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
    /** [r]�J�[�e�������t����V�[�� */
    GgafScene* _pScene;
    /** [r]���݂̃J�[�e���̏�� */
    GgafCurtainState _state;
    /** [r]�J�[�e���̒��� */
    float _curtain_length;
    /** [r]���݂̃J�[�e���̒���(�J���) */
    float _now_curtain_length;
    /** [r]�J�[�e�����J���ۂ̑��x */
    float _opening_velocity;
    /** [r]�J�[�e����߂�ۂ̑��x */
    float _closeing_velocity;

    /**
     * �R���X�g���N�^ .
     * �J�[�e���̒�����1.0�ɐݒ肳��܂��B<BR>
     * �܂��A������Ԃ̓J�[�e���͊J���Ă��܂��B<BR>
     * @param _pScene �J�[�e�������t����V�[��
     * @return
     */
    GgafCurtain(GgafScene* prm_pScene);

    /**
     * �J�[�e�����J���� .
     * @param prm_opening_velocity �J�[�e�����J���鑬�x
     */
    virtual void open(float prm_opening_velocity);

    /**
     * �J�[�e����߂� .
     * @param prm_closeing_velocity �J�[�e����߂鑬�x
     */
    virtual void close(float prm_closeing_velocity);

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
    virtual void processOpenBegin() {}

    /**
     * �J�[�e�����J���Ă����r���̏��� .
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpening() {}

    /**
     * �J�[�e�����J�����������̏��� .
     * _now_curtain_length��0�ɂȂ����ۂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processOpenDone() {}

    /**
     * �J�[�e�����܂�n�߂�u�Ԃ̏��� .
     * close() ���ɂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processCloseBegin() {}

    /**
     * �J�[�e�����܂��Ă����r���̏��� .
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processClosing() {}

    /**
     * �J�[�e�����܂������̏��� .
     * _now_curtain_length �� _curtain_length �ɂȂ����ۂP�x�����Ăяo����܂��B <BR>
     * ���ʂŎ��ۂ̏������������Ă��������B<BR>
     */
    virtual void processCloseDone() {}

    virtual ~GgafCurtain();
};

}
#endif /*GGAFCURTAIN_H_*/
