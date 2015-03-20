#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHSETEFFECT_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHSETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"

namespace GgafDxCore {

/**
 * GgafDxCubeMapMeshsModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshSetEffect : public GgafDxMeshSetEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_reflectance;

public:
    GgafDxCubeMapMeshSetEffect(char* prm_effect_name);

    virtual ~GgafDxCubeMapMeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHEFFECT_H_*/
