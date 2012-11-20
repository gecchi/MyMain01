#ifndef COLLIAABACTER_H_
#define COLLIAABACTER_H_
namespace GgafLib {

/**
 * �����蔻��\���p�L���[�u�N���X
 * GgafDxAABActor ���p�����A�����蔻��̈�\���@�\��ǉ������A�N�^�[�ł��B
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class ColliAABActor : public GgafDxCore::GgafDxAABActor {
    static ColliAABActor* _pObj;

public:
    static ColliAABActor* get();
    static void release();

    ColliAABActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = nullptr);

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

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitarea(CollisionChecker* prm_pChecker);

    virtual ~ColliAABActor();

};

}
#endif /*COLLIAABACTER_H_*/
