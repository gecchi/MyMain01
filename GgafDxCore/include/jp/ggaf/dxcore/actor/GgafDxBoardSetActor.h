#ifndef GGAFDXCORE_GGAFDXBOARDSETACTORD_H_
#define GGAFDXCORE_GGAFDXBOARDSETACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * ���W�ϊ��ς݂̃X�v���C�g�A�N�^�[(��ʕ\�����p) .
 * GgafDxTransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * GgafDxBoardActor�ɁA���ꃂ�f���͈ꊇ�`����s���悤�ɍœK���������A�N�^�[�B<BR>
 * ��]�@�\�Ȃ��A�g��k���@�\�Ȃ��B<BR>
 * �P���\���̂��ߍ����B�����\����A�w�i���Ɏg�p�������B<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetActor : public GgafDxFigureActor {
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
    GgafCore::GgafGroupHead* appendGroupChildAsFk(kind_t prm_kind,
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
    GgafCore::GgafGroupHead* appendGroupChildAsFk(GgafDxGeometricActor* prm_pGeoActor,
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
    GgafDxBoardSetModel* const _pBoardSetModel;
    /** [r]�G�t�F�N�g */
    GgafDxBoardSetEffect* const _pBoardSetEffect;
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
    GgafDxBoardSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //�f�X�g���N�^

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
};

}
#endif /*GGAFDXCORE_GGAFDXBOARDSETACTORD_H_*/
