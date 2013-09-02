#ifndef GGAFDXCORE_GGAFDXMORPHMESHEFFECT_H_
#define GGAFDXCORE_GGAFDXMORPHMESHEFFECT_H_
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMorphMesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_morph_target_num;
    D3DXHANDLE _ah_weight[MAX_MORPH_TARGET+1];
    D3DXHANDLE _h_matView;
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
    GgafDxMorphMeshEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxMorphMeshEffectManagerである<BR>
     */
    virtual ~GgafDxMorphMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXMORPHMESHEFFECT_H_*/
