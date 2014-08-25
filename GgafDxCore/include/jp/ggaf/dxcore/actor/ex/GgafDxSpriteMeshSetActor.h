#ifndef GGAFDXCORE_GGAFDXSPRITEMESHSETACTOR_H_
#define GGAFDXCORE_GGAFDXSPRITEMESHSETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"

namespace GgafDxCore {

/**
 * スプライトメッシュアクター.
 * GgafDxMeshSetActor を継承し、
 * さらにUVを切り替える機能を有したアクター
 * メッシュ３Dオブジェクトの表面のテクスチャをアニメーションできます。
 * それのSet版。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteMeshSetActor : public GgafDxMeshSetActor {

public:
    /** UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* _pUvFlipper;

public:
    GgafDxSpriteMeshSetActor(const char* prm_name,
                             const char* prm_model,
                             GgafCore::GgafStatus* prm_pStat,
                             GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~GgafDxSpriteMeshSetActor();

};

}
#endif /*GGAFDXCORE_GGAFDXSPRITEMESHSETACTOR_H_*/
