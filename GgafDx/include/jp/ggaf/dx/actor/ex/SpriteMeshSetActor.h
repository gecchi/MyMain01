#ifndef GGAF_DX_SPRITEMESHSETACTOR_H_
#define GGAF_DX_SPRITEMESHSETACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"

namespace GgafDx {

/**
 * スプライトメッシュアクター.
 * MeshSetActor を継承し、
 * さらにUVを切り替える機能を有したアクター
 * メッシュ３Dオブジェクトの表面のテクスチャをアニメーションできます。
 * それのSet版。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshSetActor : public MeshSetActor {

public:
    /** UVフリッパー(パラパラアニメ) */
    UvFlipper* _pUvFlipper;

public:
    SpriteMeshSetActor(const char* prm_name,
                       const char* prm_model,
                       CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~SpriteMeshSetActor();

};

}
#endif /*GGAF_DX_SPRITEMESHSETACTOR_H_*/
