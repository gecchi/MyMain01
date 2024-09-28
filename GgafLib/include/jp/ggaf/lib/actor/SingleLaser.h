#ifndef GGAF_LIB_SINGLELASER_H_
#define GGAF_LIB_SINGLELASER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"
#include "jp/ggaf/lib/manager/DefaultEffectManager.h"
#include "jp/ggaf/lib/manager/DefaultModelManager.h"

namespace GgafLib {

/**
 * 単発レーザー .
 * GgafDx::MeshSetActorと同様に複数モデル描画により、高速化を目論む。 <BR>
 * 但し表示時に、マテリアルカラー、スペキュラーの計算を行わない。<BR>
 * その代わりに、GgafDx::MeshSetActor よりもさらに多くのセット数（現在26）をサポート。<BR>
 * 大量表示用に最適化されている。<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDx::MeshSetActor {

public:
    /** 衝突判定支援オブジェクト */
    WorldCollisionChecker* _pWorldCollisionChecker;

public:
    SingleLaser(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~SingleLaser();
};

}
#endif /*GGAF_LIB_SINGLELASER_H_*/

