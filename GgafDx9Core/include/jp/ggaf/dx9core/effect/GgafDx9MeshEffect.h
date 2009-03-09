#ifndef GGAFDX9MESHEFFECT_H_
#define GGAFDX9MESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh用モデルクラス.
 */
class GgafDx9MeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9MeshEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9MeshEffectManagerである<BR>
     */
    virtual ~GgafDx9MeshEffect(); //デストラクタ

};

}
#endif /*GGAFDX9MESHEFFECT_H_*/
