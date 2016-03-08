#ifndef GGAFDXCORE_GGAFDXMASSBOARDACTOR_H_
#define GGAFDXCORE_GGAFDXMASSBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMassBoardModel.h"

namespace GgafDxCore {

/**
 * ���W�ϊ��ς݂̃X�v���C�g�A�N�^�[(��ʕ\�����p) .
 * GgafDxTransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * GgafDxBoardActor�ɁA���ꃂ�f���͈ꊇ�`����s���悤�ɍœK���������A�N�^�[�B<BR>
 * ��]�@�\�Ȃ��A�g��k���@�\�Ȃ��B<BR>
 * �P���\���̂��ߍ����B�����\����A�w�i���Ɏg�p�������B<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassBoardActor : public GgafDxMassActor {
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

    void setFaceAngAs(const GgafDxGeoElem* prm_pActor) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setFaceAngAs(const GgafDxGeometricActor* prm_pActor) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setScale(scale S) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setScale(scale SX, scale SY) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setScaleR(float prm_rate) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void addScale(scale dS) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void addScaleX(scale dsx) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void addScaleY(scale dsy) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }
    void addScaleZ(scale dsz) override {
        throwGgafCriticalException("�g�p�s�ł��B");
    }

public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxMassBoardModel* const _pMassBoardModel;
    /** [r]�G�t�F�N�g */
    GgafDxMassBoardEffect* const _pMassBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* const _pUvFlipper;
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
    GgafDxMassBoardActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processSettlementBehavior() override {
    }

    virtual void positionAs(const GgafDxGeometricActor* prm_pActor) override;

    virtual void positionAs(const GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
    float getModelWidth();
    float getModelHeight();

    virtual ~GgafDxMassBoardActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMASSBOARDACTOR_H_*/
