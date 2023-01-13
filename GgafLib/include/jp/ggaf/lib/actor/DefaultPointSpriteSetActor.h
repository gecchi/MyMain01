#ifndef GGAF_LIB_DEFAULTPOINTSPRITESETACTOR_H_
#define GGAF_LIB_DEFAULTPOINTSPRITESETACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/PointSpriteSetActor.h"

namespace GgafLib {

/**
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class DefaultPointSpriteSetActor : public GgafDx::PointSpriteSetActor {

public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pColliCollisionChecker;

public:
    DefaultPointSpriteSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pColliCollisionChecker;
    }

    virtual ~DefaultPointSpriteSetActor();
};

}
#endif /*GGAF_LIB_DEFAULTMESHSETACTOR_H_*/
