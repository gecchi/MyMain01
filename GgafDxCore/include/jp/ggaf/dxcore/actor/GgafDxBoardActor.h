#ifndef GGAFDXCORE_GGAFDXBOARDACTORD_H_
#define GGAFDXCORE_GGAFDXBOARDACTORD_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[ .
 * GgafDxTransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �e�N�X�`���̂P�s�N�Z�������̂܂܂P�h�b�g�ŕ\�����������Ɏg�p�B<BR>
 * 2D�[���X�v���C�g�I�ȋ@�\��z�肵���A�N�^�[�B<BR>
 * ��]�@�\�Ȃ��A�g��k���@�\�@�\����B<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDxBoardActor : public GgafDxDrawableActor {
    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    int isOutOfView() override {
        throwGgafCriticalException("GgafDxBoardActor::isOutOfView() �͎g�p�s�ł��B");
        return 0;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    bool isOutOfUniverse() override {
        throwGgafCriticalException("GgafDxBoardActor::isOutOfUniverse() �͎g�p�s�ł��B");
        return false;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
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
        throwGgafCriticalException("GgafDxBoardActor::addSubGroupAsFk() �͎g�p�s�ł��B");
        return nullptr;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    GgafCore::GgafGroupHead* addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                             int prm_X_init_local,
                                             int prm_Y_init_local,
                                             int prm_Z_init_local,
                                             int prm_RX_init_local,
                                             int prm_RY_init_local,
                                             int prm_RZ_init_local) override {
        throwGgafCriticalException("GgafDxBoardActor::addSubGroupAsFk() �͎g�p�s�ł��B");
        return nullptr;
    }

    //Z����]����OK�ɂ���
//    void rotateAs(GgafDxGeoElem* prm_pActor) override {
//        throwGgafCriticalException("GgafDxBoardActor::rotateAs() �͎g�p�s�ł��B");
//    }
//
//    void rotateAs(GgafDxGeometricActor* prm_pActor) override {
//        throwGgafCriticalException("GgafDxBoardActor::rotateAs() �͎g�p�s�ł��B");
//    }
//
//
//    void addScale(scale dS) override {
//        throwGgafCriticalException("GgafDxBoardActor::addScale() �͎g�p�s�ł��B");
//    }

public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxBoardModel* _pBoardModel;
    /** [r]�G�t�F�N�g */
    GgafDxBoardEffect* _pBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;
    /** [r]��(px) */
    pixcoord _width_px;
    /** [r]����(px) */
    pixcoord _height_px;
    /** [r]��(px)�̔��� */
    pixcoord _harf_width_px;
    /** [r]����(px)�̔��� */
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

    virtual ~GgafDxBoardActor(); //�f�X�g���N�^

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
