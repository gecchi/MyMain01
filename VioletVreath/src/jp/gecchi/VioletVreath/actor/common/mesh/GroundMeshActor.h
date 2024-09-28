#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace VioletVreath {

/**
 * メッシュアクターの具象クラス.
 * GgafDx::MeshActor を空実装した具象アクターです。
 * （現在未使用）
 */
class GroundMeshActor : public GgafDx::MeshActor {

public:
    frame offset_frames_;

    GgafLib::WorldCollisionChecker* _pWorldCollisionChecker;

public:
    GroundMeshActor(const char* prm_name, const char* prm_model);
    virtual void onCreateModel() override {
    }
    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

//    /**
//     * フレームワークオーバーライド
//     */
//    virtual void processPreDraw() override;
    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline GgafLib::WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
