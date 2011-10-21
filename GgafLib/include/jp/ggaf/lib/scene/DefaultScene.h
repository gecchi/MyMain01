#ifndef DEFAULTSCENE_H_
#define DEFAULTSCENE_H_
namespace GgafLib {

/**
 * �V�[���̋�ۃN���X .
 * GgafDxCore::GgafDxScene ���p�����A�����������ۃV�[���ł��B
 * @version 1.00
 * @since 2007/12/06
 * @author Masatoshi Tsuge
 */
class DefaultScene : public GgafDxCore::GgafDxScene {
public:

    /** �V�[���C�x���g�p�̃t���[���l�̔z��(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    UINT32* _paFrame_NextEvent;
    /** �V�[���̃C�x���g���i_paFrame_NextEvent�̗v�f���j(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _event_num;
    /** �V�[���̌��݃C�x���g(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _iCnt_Event;
    /** �V�[���i���Ǘ�(GgafElement<GgafScene>::GgafProgress* _pProg; ���V���h�[) */
    SceneProgress* _pProg;

    DefaultScene(const char* prm_name);

    void useProgress(int prm_num = 10) override;

    virtual void initialize() override {
    }

    /**
     * �V�[�������Z�b�g���A�ė��p�\�ɂ��� .
     * ���ʂŎ������Ă��������B
     */
    virtual void onReset() override {
    }

    virtual void processBehavior() override {
        TRACE("DefaultScene::processBehavior " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processJudgement() override {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void processDraw() override {
        TRACE("DefaultScene::processJudgement " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
        TRACE("DefaultScene::catchEvent " << getName() << "no:" << prm_no);
    }

    virtual void processFinal() override {
        TRACE("DefaultScene::processFinally " << getName() << "frame:" << _frame_of_behaving);
    }

    virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
