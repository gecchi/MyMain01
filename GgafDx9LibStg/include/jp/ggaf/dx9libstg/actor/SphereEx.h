#ifndef SPHEREEX_H_
#define SPHEREEX_H_
namespace GgafDx9LibStg {

/**
 * 当たり判定表示用球クラス
 * DefaultSphereActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class SphereEx : public GgafDx9Core::GgafDx9SphereActor {
    static SphereEx* _pObj;

public:
    static SphereEx* get();
    static void release();

    SphereEx(const char* prm_name);

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

    virtual ~SphereEx();

};

}
#endif /*SPHEREEX_H_*/
