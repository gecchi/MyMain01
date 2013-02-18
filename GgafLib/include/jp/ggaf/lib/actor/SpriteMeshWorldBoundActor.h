#ifndef SPRITEMESHWORLDBOUNDACTOR_H_
#define SPRITEMESHWORLDBOUNDACTOR_H_
namespace GgafLib {

/**
 * 世界境界.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class SpriteMeshWorldBoundActor : public GgafDxCore::GgafDxSpriteMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;

public:
    SpriteMeshWorldBoundActor(const char* prm_name,
                              const char* prm_model,
                              GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    int isOutOfView() override {
        //画面外判定無し
        return 0;
    }

    bool isOutOfUniverse() override {;
        //ゲーム座標範囲外判定無し
        return false;
    }
    virtual ~SpriteMeshWorldBoundActor();
};

}
#endif /*WORLDBOUNDACTOR_H_*/
