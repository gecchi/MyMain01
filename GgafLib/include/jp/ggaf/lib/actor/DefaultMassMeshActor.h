#ifndef GGAFLIB_DEFAULTMASSMESHACTOR_H_
#define GGAFLIB_DEFAULTMASSMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"

namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class DefaultMassMeshActor : public GgafDxCore::GgafDxMassMeshActor {

public:
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultMassMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual ~DefaultMassMeshActor();
};

}
#endif /*GGAFLIB_DEFAULTMASSMESHACTOR_H_*/
