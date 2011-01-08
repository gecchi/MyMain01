#ifndef COLLIAAPRISMACTOR_H_
#define COLLIAAPRISMACTOR_H_
namespace GgafDx9LibStg {

/**
 * �����蔻��\���p�L���[�u�N���X
 * DefaultCubeActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class ColliAAPrismActor : public GgafDx9Core::GgafDx9AAPrismActor {
    static ColliAAPrismActor* _pObj;

public:
    static ColliAAPrismActor* get();
    static void release();

    ColliAAPrismActor(const char* prm_name);

    //void processDraw() {} //�I�[�o�[���C�h�������ɂ���B
    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~ColliAAPrismActor();

};

}
#endif /*COLLIAABACTER_H_*/