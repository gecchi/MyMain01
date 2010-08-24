#ifndef GGAFDX9FORMATIONACTOR_H_
#define GGAFDX9FORMATIONACTOR_H_
namespace GgafDx9Core {

/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * �p���N���X��processJudgement()�g�p�����ӂ��邱�ƁB
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDx9FormationActor : public GgafDx9GeometricActor {
private:
    /**
     * �T�u��������Ύ�
     */
    virtual void processJudgement() override;

public:
    /** �����A�N�^�[�� */
    int _num_sub;

    frame _frame_offset_end;
    /**
     *
     * @param prm_name
     * @param prm_frame_offset_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafDx9FormationActor(const char* prm_name, frame prm_frame_offset_end = 30*60);

    virtual void initialize() override {
    }

    virtual void processBehavior() override;

    virtual void processDraw() {
    }

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * �ґ��ɏ��������A�N�^�[���S�ł����ꍇ�ɌĂяo�����\�b�h�Ƃ���B .
     * ��̓I�ȏ����i�ґ��{�[�i�X���Z��A������ʉ����j�͉��ʂŎ������邱�ƁB
     * �܂��A�{���\�b�h���@�\���邽�߂ɂ́A�A�N�^�[���Ŏ��g�����ꂽ�ꍇ�ɁA
     * wasDestroyedFollower() ���Ăяo�������K�{�ł��B
     * @param prm_pActorLast
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    }


    /**
     * �ґ��ɏ��������A�N�^�[�́A���g�����ł���ۂɌĂяo�����\�b�h .
     * wasDestroyedFormation() ���Ăяo����邽�߂ɂ́A�{���\�b�h���A�N�^�[���Ŏ��g�����ꂽ�ꍇ��
     * �s�x�Ăт����ĉ������B
     * �����ŃJ�E���^�����炵�A�J�E���g��0�ɂȂ�� wasDestroyedFormation() ���Ăт������܂��B
     * @param prm_pActor
     */
    virtual void wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor);


    /**
     * �����o�[�̓o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;

    virtual ~GgafDx9FormationActor();
};

}
#endif /*GGAFDX9FORMATIONACTOR_H_*/
