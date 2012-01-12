#ifndef DEFAULTSPRITEACTOR_H_
#define DEFAULTSPRITEACTOR_H_
namespace GgafLib {

/**
 * スプライトアクターの具象クラス.
 * GgafDxCore::GgafDxSpriteActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2008/02/25
 * @author Masatoshi Tsuge
 */
class DefaultSpriteActor : public GgafDxCore::GgafDxSpriteActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pCollisionChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;


    DefaultSpriteActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat);

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultSpriteActor();

};

}
#endif /*DEFAULTSPRITEACTOR_H_*/
