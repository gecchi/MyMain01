#ifndef GGAFFORMATIONACTOR_H_
#define GGAFFORMATIONACTOR_H_

namespace GgafCore {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafFormation : public GgafActor {
private:



public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[��(addSubLast() callUp() �ɂ�葝��) */
    int _num_sub;
    /** [r]�j��ɂ����ł����A�N�^�[�� (�����A�N�^�[�� informDestroyedFollower() �ɂ�葝��)*/
    int _num_destory;

    frame _offset_frames_end;

    /** �S�Ŏ� true (GgafActor::notifyFormationAboutDestroyed() ���ݒ�) */
    bool _was_all_destroyed;
    bool _is_init;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafFormation(const char* prm_name, frame prm_offset_frames_end);

    void DestroyedFollower(GgafActor* prm_pActor_Destroyed);


    /**
     * �ґ��ɏ��������A�N�^�[���j��ɂ��S�ł����ꍇ�ɌĂяo����郁�\�b�h�i�Ƃ���) .
     * �ґ��S�Ŏ��̋�̓I�ȏ����i�ґ��{�[�i�X���Z��A������ʉ����j�͉��ʂŎ������邱�ƁB <BR>
     * �܂��A�{���\�b�h���@�\���邽�߂ɂ́A�A�N�^�[���Ŏ��g�����ꂽ�ꍇ�ɁA<BR>
     * wasDestroyedFollower() ���Ăяo�������K�{�ł��B <BR>
     * �ґ��S�Ŏ��̏������Ȃ��ꍇ�́Aoverride ����K�v�͂���܂��� �B <BR>
     * @param prm_pActor_LastDestroyed �Ō�ɂ��ꂽ�A�N�^�[
     */
    virtual void onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) = 0;


    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafFormation::onGarbaged() ���Ăяo���ĉ������B
     */
    virtual void onGarbaged() override;

    virtual ~GgafFormation();
};

}
#endif /*GGAFFORMATIONACTOR_H_*/
