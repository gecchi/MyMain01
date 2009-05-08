#ifndef GGAFDX9MORPHMESHEFFECT_H_
#define GGAFDX9MORPHMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh用モデルクラス.
 */
class GgafDx9MorphMeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hWeight;
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
