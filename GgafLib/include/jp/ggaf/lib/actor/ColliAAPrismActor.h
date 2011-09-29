#ifndef COLLIAAPRISMACTOR_H_
#define COLLIAAPRISMACTOR_H_
namespace GgafLib {

/**
 * 当たり判定表示用AAプリズムクラス
 * GgafDxAAPrismActor を継承し、当たり判定領域表示機能を追加したアクターです。
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class ColliAAPrismActor : public GgafDxCore::GgafDxAAPrismActor {
    static ColliAAPrismActor* _pObj;

public:
    static ColliAAPrismActor* get();
    static void release();

    ColliAAPrismActor(const char* prm_name, GgafCore::GgafStatus* prm_pStat = NULL);

    //void processDraw() {} //オーバーライド未実装にする。
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
