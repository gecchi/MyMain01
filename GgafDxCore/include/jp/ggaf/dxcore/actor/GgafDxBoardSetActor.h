#ifndef GGAFDXBOARDSETACTORD_H_
#define GGAFDXBOARDSETACTORD_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

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
class GgafDxBoardSetActor : public GgafDxDrawableActor {
private:
    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    int isOutOfView() override {
        throwGgafCriticalException("GgafDxBoardSetActor::isOutOfView() �͎g�p�s�ł��B");
        return 0;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    bool isOutOfUniverse() override {
        throwGgafCriticalException("GgafDxBoardSetActor::isOutOfUniverse() �͎g�p�s�ł��B");
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
        throwGgafCriticalException("GgafDxBoardSetActor::addSubGroupAsFk() �͎g�p�s�ł��B");
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
        throwGgafCriticalException("GgafDxBoardSetActor::addSubGroupAsFk() �͎g�p�s�ł��B");
        return nullptr;
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void changeGeoLocal() override {
        throwGgafCriticalException("GgafDxBoardSetActor::changeGeoLocal() �͎g�p�s�ł��B");
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void changeGeoFinal() override {
        throwGgafCriticalException("GgafDxBoardSetActor::changeGeoFinal() �͎g�p�s�ł��B");
    }

    /**
     * �g�p�s�̂��߁Aprivate��override
     * @return
     */
    void rotateAs(GgafDxGeometricActor* prm_pActor) override {
        throwGgafCriticalException("GgafDxBoardSetActor::rotateAs() �͎g�p�s�ł��B");
    }
    void setScale(scale S) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScale() �͎g�p�s�ł��B");
    }
    void setScale(scale SX, scale SY) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScale() �͎g�p�s�ł��B");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScale() �͎g�p�s�ł��B");
    }
    void setScaleR(float prm_rate) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScaleR() �͎g�p�s�ł��B");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScaleR() �͎g�p�s�ł��B");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwGgafCriticalException("GgafDxBoardSetActor::setScaleR() �͎g�p�s�ł��B");
    }
    void addScale(scale dS) override {
        throwGgafCriticalException("GgafDxBoardSetActor::addScale() �͎g�p�s�ł��B");
    }

public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    GgafDxBoardSetModel* _pBoardSetModel;
    /** [r]�G�t�F�N�g */
    GgafDxBoardSetEffect* _pBoardSetEffect;
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
    GgafDxBoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //�f�X�g���N�^

    virtual void locateAs(GgafDxGeometricActor* prm_pActor) override;

    virtual void locateAs(GgafDxGeoElem* prm_pGeoElem) override;

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign = VALIGN_TOP);
};

}
#endif /*GGAFDXBOARDSETACTORD_H_*/
