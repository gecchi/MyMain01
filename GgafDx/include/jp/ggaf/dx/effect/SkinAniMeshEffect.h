#ifndef GGAF_DX_SKINANIMESHEFFECT_H_
#define GGAF_DX_SKINANIMESHEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/World3DimEffect.h"

//DefaultSkinAniMeshEffect.fx と 定数を一致させる事
#define SkinAniMeshModel_MAX_BONE_WORLD_MATRIX (50) //2以上でないとブレイクしないのでダメ

namespace GgafDx {

/**
 * Mesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class SkinAniMeshEffect : public World3DimEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;
    D3DXHANDLE _ah_matBone[SkinAniMeshModel_MAX_BONE_WORLD_MATRIX];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    SkinAniMeshEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはSkinAniMeshEffectManagerである<BR>
     */
    virtual ~SkinAniMeshEffect();

};

}
#endif /*GGAF_DX_SKINANIMESHEFFECT_H_*/
