#ifndef GGAF_LIB_DEFAULTPOINTSPRITESETACTOR_H_
#define GGAF_LIB_DEFAULTPOINTSPRITESETACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
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
    WorldCollisionChecker* _pWorldCollisionChecker;

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

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~DefaultPointSpriteSetActor();
};

}
#endif /*GGAF_LIB_DEFAULTMESHSETACTOR_H_*/
