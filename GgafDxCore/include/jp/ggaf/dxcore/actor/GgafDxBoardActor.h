#ifndef GGAFDXCORE_GGAFDXBOARDACTORD_H_
#define GGAFDXCORE_GGAFDXBOARDACTORD_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * 座標変換済みスプライトアクター .
 * GgafDxTransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * テクスチャの１ピクセルをそのまま１ドットで表示したい時に使用。<BR>
 * 2D擬似スプライト的な機能を想定したアクター。<BR>
 * 回転機能なし、拡大縮小機能機能あり。<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDxBoardActor : public GgafDxDrawableActor {
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
    bool isOutOfUniverse() override {
        throwGgafCriticalException("GgafDxBoardActor::isOutOfUniverse() は使用不可です。");
        return false;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GgafGroupHead* addSubGroupAsFk(actorkind prm_kind,
                                             GgafDxGeometricActor* prm_pGeoActor,
                                             int prm_X_init_local,
                                             int prm_Y_init_local,
                                             int prm_Z_init_local,
                                             int prm_RX_init_local,
                                             int prm_RY_init_local,
                                             int prm_RZ_init_local) override {
        throwGgafCriticalException("GgafDxBoardActor::addSubGroupAsFk() は使用不可です。");
        return nullptr;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GgafGroupHead* addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                             int prm_X_init_local,
                                             int prm_Y_init_local,
                                             int prm_Z_init_local,
                                             int prm_RX_init_local,
                                             int prm_RY_init_local,
                                             int prm_RZ_init_local) override {
        throwGgafCriticalException("GgafDxBoardActor::addSubGroupAsFk() は使用不可です。");
        return nullptr;
    }

    //Z軸回転だけOKにした
//    void rotateAs(GgafDxGeoElem* prm_pActor) override {
//        throwGgafCriticalException("GgafDxBoardActor::rotateAs() は使用不可です。");
//    }
//
//    void rotateAs(GgafDxGeometricActor* prm_pActor) override {
//        throwGgafCriticalException("GgafDxBoardActor::rotateAs() は使用不可です。");
//    }
//
//
//    void addScale(scale dS) override {
//        throwGgafCriticalException("GgafDxBoardActor::addScale() は使用不可です。");
//    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    GgafDxBoardModel* _pBoardModel;
    /** [r]エフェクト */
    GgafDxBoardEffect* _pBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* _pUvFlipper;
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

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);

    virtual void positionAs(GgafDxGeometricActor* prm_pActor) override;
    virtual void positionAs(GgafDxGeoElem* prm_pGeoElem) override;
    virtual void setScale(scale S) override;
    virtual void setScale(scale SX, scale SY) override;
    virtual void setScale(scale SX, scale SY, scale SZ) override;
    virtual void setScaleR(float prm_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override;

};

}
#endif /*GGAFDXCORE_GGAFDXBOARDACTORD_H_*/
