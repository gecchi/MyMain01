#ifndef GGAF_DX_BOARDSETACTORD_H_
#define GGAF_DX_BOARDSETACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * 座標変換済みのスプライトアクター(大量表示時用) .
 * TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * BoardActorに、同一モデルは一括描画を行うように最適化したたアクター。<BR>
 * 回転機能なし、拡大縮小機能なし。<BR>
 * 単純表示のため高速。文字表示や、背景等に使用したい。<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class BoardSetActor : public FigureActor {
private:
    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    int isOutOfView() override {
        throwCriticalException("使用不可です。");
        return 0;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    bool isOutOfSpacetime() const override {
        throwCriticalException("使用不可です。");
        return false;
    }

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

    void setFaceAngAs(const GeoElem* prm_pActor) override {
        throwCriticalException("使用不可です。");
    }
    void setFaceAngAs(const GeometricActor* prm_pActor) override {
        throwCriticalException("使用不可です。");
    }
    void setScale(scale S) override {
        throwCriticalException("使用不可です。");
    }
    void setScale(scale SX, scale SY) override {
        throwCriticalException("使用不可です。");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwCriticalException("使用不可です。");
    }
    void setScaleR(float prm_rate) override {
        throwCriticalException("使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwCriticalException("使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwCriticalException("使用不可です。");
    }
    void addScale(scale dS) override {
        throwCriticalException("使用不可です。");
    }
    void addScaleX(scale dsx) override {
        throwCriticalException("使用不可です。");
    }
    void addScaleY(scale dsy) override {
        throwCriticalException("使用不可です。");
    }
    void addScaleZ(scale dsz) override {
        throwCriticalException("使用不可です。");
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    BoardSetModel* const _pBoardSetModel;
    /** [r]エフェクト */
    BoardSetEffect* const _pBoardSetEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;
    /** [r]幅(px) */
    pixcoord _width_px;
    /** [r]高さ(px) */
    pixcoord _height_px;
    /** [r]幅(px)の半分 */
    pixcoord _harf_width_px;
    /** [r]高さ(px)の半分 */
    pixcoord _harf_height_px;
    Align _align;
    Valign _valign;

public:
    BoardSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~BoardSetActor(); //デストラクタ

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
    float getModelWidth();
    float getModelHeight();
};

}
#endif /*GGAF_DX_BOARDSETACTORD_H_*/
