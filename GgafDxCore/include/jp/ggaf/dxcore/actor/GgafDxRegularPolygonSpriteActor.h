#ifndef GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_
#define GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * 正多角形疑似スプライトアクター .
 * GgafDxFigureActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです。<BR>
 * いわゆる板ポリ<BR>
 * @version 1.00
 * @since 2010/10/18
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

    GgafDxAlign _align;

    GgafDxValign _valign;
    /** 何枚扇を描画するか */
    int _draw_fan_num;
    /** 多角形描画を開始する最初の頂点の角度位置 */
    angle _circumference_begin_position;

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

//    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
//    virtual void setAlign(GgafDxAlign prm_align);
//    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
    /**
     * 描画するFAN(扇型)の枚数を取得
     * @return 描画するFAN(扇型)の枚数
     */
    int getDrawFanNum() {
        return _draw_fan_num;
    }

    /**
     * 描画するFAN(扇型)の枚数を指定する .
     * @param prm_draw_fan_num 描画するFAN(扇型)の枚数
     */
    void setDrawFanNum(int prm_draw_fan_num) {
        _draw_fan_num = prm_draw_fan_num;
    }

    /**
     * 多角形描画を開始する最初の頂点の角度位置を設定する .
     * @param prm_ang 最初の頂点の角度位置
     */
    void setBeginAngPos(angle prm_ang) {
        _circumference_begin_position = prm_ang;
    }

    /**
     * 現在の多角形描画を開始する最初の頂点の角度位置を取得
     * @return 最初の頂点の角度位置
     */
    angle getBeginAngPos() {
        return _circumference_begin_position;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEACTOR_H_*/
