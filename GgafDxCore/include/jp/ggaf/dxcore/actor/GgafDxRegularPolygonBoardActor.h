#ifndef GGAFDXCORE_GGAFDXREGULARPOLYGONBOARDACTOR_H_
#define GGAFDXCORE_GGAFDXREGULARPOLYGONBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * 座標変換済みスプライトアクター .
 * GgafDxTransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * テクスチャの１ピクセルをそのまま１ドットで表示したい時に使用。<BR>
 * 2D擬似スプライト的な機能を想定したアクター。<BR>
 * 回転機能(Z軸回転のみ)、拡大縮小機能機能あり。<BR>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class GgafDxRegularPolygonBoardActor : public GgafDxFigureActor {
    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    int isOutOfView() override {
        throwGgafCriticalException("使用不可です。");
        return 0;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    bool isOutOfSpacetime() const override {
        throwGgafCriticalException("使用不可です。");
        return false;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GgafGroupHead* appendGroupChildAsFk(kind_t prm_kind,
                                             GgafDxGeometricActor* prm_pGeoActor,
                                             int prm_x_init_local,
                                             int prm_y_init_local,
                                             int prm_z_init_local,
                                             int prm_rx_init_local,
                                             int prm_ry_init_local,
                                             int prm_rz_init_local) override {
        throwGgafCriticalException("使用不可です。");
        return nullptr;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GgafGroupHead* appendGroupChildAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                             int prm_x_init_local,
                                             int prm_y_init_local,
                                             int prm_z_init_local,
                                             int prm_rx_init_local,
                                             int prm_ry_init_local,
                                             int prm_rz_init_local) override {
        throwGgafCriticalException("使用不可です。");
        return nullptr;
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    GgafDxRegularPolygonBoardModel* const _pRegularPolygonBoardModel;
    /** [r]エフェクト */
    GgafDxRegularPolygonBoardEffect* const _pRegularPolygonBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;

    GgafDxAlign _align;
    GgafDxValign _valign;
    /** 何枚扇を描画するか */
    int _draw_fan_num;
    /** 多角形描画を開始する最初の頂点の角度位置 */
    angle _circumference_begin_position;
public:
    /**
     *
     * @param prm_name
     * @param prm_model_id
     * @param prm_effect_id
     * @param prm_technique
     */
    GgafDxRegularPolygonBoardActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique );

    virtual void processDraw() override;

    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxRegularPolygonBoardActor(); //デストラクタ

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    virtual void setPositionAt(const GgafDxGeometricActor* prm_pActor) override;
    virtual void setPositionAt(const GgafDxGeoElem* prm_pGeoElem) override;
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

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    float getModelWidth();
    float getModelHeight();

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
#endif /*GGAFDXCORE_GGAFDXBOARDACTORD_H_*/
