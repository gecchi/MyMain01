#ifndef GGAFLIB_WORLDBOUNDACTOR_H_
#define GGAFLIB_WORLDBOUNDACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxWorldBoundActor.h"

namespace GgafLib {

/**
 * 世界境界.
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBoundActor : public GgafDxCore::GgafDxWorldBoundActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* const _pScaler;

    frame _offset_frames;

public:
    WorldBoundActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void processSettlementBehavior() override;

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override {
    }

    virtual int isOutOfView() override {
        //画面外判定無し
        return 0;
    }

    virtual bool isOutOfUniverse() override {;
        //ゲーム座標範囲外判定無し
        return false;
    }
    virtual ~WorldBoundActor();
};

}
#endif /*GGAFLIB_WORLDBOUNDACTOR_H_*/
