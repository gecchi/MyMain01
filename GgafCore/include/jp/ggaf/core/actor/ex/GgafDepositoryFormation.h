#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_

namespace GgafCore {

/**
 * �f�|�W�g���Ǘ��̃t�H�[���[�V�����Ǘ��[�N���X .
 * �ґ������o�[�͎g���񂷃t�H�[���[�V�����B
 * �g�p����ꍇ�́A�{�N���X���p�����A
 * setFormationMemberDepo(GgafActorDepository*) �ɂ��
 * �ґ������o�[�����̃f�|�W�g���I�u�W�F�N�g��o�^���Ă��������B
 * processJudgement()�������ς�
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDepositoryFormation : public GgafFormation {
private:
//    /**
//     * �g�p�s�� .
//     * @param prm_pSub
//     */
//    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
//        throwGgafCriticalException("GgafDepositoryFormation::addSubLast() �͎g�p�s�ł��B");
//    }

public:
    /** [r]�ґ��v�f�Ƃ��ĊǗ�����Ă���A�N�^�[�̃��X�g */
    GgafCore::GgafLinkedListRing<GgafActor> _listFollower;
    /** [r]����ȏ� callUpMember() �s�̏ꍇ true */
    bool _can_call_up;
    /** [r]�S�Ŏ� true (GgafActor::notifyDestroyedToFormation() ���ݒ�) */
    bool _was_all_destroyed;
    /** [r]�\�������o�[�̃X�g�b�J�[�inullptr�̏ꍇ�\�������o�[�͔z���A�N�^�[�̂͂��j */
    GgafCore::GgafActorDepository* _pDepo;

public:
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
     * �����o�[������������ɂ́A��p���\�b�h callUpMember() ���g�p����K�v������B
     * �����o�[�������I�����́Asayonara() ���g�p�B
     * @param prm_pDepo
     */
    void setFormationMemberDepo(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * �T�u��������Ζ{�I�u�W�F�N�g����Ƃ������� .
     * �\�������o�[���S�� sayonara() ���A�f�|�W�g���ɖ߂����ꍇ�A
     * �{�t�H�[���[�V�����I�u�W�F�N�g��������������悤�ɂ��邽�߂�
     * �����ł��B
     * ���ʂ� processFinal() �̏������K�v�ȏꍇ�́A
     * �I�[�o�[���C�h���āA���̏������ł̉�������
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * ���Ăяo���Ă��������A
     */
    virtual void processFinal() override;

    /**
     * �f�|�W�g������A�N�^�[��{�t�H�[���[�V���������o�[�Ƃ��Đݒ肵�擾����i���W����j .
     * etFormationMemberDepository() �̎��O���s���K�v�B<BR>
     * �{���\�b�h���Ăяo���ƁA�f�|�W�g���ɊǗ����ꂽ�����o�[����� dispatch() ����܂��B(������ activate() �������)
     * �f�|�W�g���̃����o�[�����ׂĊ������ŁA�͊����Ă���ꍇ nullptr ���Ԃ�܂��B
     * �܂��A������ prm_formation_sub_num �͍ő�ґ��\���v�����ŁA���̐��ȏ�̌Ăяo���ł� nullptr ���Ԃ�܂��B
     * ��x�ł� nullptr ���Ԃ����ƁA�����t���O canCallUp() �� false �ɂȂ�A�ȍ~�{�t�H�[���[�V�����I�u�W�F�N�g��
     * �����o�[�Ăяo���ł��Ȃ��悤�ɂȂ�܂��B�Ɠ����ɁAprocessFinal() �Ŏ����I�� sayonara(_offset_frames_end) �����s����A
     * �t�H�[���[�V�����I�u�W�F�N�g�͎����I���̐��ɓ���܂��B_offset_frames_end �̃f�t�H���g�l�� FORMATION_END_DELAY �t���[���ł��B
     * ���ӁB�����[�ɌĂяo���Ă������o�[���m�ۂł��Ȃ��ꍇ���A
     * �{�t�H�[���[�V�����I�u�W�F�N�g�� sayonara(_offset_frames_end) �����s����I�����Ă��܂��܂��B
     * �\�������o�[��o�^��ɌĂяo���悤�ɂ��ĉ������B
     * @param prm_formation_sub_num �{�t�H�[���[�V�����̍ő�ґ��\���v����
     * @return �ґ��\���v���̃A�N�^�[�B
     *         �ő�ґ��\���v�������I�[�o�[���ČĂяo�����ꍇ�A������
     *         �f�|�W�g���ɍ\���v�����������Ȃ��ꍇ�� nullptr
     */
    GgafActor* callUpMember(int prm_formation_sub_num = INT_MAX);

    /**
     * callUpMember() �\�ȏꍇ true
     * @return
     */
    bool canCallUp();

    /**
     * �����o�[���c���Ă���Ή�����܂��B
     * �p�����ăI�[�o�[���C�h����ꍇ�́A��������
     * GgafDepositoryFormation::onEnd() ���Ăяo���ĉ������B
     */
    virtual void onEnd() override;

    /**
     * �f�|�W�g�����[�h�Ǘ��̕ґ��S�Ă� sayonara() �����s����B
     */
    virtual void sayonaraFollwer();

    virtual void processOnSayonara() override {
    }

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
