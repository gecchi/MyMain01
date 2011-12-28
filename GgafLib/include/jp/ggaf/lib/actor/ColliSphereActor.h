#ifndef COLLISPHEREACTOR_H_
#define COLLISPHEREACTOR_H_
namespace GgafLib {

/**
 * �����蔻��\���p���N���X
 * DefaultSphereActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class ColliSphereActor : public GgafDxCore::GgafDxSphereActor {
    static ColliSphereActor* _pObj;

public:
    static ColliSphereActor* get();
    static void release();

    ColliSphereActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = NULL);

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


    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~ColliSphereActor();

};

}
#endif /*COLLISPHEREACTOR_H_*/
