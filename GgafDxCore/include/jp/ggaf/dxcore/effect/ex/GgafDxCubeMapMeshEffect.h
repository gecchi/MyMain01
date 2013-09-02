#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHEFFECT_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"

namespace GgafDxCore {

/**
 * GgafDxCubeMapMeshModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshEffect : public GgafDxMeshEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_reflectance;

public:
    GgafDxCubeMapMeshEffect(char* prm_effect_name);

    virtual ~GgafDxCubeMapMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHEFFECT_H_*/
