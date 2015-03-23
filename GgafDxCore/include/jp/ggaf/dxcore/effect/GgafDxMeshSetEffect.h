#ifndef GGAFDXCORE_GGAFDXMESHSETEFFECT_H_
#define GGAFDXCORE_GGAFDXMESHSETEFFECT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMeshSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class GgafDxMeshSetEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _ah_matWorld[19];
    D3DXHANDLE _ah_materialDiffuse[19];
    D3DXHANDLE _ah_offset_u[19];
    D3DXHANDLE _ah_offset_v[19];
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMeshSetEffect(const char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxMeshSetEffectManagerである<BR>
     */
    virtual ~GgafDxMeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETEFFECT_H_*/
