#ifndef GGAFDXMESHSETEFFECT_H_
#define GGAFDXMESHSETEFFECT_H_
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
    D3DXHANDLE _ahOffsetU[19];
    D3DXHANDLE _ahOffsetV[19];
    D3DXHANDLE _h_specular;
    D3DXHANDLE _h_specular_power;
    D3DXHANDLE _h_posCam;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMeshSetEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxMeshSetEffectManagerである<BR>
     */
    virtual ~GgafDxMeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXMESHSETEFFECT_H_*/
