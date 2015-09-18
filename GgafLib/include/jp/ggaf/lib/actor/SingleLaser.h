#ifndef GGAFLIB_SINGLELASER_H_
#define GGAFLIB_SINGLELASER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"

namespace GgafLib {

/**
 * 単発レーザー .
 * GgafDxCore::GgafDxMeshSetActorと同様に複数モデル描画により、高速化を目論む。 <BR>
 * 但し表示時に、マテリアルカラー、スペキュラーの計算を行わない。<BR>
 * その代わりに、GgafDxCore::GgafDxMeshSetActor よりもさらに多くのセット数（現在26）をサポート。<BR>
 * 大量表示用に最適化されている。<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDxCore::GgafDxMeshSetActor {

public:
    static D3DXHANDLE _ah_matWorld[26];

    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;

public:
    SingleLaser(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);

    /**
     * スタティックイニシャライザもどき .
     * @return true
     */
    static bool initStatic(SingleLaser* prm_pSingleLaser);

    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~SingleLaser();
};

}
#endif /*GGAFLIB_SINGLELASER_H_*/

