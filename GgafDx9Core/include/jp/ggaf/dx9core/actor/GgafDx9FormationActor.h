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
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            _TRACE_("GgafDx9FormationActor["<<getName()<<" end("<<_frame_offset_end<<")!!!!!!!!!!!!");
            inactivate();
            sayonara(_frame_offset_end);
        }
    }

public:

    DWORD _frame_offset_end;
    /**
     *
     * @param prm_name
     * @param prm_frame_offset_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    GgafDx9FormationActor(const char* prm_name, DWORD prm_frame_offset_end = 20*60);

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

    virtual ~GgafDx9FormationActor();
};

}
#endif /*GGAFDX9FORMATIONACTOR_H_*/
