#ifndef GGAFDX9CUBEEX_H_
#define GGAFDX9CUBEEX_H_
namespace GgafDx9Core {

/**
 * �����蔻��\���p�L���[�u�N���X
 * DefaultCubeActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeEx : public GgafDx9CubeActor {

public:

    GgafDx9CubeEx(const char* prm_name);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void catchEvent(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B

    virtual ~GgafDx9CubeEx();

};

}
#endif /*GGAFDX9CUBEEX_H_*/
