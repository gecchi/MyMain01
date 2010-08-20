#ifndef GGAFDX9SPHEREEX_H_
#define GGAFDX9SPHEREEX_H_
namespace GgafDx9Core {

/**
 * 当たり判定表示用球クラス
 * DefaultSphereActor を継承し、当たり判定領域表示機能を追加したアクターです。
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

    //void processDraw() {} //オーバーライド未実装にする。

    virtual ~GgafDx9SphereEx();

};

}
#endif /*GGAFDX9SPHEREEX_H_*/
