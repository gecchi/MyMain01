#ifndef GGAFDX9BOARDSETEFFECT_H_
#define GGAFDX9BOARDSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardSet用モデルクラス.
 */
class GgafDx9BoardSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _ahOffsetU[8];
    D3DXHANDLE _ahOffsetV[8];
    D3DXHANDLE _ahTransformedX[8];
    D3DXHANDLE _ahTransformedY[8];
    D3DXHANDLE _ahAlpha[8];
    D3DXHANDLE _ahDepthZ[8];

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
