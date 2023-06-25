#ifndef GGAF_DX_MORPHMESHEFFECT_H_
#define GGAF_DX_MORPHMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * MorphMesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MorphMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_morph_target_num;
    D3DXHANDLE _ah_weight[MAX_MORPH_TARGET+1];
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MorphMeshEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはMorphMeshEffectManagerである<BR>
     */
    virtual ~MorphMeshEffect();

};

}
#endif /*GGAF_DX_MORPHMESHEFFECT_H_*/
