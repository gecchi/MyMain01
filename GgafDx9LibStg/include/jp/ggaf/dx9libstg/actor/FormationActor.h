#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_
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
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            _TRACE_("FormationActor["<<getName()<<" retire("<<_frame_offset_retire<<")!!!!!!!!!!!!");
            inactivate();
            retire(_frame_offset_retire);//20�b��J��
        }
    }

public:

    DWORD _frame_offset_retire;

    FormationActor(const char* prm_name, DWORD prm_frame_offset_retire = 5*60);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processDraw() {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * �����o�[�̓o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�t�H�[���[�V�����̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub);

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
