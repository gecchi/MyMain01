#ifndef GGAFDX9MESHEFFECT_H_
#define GGAFDX9MESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;

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
