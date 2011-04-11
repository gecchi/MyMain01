#ifndef GGAFDX9FORMATIONACTOR_H_
#define GGAFDX9FORMATIONACTOR_H_

#define FORMATION_END_DELAY (30*60)
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
    GgafDx9FormationActor(const char* prm_name, frame prm_frame_offset_end = FORMATION_END_DELAY);

    virtual void initialize() override {
    }

    virtual void processBehavior() override;

    virtual void processDraw() {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * �ґ��ɏ��������A�N�^�[���S�ł����ꍇ�ɌĂяo����郁�\�b�h�i�Ƃ���) .
     * �ґ��S�Ŏ��̋�̓I�ȏ����i�ґ��{�[�i�X���Z��A������ʉ����j�͉��ʂŎ������邱�ƁB <BR>
     * �܂��A�{���\�b�h���@�\���邽�߂ɂ́A�A�N�^�[���Ŏ��g�����ꂽ�ꍇ�ɁA<BR>
     * wasDestroyedFollower() ���Ăяo�������K�{�ł��B <BR>
     * �ґ��S�Ŏ��̏������Ȃ��ꍇ�́Aoverride ����K�v�͂���܂��� �B <BR>
     * @param prm_pActorLast �Ō�ɂ��ꂽ�A�N�^�[
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    }


    /**
     * �ґ��ɏ��������A�N�^�[�����ł���ۂɃR�[�����Ă��炤���\�b�h .
     * �ґ��S�Ŕ�����s�������iwasDestroyedFormation(GgafDx9GeometricActor*) ���R�[���o�b�N���������j�ꍇ�́A<BR>
     * �{���\�b�h���A�N�^�[���Ŏ��g�����ꂽ���ɁA�s�x�Ăт����s���K�v������܂��B<BR>
     * ��̓I�ɁA�ґ��v�f�̊e�A�N�^�[�́u�j��ɂ��v���ŏ������ɁA���̂悤�ȂP�s�������Ă��������B<BR>
     * �i���u�̈�O�ɂ��v���ŏ����ŌĂяo���Ă͂����܂���j<BR>
     * <code>
     *
     * ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
     *
     * </code>
     * ���́A�P�ɓ����ŃJ�E���^�����炵�A�J�E���g��0�ɂȂ�� wasDestroyedFormation() ���R�[���o�b�N���Ă��邾���ł��B<BR>
     * @param prm_pActor ���ꂽ�A�N�^�[
     */
    virtual void wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor);

    /**
     * �ґ��̃����o�[�̓o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;

    virtual ~GgafDx9FormationActor();
};

}
#endif /*GGAFDX9FORMATIONACTOR_H_*/
