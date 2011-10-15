#ifndef GGAFDXFORMATIONACTOR_H_
#define GGAFDXFORMATIONACTOR_H_

namespace GgafDxCore {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDxFormationActor : public GgafDxGeometricActor {
private:

    void sayonaraFollwer();


public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[��(addSubLast() callUp() �ɂ�葝��) */
    int _num_sub;
    /** [r]�j��ɂ����ł����A�N�^�[�� (�����A�N�^�[�� informDestroyedFollower() �ɂ�葝��)*/
    int _num_destory;
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[�̃��X�g */
    GgafCore::GgafLinkedListRing<GgafDxGeometricActor> _listFllower;

    frame _offset_frames_end;
    bool _is_called_up;

    /** �S�Ŏ� true (GgafDxGeometricActor::notifyFormationAboutDestroyed() ���ݒ�) */
    bool _was_all_destroyed;
    bool _is_init;

    /** �\�������o�[�̃X�g�b�J�[�iNULL�̏ꍇ�\�������o�[�͔z���A�N�^�[�̂͂��j */
    GgafCore::GgafActorDepository* _pDepo;
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafDxFormationActor(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �f�|�W�g�����[�h�ɂ���B
     * �\�������o�[���A�z���A�N�^�[�ɂ��邩�A�f�|�W�g���ɒu�����ŁA
     * �{�N���X�̓��[�h�����݂���B
     * �{���\�b�h�����s���A�\�������o�[�̓������f�|�W�g����ݒ肵���ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�̓f�|�W�g�����[�h�ɂȂ�B
     * �f�|�W�g�����[�h�ł́AaddSubLast �͕s�v�B
     * �����o�[�Ăяo���ŁAcallUp() ���g�p�\�B
     * @param prm_pDepo
     */
    void setFormationAbleActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * �T�u��������Ύ� .
     * processJudgement() �������ς݂̂��߁A�I�[�o�[���C�h���Ȃ��ŉ������B
     * �ǂ����Ă��I�[�o�[���C�h���K�v�ȏꍇ�́A�������ł̉�������
     * <code>
     * GgafDxFormationActor::processJudgement();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processJudgement() override;

    /**
     * �f�|�W�g�����烁���o�[�Ăяo������B .
     * �f�|�W�g�����[�h���Ăяo���\�BsetFormationAbleActorDepository() �̎��O���s���K�v�B
     * ���ӁB�����[�ɌĂяo���Ă������o�[���m�ۂł��Ȃ��ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�͏I������B
     * @return
     */
    GgafDxGeometricActor* callUp();

    /**
     * �ґ��̃����o�[�̓o�^���܂�.
     * �f�|�W�g�����[�h�ł͂Ȃ��ꍇ�A�\�������o�[�����̃��\�b�h�ɂ�菉���o�^���Ă����K�v������B
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;

    /**
     * �ґ��ɏ��������A�N�^�[���j��ɂ��S�ł����ꍇ�ɌĂяo����郁�\�b�h�i�Ƃ���) .
     * �ґ��S�Ŏ��̋�̓I�ȏ����i�ґ��{�[�i�X���Z��A������ʉ����j�͉��ʂŎ������邱�ƁB <BR>
     * �܂��A�{���\�b�h���@�\���邽�߂ɂ́A�A�N�^�[���Ŏ��g�����ꂽ�ꍇ�ɁA<BR>
     * wasDestroyedFollower() ���Ăяo�������K�{�ł��B <BR>
     * �ґ��S�Ŏ��̏������Ȃ��ꍇ�́Aoverride ����K�v�͂���܂��� �B <BR>
     * @param prm_pActor_LastDestroyed �Ō�ɂ��ꂽ�A�N�^�[
     */
    virtual void onDestroyedAll(GgafDxGeometricActor* prm_pActor_LastDestroyed) = 0;

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafDxFormationActor::onGarbaged() ���Ăяo���ĉ������B
     */
    virtual void onGarbaged() override;

    virtual ~GgafDxFormationActor();
};

}
#endif /*GGAFDXFORMATIONACTOR_H_*/
