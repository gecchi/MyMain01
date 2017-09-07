#ifndef GGAFDXCORE_GGAFDXFRAMEDBOARDACTOR_H_
#define GGAFDXCORE_GGAFDXFRAMEDBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class GgafDxFramedBoardActor : public GgafDxFigureActor {
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
    GgafDxFramedBoardModel* const _pFramedBoardModel;
    /** [r]エフェクト */
    GgafDxFramedBoardEffect* const _pFramedBoardEffect;
    /** [r]UVフリッパー(中心のメイン) */
    GgafDxUvFlipper* const _pUvFlipper;
    /** [r]UVフリッパー(周囲フレーム) */
    GgafDxUvFlipper* const _pUvFlipper_frame;

    /** [r]モデルのオリジナルの周囲フレームの幅(px) */
    const pixcoord _model_frame_width_px;
    /** [r]モデルのオリジナルの周囲フレームの高さ(px) */
    const pixcoord _model_frame_height_px;
    /** [r]モデルのオリジナルの中心のメインの幅(px) */
    const pixcoord _model_center_width_px;
    /** [r]モデルのオリジナルの中心のメインの高さ(px) */
    const pixcoord _model_center_height_px;
    /** [r]モデルのオリジナルの幅(px) */
    const pixcoord _model_total_width_px;
    /** [r]モデルのオリジナルの高さ(px) */
    const pixcoord _model_total_height_px;
    /** [r]角がゆがまないで表示できる限界の幅(px) */
    const scale _lim_center_sx;
    /** [r]角がゆがまないで表示できる限界の高さ(px) */
    const scale _lim_center_sy;

    GgafDxAlign _align;
    GgafDxValign _valign;
public:
    GgafDxFramedBoardActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxFramedBoardActor(); //デストラクタ

    virtual void setPositionAt(const GgafDxGeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    inline GgafDxUvFlipper* getFrameUvFlipper() {
        return _pUvFlipper_frame;
    }
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

    void setWidth(coord prm_width);
    void setHeight(coord prm_height);
    void addWidth(coord prm_width);
    void addHeight(coord prm_height);
    coord getWidth();
    coord getHeight();
};

}
#endif /*GGAFDXCORE_GGAFDXFRAMEDBOARDACTOR_H_*/
