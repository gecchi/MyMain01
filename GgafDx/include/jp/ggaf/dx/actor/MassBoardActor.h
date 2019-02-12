#ifndef GGAF_DX_MASSBOARDACTOR_H_
#define GGAF_DX_MASSBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassBoardModel.h"

namespace GgafDx {

/**
 * 座標変換済みのスプライトアクター(大量表示時用) .
 * TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * BoardActorに、同一モデルは一括描画を行うように最適化したたアクター。<BR>
 * 回転機能なし、拡大縮小機能なし。<BR>
 * 単純表示のため高速。文字表示や、背景等に使用したい。<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassBoardActor : public MassActor {
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
public:
    /** [r]モデルオブジェクトへのポインタ */
    MassBoardModel* const _pMassBoardModel;
    /** [r]エフェクト */
    MassBoardEffect* const _pMassBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

    Align _align;
    Valign _valign;

public:
    MassBoardActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processSettlementBehavior() override {
    }

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);
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
    float getModelWidth();
    float getModelHeight();

    virtual ~MassBoardActor(); //デストラクタ
};

}
#endif /*GGAF_DX_MASSBOARDACTOR_H_*/
