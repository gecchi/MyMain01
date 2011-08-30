#ifndef DEFAULTPOINTSPRITEACTOR_H_
#define DEFAULTPOINTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * スプライトアクターの具象クラス.
 * GgafDx9Core::GgafDx9PointSpriteActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2008/02/25
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteActor : public GgafDx9Core::GgafDx9PointSpriteActor {

public:
    frame _offset_frames;

    CollisionChecker* _pCollisionChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9Scaler* _pScaler;


    DefaultPointSpriteActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat);

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultPointSpriteActor();

};

}
#endif /*DEFAULTPOINTSPRITEACTOR_H_*/
