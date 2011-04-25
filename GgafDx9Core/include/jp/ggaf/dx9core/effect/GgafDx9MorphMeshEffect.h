#ifndef GGAFDX9MORPHMESHEFFECT_H_
#define GGAFDX9MORPHMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9MorphMesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDx9MorphMeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

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
    GgafDx9MorphMeshEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9MorphMeshEffectManagerである<BR>
     */
    virtual ~GgafDx9MorphMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDX9MORPHMESHEFFECT_H_*/
