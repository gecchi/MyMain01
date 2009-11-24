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
    D3DXHANDLE _hMorphTargetnum;
    D3DXHANDLE _hWeight[10];
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9MorphMeshEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9MorphMeshEffectManagerである<BR>
     */
    virtual ~GgafDx9MorphMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDX9MORPHMESHEFFECT_H_*/
