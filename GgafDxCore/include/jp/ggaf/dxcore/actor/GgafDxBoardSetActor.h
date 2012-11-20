#ifndef GGAFDXBOARDSETACTORD_H_
#define GGAFDXBOARDSETACTORD_H_
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
        return 0;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    bool isOutOfUniverse() override {
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
        return nullptr;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void changeGeoLocal() override {
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void changeGeoFinal() override {
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void rotateWith(GgafDxGeometricActor* prm_pActor) override {
    }
    void setScale(scale S) override {
    }
    void setScale(scale SX, scale SY) override {
    }
    void setScale(scale SX, scale SY, scale SZ) override {
    }
    void setScaleR(float prm_rate) override {
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
    }
    void addScale(scale dS) override {
    }

public:
    int _draw_set_num;
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
    GgafDxAlign _align;
    GgafDxValign _valign;

    GgafDxBoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //デストラクタ

    virtual void locateWith(GgafDxGeometricActor* prm_pActor) override;

    virtual void locateWith(GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);
};

}
#endif /*GGAFDXBOARDSETACTORD_H_*/
