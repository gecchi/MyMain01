#ifndef GGAF_DX_REGULARPOLYGONBOARDACTOR_H_
#define GGAF_DX_REGULARPOLYGONBOARDACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D表示用正多角形アクター .
 * 板ポリゴンにテクスチャを貼り付けた<BR>
 * テクスチャの１ピクセルをそのまま１ドットで表示したい時に使用。<BR>
 * 2D擬似スプライト的な機能を想定したアクター。<BR>
 * 回転機能(Z軸回転のみ)、拡大縮小機能機能あり。<BR>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class RegularPolygonBoardActor : public FigureActor, public IAlignAbleActor {

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GroupHead* appendGroupChildAsFk(kind_t prm_kind,
                                              GeometricActor* prm_pGeoActor,
                                              int prm_x_init_local,
                                              int prm_y_init_local,
                                              int prm_z_init_local,
                                              int prm_rx_init_local,
                                              int prm_ry_init_local,
                                              int prm_rz_init_local) override {
        throwCriticalException("使用不可です。");
        return nullptr;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GroupHead* appendGroupChildAsFk(GeometricActor* prm_pGeoActor,
                                              int prm_x_init_local,
                                              int prm_y_init_local,
                                              int prm_z_init_local,
                                              int prm_rx_init_local,
                                              int prm_ry_init_local,
                                              int prm_rz_init_local) override {
        throwCriticalException("使用不可です。");
        return nullptr;
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    RegularPolygonBoardModel* _pRegularPolygonBoardModel;
    /** [r]エフェクト */
    RegularPolygonBoardEffect* const _pRegularPolygonBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

    Align _align;
    Valign _valign;
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
     * @return
     */
    RegularPolygonBoardActor(const char* prm_name,
                             const char* prm_model,
                             const char* prm_effect_id,
                             const char* prm_technique );

    virtual void processDraw() override;
    virtual void setPositionAt(const GeometricActor* prm_pActor) override;
    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;
    virtual void setScale(scale s) override;
    virtual void setScale(scale sx, scale sy) override;
    virtual void setScale(scale sx, scale sy, scale sz) override;
    virtual void setScaleR(float prm_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override;
    virtual void addScaleX(scale dsx) override {
        _sx += dsx;
    }
    virtual void addScaleY(scale dsy) override {
        _sy += dsy;
    }
    virtual void addScaleZ(scale dsz) override {
        _sz += dsz;
    }

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
//
//    float getModelWidth();
//    float getModelHeight();

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

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~RegularPolygonBoardActor();
};

}
#endif /*GGAF_DX_BOARDACTORD_H_*/
