#ifndef DEFAULTBOARDACTOR_H_
#define DEFAULTBOARDACTOR_H_
namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxBoardActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2009/03/11
 * @author Masatoshi Tsuge
 */
class DefaultBoardActor : public GgafDxCore::GgafDxBoardActor {

public:
    DefaultBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = NULL);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultBoardActor();

};

}
#endif /*DEFAULTBOARDACTOR_H_*/
