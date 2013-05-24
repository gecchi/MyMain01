#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace VioletVreath {

/**
 * メッシュアクターの具象クラス.
 * GgafDxCore::GgafDxMeshActor を空実装した具象アクターです。
 * （現在未使用）
 */
class GroundMeshActor : public GgafDxCore::GgafDxMeshActor {

public:
    GgafDxCore::GgafDxScaler* _pScaler;

    frame offset_frames_;

    GgafLib::CollisionChecker3D* _pColliChecker;

public:
    GroundMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);
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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
