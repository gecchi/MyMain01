#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_

namespace GgafCore {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDepositoryFormation : public GgafFormation {
private:

    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
    }
public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[�̃��X�g */
    GgafCore::GgafLinkedListRing<GgafActor> _listFllower;
    bool _is_called_up;
    bool _is_all_called_up;
    /** �S�Ŏ� true (GgafActor::notifyFormationAboutDestroyed() ���ݒ�) */
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
    GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �f�|�W�g�����[�h�ɂ���B
     * �\�������o�[���A�z���A�N�^�[�ɂ��邩�A�f�|�W�g���ɒu�����ŁA
     * �{�N���X�̓��[�h�����݂���B
     * �{���\�b�h�����s���A�\�������o�[�̓������f�|�W�g����ݒ肵���ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�̓f�|�W�g�����[�h�ɂȂ�B
     * �f�|�W�g�����[�h�ł́AaddSubLast �͕s�v�B
     * �����o�[�Ăяo���ŁAcallUpUntil() ���g�p�\�B
     * @param prm_pDepo
     */
    void setFormationAbleActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * �T�u��������Ύ� .
     * processJudgement() �������ς݂̂��߁A�I�[�o�[���C�h���Ȃ��ŉ������B
     * �ǂ����Ă��I�[�o�[���C�h���K�v�ȏꍇ�́A�������ł̉�������
     * <code>
     * GgafDepositoryFormation::processJudgement();
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
    GgafActor* callUpUntil(int prm_formation_sub_num);


    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafDepositoryFormation::onEnded() ���Ăяo���ĉ������B
     */
    virtual void onEnded() override;

    virtual void sayonaraFollwer();

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
