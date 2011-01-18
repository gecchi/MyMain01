#ifndef GGAFDX9MESHSETEFFECT_H_
#define GGAFDX9MESHSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9MeshSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _ah_matWorld[19];
    D3DXHANDLE _ah_materialDiffuse[19];
    D3DXHANDLE _ahOffsetU[19];
    D3DXHANDLE _ahOffsetV[19];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9MeshSetEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9MeshSetEffectManagerである<BR>
     */
    virtual ~GgafDx9MeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDX9MESHSETEFFECT_H_*/
