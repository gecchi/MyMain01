#ifndef GGAFTREEFORMATION_H_
#define GGAFTREEFORMATION_H_

namespace GgafCore {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafTreeFormation : public GgafFormation {
private:

    void sayonaraFollwer();


public:

    /** �S�Ŏ� true (GgafActor::notifyFormationAboutDestroyed() ���ݒ�) */
    bool _was_all_destroyed;
    bool _is_init;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end);


    /**
     * �T�u��������Ύ� .
     * processJudgement() �������ς݂̂��߁A�I�[�o�[���C�h���Ȃ��ŉ������B
     * �ǂ����Ă��I�[�o�[���C�h���K�v�ȏꍇ�́A�������ł̉�������
     * <code>
     * GgafTreeFormation::processJudgement();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processJudgement() override;


    /**
     * �ґ��̃����o�[�̓o�^���܂�.
     * �f�|�W�g�����[�h�ł͂Ȃ��ꍇ�A�\�������o�[�����̃��\�b�h�ɂ�菉���o�^���Ă����K�v������B
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;


    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafTreeFormation::onEnded() ���Ăяo���ĉ������B
     */
    virtual void onEnded() override;

    virtual ~GgafTreeFormation();
};

}
#endif /*GGAFTREEFORMATION_H_*/
