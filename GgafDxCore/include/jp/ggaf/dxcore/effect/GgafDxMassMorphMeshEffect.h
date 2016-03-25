#ifndef GGAFDXCORE_GGAFDXMASSMORPHMESHEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSMORPHMESHEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassMorphMesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMassMorphMeshEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_morph_target_num;
    D3DXHANDLE _h_matView;
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
    GgafDxMassMorphMeshEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxMassMorphMeshEffectManagerである<BR>
     */
    virtual ~GgafDxMassMorphMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXMASSMORPHMESHEFFECT_H_*/
