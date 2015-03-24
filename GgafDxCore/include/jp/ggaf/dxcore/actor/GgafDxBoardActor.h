#ifndef GGAFDXCORE_GGAFDXBOARDACTORD_H_
#define GGAFDXCORE_GGAFDXBOARDACTORD_H_
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
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDxBoardActor : public GgafDxFigureActor {
    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    int isOutOfView() override {
        throwGgafCriticalException("GgafDxBoardActor::isOutOfView() は使用不可です。");
        return 0;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    bool isOutOfSpacetime() const override {
        throwGgafCriticalException("GgafDxBoardActor::isOutOfSpacetime() は使用不可です。");
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
        throwGgafCriticalException("GgafDxBoardActor::addSubGroupAsFk() は使用不可です。");
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
        throwGgafCriticalException("GgafDxBoardActor::addSubGroupAsFk() は使用不可です。");
        return nullptr;
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    GgafDxBoardModel* const _pBoardModel;
    /** [r]エフェクト */
    GgafDxBoardEffect* const _pBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;

    GgafDxAlign _align;
    GgafDxValign _valign;

public:
    /**
     *
     * @param prm_name
     * @param prm_model_id
     * @param prm_effect_id
     * @param prm_technique
     */
    GgafDxBoardActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique );

    virtual void processDraw() override;

    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardActor(); //デストラクタ

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    virtual void positionAs(const GgafDxGeometricActor* prm_pActor) override;
    virtual void positionAs(const GgafDxGeoElem* prm_pGeoElem) override;
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

    /**
     * α設定.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;
    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    float getModelWidth();
    float getModelHeight();
};

}
#endif /*GGAFDXCORE_GGAFDXBOARDACTORD_H_*/
