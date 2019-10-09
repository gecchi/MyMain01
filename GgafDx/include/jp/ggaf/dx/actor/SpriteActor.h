#ifndef GGAF_DX_SPRITEACTORD_H_
#define GGAF_DX_SPRITEACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * スプライトアクター.
 * FigureActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです。<BR>
 * いわゆる板ポリ<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class SpriteActor : public FigureActor {

public:
    /** [r]モデル資源 */
    SpriteModel* const _pSpriteModel;
    /** [r]エフェクト資源 */
    SpriteEffect* const _pSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

    float _far_rate;
    Align _align;
    Valign _valign;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    SpriteActor(const char* prm_name,
                const char* prm_model_id,
                const char* prm_effect_id,
                const char* prm_technique,
                Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~SpriteActor();

    /**
     * 遠くの座標でも強制表示 .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
};

}
#endif /*GGAF_DX_SPRITEACTORD_H_*/
