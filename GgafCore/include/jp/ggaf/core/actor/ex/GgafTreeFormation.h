#ifndef GGAFTREEFORMATION_H_
#define GGAFTREEFORMATION_H_

namespace GgafCore {

/**
 * �z���c���[�Ǘ��̃t�H�[���[�V�����Ǘ��N���X .
 * �ґ������o�[�͎g���̂Ẵt�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����AaddSubLast(GgafActor*) �ɂ��
 * �ґ������o�[��ǉ����Ă����Ă��������B
 * processJudgement()�������ς݁B
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafTreeFormation : public GgafFormation {
private:

    void sayonaraFollwer();


public:
    /** �S�Ŏ� true (GgafActor::notifyDestroyedToFormation() ���ݒ�) */
    bool _was_all_destroyed;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end);


    /**
     * �T�u��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() �����ꍇ�A�{�t�H�[���[�V�����I�u�W�F�N�g��������������
     * �悤�ɂ��邽�߂Ɏ����ς݂ł��B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * �ґ��̃����o�[��o�^���܂�.
     * GgafFormation �͂Q�̃t�H�[���[�V�����Ǘ����[�h�����݂���B
     * �\�������o�[���A�z���A�N�^�[�ɂ��邩�A�f�|�W�g���ɒu�����ŊǗ����[�h�����肷��B
     * �{���\�b�h�����s���A�ґ��\�������o�[��z���A�N�^�[�ɐݒ肵���ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�͔z���Ǘ����[�h�ɂȂ�B���̃��[�h�̕ґ������o�[�͎g���̂Ăł���B
     * �z���Ǘ����[�h�́A�\�������o�[�����̃��\�b�h�ɂ�菉���o�^���Ă����K�v������B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * �\�������o�[������������ɂ́A�ʏ�ʂ� activate() ���g�p�B
     * �\�������o�[�������I�����́Asayonara() ���g�p�B
     * @param prm_pSub �ґ��̃����o�[�̃A�N�^�[
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
