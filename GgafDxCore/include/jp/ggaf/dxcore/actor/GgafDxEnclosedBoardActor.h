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
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    int isOutOfView() override {
        throwGgafCriticalException("�g�p�s�ł��B");
        return 0;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    bool isOutOfSpacetime() const override {
        throwGgafCriticalException("�g�p�s�ł��B");
        return false;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
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
        throwGgafCriticalException("�g�p�s�ł��B");
        return nullptr;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    GgafCore::GgafGroupHead* addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                             int prm_x_init_local,
                                             int prm_y_init_local,
                                             int prm_z_init_local,
                                             int prm_rx_init_local,
                                             int prm_ry_init_local,
                                             int prm_rz_init_local) override {
        throwGgafCriticalException("�g�p�s�ł��B");
        return nullptr;
    }



public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxEnclosedBoardModel* const _pEnclosedBoardModel;
    /** [r]�G�t�F�N�g */
    GgafDxEnclosedBoardEffect* const _pEnclosedBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* const _pUvFlipper;
    /** [r]��(px) */
    pixcoord _unit_width_px;
    /** [r]����(px) */
    pixcoord _unit_height_px;
//    /** [r]��(px)�̔��� */
//    pixcoord _unit_harf_width_px;
//    /** [r]����(px)�̔��� */
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

    /** �䂪�܂Ȃ����̌��E */
    pixcoord _lim_width_px;
    /** �䂪�܂Ȃ������̌��E */
    pixcoord _lim_height_px;


public:
    GgafDxEnclosedBoardActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxEnclosedBoardActor(); //�f�X�g���N�^

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
