#ifndef GGAFDXBOARDSETACTORD_H_
#define GGAFDXBOARDSETACTORD_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

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
class GgafDxBoardSetActor : public GgafDxDrawableActor {
private:
    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    int isOutOfView() override {
        throwGgafCriticalException("GgafDxBoardSetActor::isOutOfView() は使用不可です。");
        return 0;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    bool isOutOfUniverse() override {
        throwGgafCriticalException("GgafDxBoardSetActor::isOutOfUniverse() は使用不可です。");
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
        throwGgafCriticalException("GgafDxBoardSetActor::addSubGroupAsFk() は使用不可です。");
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
        throwGgafCriticalException("GgafDxBoardSetActor::addSubGroupAsFk() は使用不可です。");
        return nullptr;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void changeGeoLocal() override {
        throwGgafCriticalException("GgafDxBoardSetActor::changeGeoLocal() は使用不可です。");
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void changeGeoFinal() override {
        throwGgafCriticalException("GgafDxBoardSetActor::changeGeoFinal() は使用不可です。");
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void rotateAs(GgafDxGeometricActor* prm_pActor) override {
        throwGgafCriticalException("GgafDxBoardSetActor::rotateAs() は使用不可です。");
    }
    void setScale(scale S) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScale() は使用不可です。");
    }
    void setScale(scale SX, scale SY) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScale() は使用不可です。");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScale() は使用不可です。");
    }
    void setScaleR(float prm_rate) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScaleR() は使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScaleR() は使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScaleR() は使用不可です。");
    }
    void addScale(scale dS) override {
        throwGgafCriticalException("GgafDxBoardSetActor::addScale() は使用不可です。");
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    GgafDxBoardSetModel* _pBoardSetModel;
    /** [r]エフェクト */
    GgafDxBoardSetEffect* _pBoardSetEffect;
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
    GgafDxBoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //デストラクタ

    virtual void locateAs(GgafDxGeometricActor* prm_pActor) override;

    virtual void locateAs(GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);
};

}
#endif /*GGAFDXBOARDSETACTORD_H_*/
