#ifndef GGAF_DX_SPRITEMESHACTOR_H_
#define GGAF_DX_SPRITEMESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * スプライトメッシュセットアクター.
 *
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
     * @param prm_pColliChecker
     */
    SpriteMeshActor(const char* prm_name,
                    const char* prm_model);

    virtual void processDraw() override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~SpriteMeshActor();
};

}
#endif /*GGAF_DX_SPRITEMESHACTOR_H_*/
