#ifndef GGAF_DX_BOARDSETACTORD_H_
#define GGAF_DX_BOARDSETACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * ���W�ϊ��ς݂̃X�v���C�g�A�N�^�[(��ʕ\�����p) .
 * TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * BoardActor�ɁA���ꃂ�f���͈ꊇ�`����s���悤�ɍœK���������A�N�^�[�B<BR>
 * ��]�@�\�Ȃ��A�g��k���@�\�Ȃ��B<BR>
 * �P���\���̂��ߍ����B�����\����A�w�i���Ɏg�p�������B<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class BoardSetActor : public FigureActor {
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

    void setFaceAngAs(const GeoElem* prm_pActor) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setFaceAngAs(const GeometricActor* prm_pActor) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setScale(scale S) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setScale(scale SX, scale SY) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setScaleR(float prm_rate) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void addScale(scale dS) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void addScaleX(scale dsx) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void addScaleY(scale dsy) override {
        throwCriticalException("�g�p�s�ł��B");
    }
    void addScaleZ(scale dsz) override {
        throwCriticalException("�g�p�s�ł��B");
    }

public:
    /** [r]���f���I�u�W�F�N�g�ւ̃|�C���^ */
    BoardSetModel* const _pBoardSetModel;
    /** [r]�G�t�F�N�g */
    BoardSetEffect* const _pBoardSetEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;
    /** [r]��(px) */
    pixcoord _width_px;
    /** [r]����(px) */
    pixcoord _height_px;
    /** [r]��(px)�̔��� */
    pixcoord _harf_width_px;
    /** [r]����(px)�̔��� */
    pixcoord _harf_height_px;
    Align _align;
    Valign _valign;

public:
    BoardSetActor(const char* prm_name,
                        const char* prm_model_id,
                        const char* prm_effect_id,
                        const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~BoardSetActor(); //�f�X�g���N�^

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
    float getModelWidth();
    float getModelHeight();
};

}
#endif /*GGAF_DX_BOARDSETACTORD_H_*/
