#ifndef GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_
#define GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * 正多角形疑似スプライトアクター .
 * 板ポリゴンにテクスチャを貼り付けた<BR>
 * 所謂擬似スプライトのアクターです。<BR>
 * いわゆる板ポリ<BR>
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteActor : public FigureActor {

public:
    /** [r]モデル資源 */
    RegularPolygonSpriteModel* const _pRegularPolygonSpriteModel;
    /** [r]エフェクト資源 */
    RegularPolygonSpriteEffect* const _pRegularPolygonSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

    float _far_rate;

    /** 何枚扇を描画するか */
    int _draw_fan_num;
    /** 多角形描画を開始する最初の頂点の角度位置 */
    angle _circumference_begin_position;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".rsprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    RegularPolygonSpriteActor(const char* prm_name,
                              const char* prm_model,
                              const char* prm_effect_id,
                              const char* prm_technique,
                              CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~RegularPolygonSpriteActor();

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
#endif /*GGAF_DX_REGULARPOLYGONSPRITEACTOR_H_*/
