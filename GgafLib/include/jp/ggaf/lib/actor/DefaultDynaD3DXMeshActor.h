#ifndef GGAF_LIB_DEFAULTDYNAD3DXMESHACTOR_H_
#define GGAF_LIB_DEFAULTDYNAD3DXMESHACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/DynaD3DXMeshActor.h"

namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * GgafDx::DynaD3DXMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DefaultDynaD3DXMeshActor : public GgafDx::DynaD3DXMeshActor {

public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;

public:
    DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model);

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

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~DefaultDynaD3DXMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTDYNAD3DXMESHACTOR_H_*/
