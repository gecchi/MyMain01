#ifndef GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_
#define GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * スプライトアクター.
 * GgafDxGeometricActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです。<BR>
 * いわゆる板ポリ<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class GgafDxRegularPolygonSpriteActor : public GgafDxFigureActor {

public:
    /** [r]モデル資源 */
    GgafDxRegularPolygonSpriteModel* const _pRegularPolygonSpriteModel;
    /** [r]エフェクト資源 */
    GgafDxRegularPolygonSpriteEffect* const _pRegularPolygonSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;

    float _far_rate;
    /** 何枚扇を描画するか */
    int _draw_fan_num;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxRegularPolygonSpriteActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique,
                      GgafCore::GgafStatus* prm_pStat,
                      GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxRegularPolygonSpriteActor();

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

    void setDrawFanNum(int prm_draw_fan_num) {
        _draw_fan_num = prm_draw_fan_num;
    }

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_*/
