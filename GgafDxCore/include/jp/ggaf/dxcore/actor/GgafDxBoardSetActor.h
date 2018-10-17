#ifndef GGAFDXCORE_GGAFDXBOARDSETACTORD_H_
#define GGAFDXCORE_GGAFDXBOARDSETACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * 座標変換済みのスプライトアクター(大量表示時用) .
 * GgafDxTransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * GgafDxBoardActorに、同一モデルは一括描画を行うように最適化したたアクター。<BR>
 * 回転機能なし、拡大縮小機能なし。<BR>
 * 単純表示のため高速。文字表示や、背景等に使用したい。<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetActor : public GgafDxFigureActor {
private:
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

    void setFaceAngAs(const GgafDxGeoElem* prm_pActor) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setFaceAngAs(const GgafDxGeometricActor* prm_pActor) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setScale(scale S) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setScale(scale SX, scale SY) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setScaleR(float prm_rate) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwGgafCriticalException("使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwGgafCriticalException("使用不可です。");
    }
    void addScale(scale dS) override {
        throwGgafCriticalException("使用不可です。");
    }
    void addScaleX(scale dsx) override {
        throwGgafCriticalException("使用不可です。");
    }
    void addScaleY(scale dsy) override {
        throwGgafCriticalException("使用不可です。");
    }
    void addScaleZ(scale dsz) override {
        throwGgafCriticalException("使用不可です。");
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    GgafDxBoardSetModel* const _pBoardSetModel;
    /** [r]エフェクト */
    GgafDxBoardSetEffect* const _pBoardSetEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;
    /** [r]幅(px) */
    pixcoord _width_px;
    /** [r]高さ(px) */
    pixcoord _height_px;
    /** [r]幅(px)の半分 */
    pixcoord _harf_width_px;
    /** [r]高さ(px)の半分 */
    pixcoord _harf_height_px;
    GgafDxAlign _align;
    GgafDxValign _valign;

public:
    GgafDxBoardSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //デストラクタ

    virtual void setPositionAt(const GgafDxGeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
    float getModelWidth();
    float getModelHeight();
};

}
#endif /*GGAFDXCORE_GGAFDXBOARDSETACTORD_H_*/
