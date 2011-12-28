#ifndef DEFAULTSPRITESETACTOR_H_
#define DEFAULTSPRITESETACTOR_H_
namespace GgafLib {

/**
 * スプライトセットアクターの具象クラス.
 * GgafDxCore::GgafDxSpriteSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/07/15
 * @author Masatoshi Tsuge
 */
class DefaultSpriteSetActor : public GgafDxCore::GgafDxSpriteSetActor {

public:
    frame _offset_frames;

    CollisionChecker* _pCollisionChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;


    DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat);

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

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*DEFAULTSPRITESETACTOR_H_*/
