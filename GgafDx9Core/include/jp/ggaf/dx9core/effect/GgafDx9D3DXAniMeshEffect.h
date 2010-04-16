#ifndef GGAFDX9D3DXANIMESHEFFECT_H_
#define GGAFDX9D3DXANIMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXAniMeshEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hMaterialDiffuse;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9D3DXAniMeshEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9D3DXAniMeshEffectManagerである<BR>
     */
    virtual ~GgafDx9D3DXAniMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDX9D3DXANIMESHEFFECT_H_*/
