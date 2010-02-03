#ifndef GGAFDX9BOARDSETEFFECT_H_
#define GGAFDX9BOARDSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardSet用モデルクラス.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _ahOffsetU[28];
    D3DXHANDLE _ahOffsetV[28];
    D3DXHANDLE _ahTransformedX[28];
    D3DXHANDLE _ahTransformedY[28];
    D3DXHANDLE _ahAlpha[28];
    D3DXHANDLE _ahDepthZ[28];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9BoardSetEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9EffectManagerである<BR>
     */
    virtual ~GgafDx9BoardSetEffect(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDSETEFFECT_H_*/
