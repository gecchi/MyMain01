#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_

namespace GgafCore {

/**
 * �f�|�W�g���Ǘ��̃t�H�[���[�V�����A�N�^�[�N���X .
 * �ґ������o�[�͎g���񂷃t�H�[���[�V�����B
 * processJudgement()�������ς�
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
    /** ����ȏ� callUpUntil() �s�̏ꍇ true */
    bool _is_all_called_up;
    /** �S�Ŏ� true (GgafActor::notifyFormationAboutDestroyed() ���ݒ�) */
    bool _was_all_destroyed;

    /** �\�������o�[�̃X�g�b�J�[�iNULL�̏ꍇ�\�������o�[�͔z���A�N�^�[�̂͂��j */
    GgafCore::GgafActorDepository* _pDepo;
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �t�H�[���[�V�����I�����̗P�\�t���[��
     * @return
     */
    GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * �f�|�W�g�����[�h�ɂ���B
     * GgafFormation �͂Q�̃t�H�[���[�V�����Ǘ����[�h�����݂���B
     * �\�������o�[���A�z���A�N�^�[�ɂ��邩�A�f�|�W�g���ɒu�����ŊǗ����[�h�����肷��B
     * �{���\�b�h�����s���A�\�������o�[�̓������f�|�W�g����ݒ肵���ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�̓f�|�W�g�����[�h�ɂȂ�B
     * �f�|�W�g�����[�h�ł́AaddSubLast �͕s�v�B
     * �����o�[������������ɂ́A��p���\�b�h callUpUntil() ���g�p����K�v������B
     * �����o�[�������I�����́Asayonara() ���g�p�B
     * @param prm_pDepo
     */
    void setFormationAbleActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * �T�u��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() ���A�f�|�W�g���ɖ߂����ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g��������������悤�ɂ��邽�߂�
     * �����ł��B
     * ���ʂ� processJudgement() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * GgafTreeFormation::processJudgement();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processJudgement() override;

    /**
     * �f�|�W�g�����烁���o�[�Ăяo������B .
     * �f�|�W�g�����[�h���Ăяo���\�BsetFormationAbleActorDepository() �̎��O���s���K�v�B
     * �{���\�b�h���Ăяo���ƁA�f�|�W�g���ɊǗ����ꂽ�����o�[����� dispatch() ����܂��B(������ activate() �������)
     * �f�|�W�g���̃����o�[���͊������ꍇ NULL ���Ԃ�܂��B
     * �܂��A������ prm_formation_sub_num �͍ő�ґ��\���v�����ŁA���̐��ȏ�̌Ăяo���ł� NULL ���Ԃ�܂��B
     * ��x�ł� NULL ���Ԃ����ƁA�����t���O isAllCalledUp() �� true �ɂȂ�A�ȍ~�{�t�H�[���[�V�����I�u�W�F�N�g��
     * �����o�[�Ăяo���ł��Ȃ��悤�ɂȂ�܂��B�Ɠ����ɁA processJudgement() �Ŏ����I�� sayonara() ���R�[������
     * �t�H�[���[�V�����I�u�W�F�N�g�͉������܂��B
     * ���ӁB�����[�ɌĂяo���Ă������o�[���m�ۂł��Ȃ��ꍇ���A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�͏I�����Ă��܂��܂��B
     * �\�������o�[��o�^��ɌĂяo���悤�ɂ��ĉ������B
     * @param prm_formation_sub_num �{�t�H�[���[�V�����̍ő�ґ��\���v����
     * @return �ґ��\���v���̃A�N�^�[�B
     *         �ő�ґ��\���v�������I�[�o�[���ČĂяo�����ꍇ�A������
     *         �f�|�W�g���ɍ\���v�����������Ȃ��ꍇ�� NULL
     */
    GgafActor* callUpUntil(int prm_formation_sub_num = INT_MAX);

    bool isAllCalledUp();

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafDepositoryFormation::onEnded() ���Ăяo���ĉ������B
     */
    virtual void onEnded() override;

    /**
     * �f�|�W�g�����[�h�Ǘ��̕ґ��S�Ă� sayonara() �����s����B
     */
    virtual void sayonaraFollwer();

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
