#ifndef GGAF_DX_SPRITEMESHACTOR_H_
#define GGAF_DX_SPRITEMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * スプライトメッシュセットアクター.
 * MeshActor を継承し、
 * さらにUVを切り替える機能を有したアクター
 * メッシュ３Dオブジェクトの表面のテクスチャをアニメーションできます。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshActor : public MeshActor {

public:
    /** UVフリッパー(パラパラアニメ) */
    UvFlipper* _pUvFlipper;

public:
    /**
     * コンストラクタ.
     * SpriteMeshSetActor で使用するモデルIDは避けて下さい。
     * @param prm_name
     * @param prm_model
     * @param prm_pStat
     * @param prm_pChecker
     */
    SpriteMeshActor(const char* prm_name,
                           const char* prm_model,
                           GgafCore::Status* prm_pStat,
                           Checker* prm_pChecker );

    virtual void processDraw() override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~SpriteMeshActor();
};

}
#endif /*GGAF_DX_SPRITEMESHACTOR_H_*/
