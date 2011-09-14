#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_

#define FORMATION_END_DELAY (30*60)
namespace GgafDx9LibStg {



/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * �p���N���X��processJudgement()�g�p�����ӂ��邱�ƁB
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FormationActor : public GgafDx9Core::GgafDx9GeometricActor {
private:
    /**
     * �T�u��������Ύ�
     */
    virtual void processJudgement() override;

public:
    /** [r]�����A�N�^�[��(addSubLast�ɂ�葝���AwasDestroyedFollower�Ō���) */
    int _num_sub;
    int _num_destory;
    int _num_inactive;

    frame _offset_frames_end;
    bool _is_called_up;
    bool _is_init;

    /** �\�������o�[�̃X�g�b�J�[ */
    GgafCore::GgafActorDepository* _pDepo;
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    FormationActor(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);

    void setActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    GgafDx9GeometricActor* callUp();
    /**
     * �ґ��̃����o�[�̓o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;


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
     * �{���\�b�h���A�N�^�[���Ŏ��g�����ꂽ���ɁA�s�x�Ăт������s���K�v������܂��B<BR>
     * ��̓I�ɁA�ґ��v�f�̊e�A�N�^�[�́u�j��ɂ��v���ŏ������ɁA���̂悤�ȂP�s�������Ă��������B<BR>
     * �i���u�̈�O�ɂ��v���ŏ����ŌĂяo���Ă͂����܂���j<BR>
     * <code>
     *
     * ((FormationActor*)getParent())->wasDestroyedFollower(this);
     *
     * </code>
     * ���́A�P�ɓ����ŃJ�E���^�����炵�A�J�E���g��0�ɂȂ�� wasDestroyedFormation() ���R�[���o�b�N���Ă��邾���ł��B<BR>
     * @param prm_pActor ���ꂽ�A�N�^�[
     */
    virtual void wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor);

    virtual void wasInactiveFollower();

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
