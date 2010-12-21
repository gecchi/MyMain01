#ifndef GGAFDX9BOARDEFFECT_H_
#define GGAFDX9BOARDEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Board用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    //D3DXHANDLE _h_matWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hTransformedX;
    D3DXHANDLE _hTransformedY;
    D3DXHANDLE _hSx;
    D3DXHANDLE _hSy;
    D3DXHANDLE _hAlpha;
    D3DXHANDLE _hDepthZ;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9BoardEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override {};

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9BoardEffectManagerである<BR>
     */
    virtual ~GgafDx9BoardEffect(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDEFFECT_H_*/
