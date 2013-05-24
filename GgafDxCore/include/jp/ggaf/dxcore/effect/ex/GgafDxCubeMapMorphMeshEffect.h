#ifndef GGAFDXCUBEMAPMORPHMESHEFFECT_H_
#define GGAFDXCUBEMAPMORPHMESHEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxMorphMeshEffect.h"

namespace GgafDxCore {

/**
 * GgafDxCubeMapMorphMeshModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMorphMeshEffect : public GgafDxMorphMeshEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_reflectance;

public:
    GgafDxCubeMapMorphMeshEffect(char* prm_effect_name);

    virtual ~GgafDxCubeMapMorphMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDXCUBEMAPMESHEFFECT_H_*/
