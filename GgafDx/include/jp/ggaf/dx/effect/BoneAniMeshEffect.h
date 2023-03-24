#ifndef GGAF_DX_BONEANIMESHEFFECT_H_
#define GGAF_DX_BONEANIMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * Mesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class BoneAniMeshEffect : public Effect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
//    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;
    D3DXHANDLE _ah_matWorld[30];
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    BoneAniMeshEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはBoneAniMeshEffectManagerである<BR>
     */
    virtual ~BoneAniMeshEffect();

};

}
#endif /*GGAF_DX_BONEANIMESHEFFECT_H_*/
