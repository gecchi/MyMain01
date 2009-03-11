#ifndef GGAFDX9BOARDEFFECT_H_
#define GGAFDX9BOARDEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Board用モデルクラス.
 */
class GgafDx9BoardEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hTransformedX;
    D3DXHANDLE _hTransformedY;
    D3DXHANDLE _hAlpha;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9BoardEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9BoardEffectManagerである<BR>
     */
    virtual ~GgafDx9BoardEffect(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDEFFECT_H_*/
