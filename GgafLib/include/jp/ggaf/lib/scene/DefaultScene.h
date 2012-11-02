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

    /** [r]�V�[���C�x���g�p�̃t���[���l�̔z��(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    UINT32* _paFrame_NextEvent;
    /** [r]�V�[���̃C�x���g���i_paFrame_NextEvent�̗v�f���j(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _event_num;
    /** �V�[���̌��݃C�x���g(���u�V�[��Creater.xls�v�}�N���̐���PG�ɑg�ݍ��܂��j */
    int _cnt_event;
    /** [r]�V�[���i���Ǘ�(GgafElement<GgafScene>::GgafProgress* _pProg; ���V���h�[) */
    SceneProgress* _pProg; //GgafElement<GgafScene>::GgafProgress* _pProg; ���V���h�[

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
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~DefaultScene();
};

}
#endif /*DEFAULTSCENE_H_*/
