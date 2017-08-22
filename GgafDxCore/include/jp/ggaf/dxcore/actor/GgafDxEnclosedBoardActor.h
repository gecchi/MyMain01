#ifndef GGAFDXCORE_GGAFDXBOARDSETACTORD_H_
#define GGAFDXCORE_GGAFDXBOARDSETACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class GgafDxEnclosedBoardActor : public GgafDxFigureActor {
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
    GgafCore::GgafGroupHead* addSubGroupAsFk(actorkind prm_kind,
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
    GgafCore::GgafGroupHead* addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
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
    GgafDxEnclosedBoardModel* const _pEnclosedBoardModel;
    /** [r]エフェクト */
    GgafDxEnclosedBoardEffect* const _pEnclosedBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;
    /** [r]幅(px) */
    pixcoord _unit_width_px;
    /** [r]高さ(px) */
    pixcoord _unit_height_px;
//    /** [r]幅(px)の半分 */
//    pixcoord _unit_harf_width_px;
//    /** [r]高さ(px)の半分 */
//    pixcoord _unit_harf_height_px;
    GgafDxAlign _align;
    GgafDxValign _valign;
    //rw
    pixcoord _width_px;
    //rw
    pixcoord _height_px;
//    double _top_edge_width_rate;
//    double _bottom_edge_width_rate;
//    double _left_edge_width_rate;
//    double _right_edge_width_rate;

    /** ゆがまない幅の限界 */
    pixcoord _lim_width_px;
    /** ゆがまない高さの限界 */
    pixcoord _lim_height_px;


public:
    GgafDxEnclosedBoardActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxEnclosedBoardActor(); //デストラクタ

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

    void setWidth(pixcoord prm_width_px) {
        _width_px = prm_width_px;
    }

    void setHeight(pixcoord prm_height_px) {
        _height_px = prm_height_px;
    }

    void addWidth(pixcoord prm_px) {
        _width_px += prm_px;
    }

    void addHeight(pixcoord prm_px) {
        _height_px += prm_px;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXBOARDSETACTORD_H_*/
