#ifndef GGAFLIB_DEFAULTPOINTSPRITESETACTOR_H_
#define GGAFLIB_DEFAULTPOINTSPRITESETACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteSetActor.h"

namespace GgafLib {

/**
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteSetActor : public GgafDxCore::GgafDxPointSpriteSetActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pColliChecker;

public:
    DefaultPointSpriteSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultPointSpriteSetActor();
};

}
#endif /*GGAFLIB_DEFAULTMESHSETACTOR_H_*/
