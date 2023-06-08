#ifndef GGAF_DX_MESHSETEFFECT_H_
#define GGAF_DX_MESHSETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

namespace GgafDx {

/**
 * MeshSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class MeshSetEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _ah_matWorld[32];
    D3DXHANDLE _ah_materialDiffuse[32];
    D3DXHANDLE _ah_offset_u[32];
    D3DXHANDLE _ah_offset_v[32];
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MeshSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはMeshSetEffectManagerである<BR>
     */
    virtual ~MeshSetEffect();

};

}
#endif /*GGAF_DX_MESHSETEFFECT_H_*/
