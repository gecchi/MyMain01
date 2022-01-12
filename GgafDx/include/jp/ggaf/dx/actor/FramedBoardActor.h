#ifndef GGAF_DX_FRAMEDBOARDACTOR_H_
#define GGAF_DX_FRAMEDBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class FramedBoardActor : public FigureActor {
private:
    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    int isOutOfView() override {
        throwCriticalException("�g�p�s�ł��B");
        return 0;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    bool isOutOfSpacetime() const override {
        throwCriticalException("�g�p�s�ł��B");
        return false;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
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
        throwCriticalException("�g�p�s�ł��B");
        return nullptr;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    GgafCore::GroupHead* appendGroupChildAsFk(GeometricActor* prm_pGeoActor,
                                              int prm_x_init_local,
                                              int prm_y_init_local,
                                              int prm_z_init_local,
                                              int prm_rx_init_local,
                                              int prm_ry_init_local,
                                              int prm_rz_init_local) override {
        throwCriticalException("�g�p�s�ł��B");
        return nullptr;
    }
public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    FramedBoardModel* const _pFramedBoardModel;
    /** [r]�G�t�F�N�g */
    FramedBoardEffect* const _pFramedBoardEffect;
    /** [r]UV�t���b�p�[(���S�̃��C��) */
    UvFlipper* const _pUvFlipper;
    /** [r]UV�t���b�p�[(���̓t���[��) */
    UvFlipper* const _pUvFlipper_frame;

    /** [r]���f���̃I���W�i���̎��̓t���[���̕�(px) */
    const pixcoord _model_frame_width_px;
    /** [r]���f���̃I���W�i���̎��̓t���[���̍���(px) */
    const pixcoord _model_frame_height_px;
    /** [r]���f���̃I���W�i���̒��S�̃��C���̕�(px) */
    const pixcoord _model_center_width_px;
    /** [r]���f���̃I���W�i���̒��S�̃��C���̍���(px) */
    const pixcoord _model_center_height_px;
    /** [r]���f���̃I���W�i���̕�(px) */
    const pixcoord _model_total_width_px;
    /** [r]���f���̃I���W�i���̍���(px) */
    const pixcoord _model_total_height_px;
    /** [r]�p���䂪�܂Ȃ��ŕ\���ł�����E�̕�(px) */
    const scale _lim_center_sx;
    /** [r]�p���䂪�܂Ȃ��ŕ\���ł�����E�̍���(px) */
    const scale _lim_center_sy;

    Align _align;
    Valign _valign;
public:
    FramedBoardActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~FramedBoardActor(); //�f�X�g���N�^

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    inline UvFlipper* getFrameUvFlipper() {
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
#endif /*GGAF_DX_FRAMEDBOARDACTOR_H_*/
