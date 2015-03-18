#ifndef GGAFLIB_DEFAULTDYNAD3DXMESHACTOR_H_
#define GGAFLIB_DEFAULTDYNAD3DXMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxDynaD3DXMeshActor.h"

namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * GgafDxCore::GgafDxDynaD3DXMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DefaultDynaD3DXMeshActor : public GgafDxCore::GgafDxDynaD3DXMeshActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultDynaD3DXMeshActor();
};

}
#endif /*GGAFLIB_DEFAULTDYNAD3DXMESHACTOR_H_*/
