#ifndef GGAFDX9SPHEREEX_H_
#define GGAFDX9SPHEREEX_H_
namespace GgafDx9Core {

/**
 * �����蔻��\���p���N���X
 * DefaultSphereActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2010/01/17
 * @author Masatoshi Tsuge
 */
class GgafDx9SphereEx : public GgafDx9SphereActor {

public:

    GgafDx9SphereEx(const char* prm_name);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void catchEvent(UINT32 prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B

    virtual ~GgafDx9SphereEx();

};

}
#endif /*GGAFDX9SPHEREEX_H_*/
