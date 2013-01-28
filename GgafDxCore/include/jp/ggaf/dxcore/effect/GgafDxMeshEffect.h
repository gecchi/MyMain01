#ifndef GGAFDXMESHEFFECT_H_
#define GGAFDXMESHEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxMesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxMeshEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_matInvWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;
    D3DXHANDLE _h_far_rate;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMeshEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxMeshEffectManagerである<BR>
     */
    virtual ~GgafDxMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDXMESHEFFECT_H_*/
