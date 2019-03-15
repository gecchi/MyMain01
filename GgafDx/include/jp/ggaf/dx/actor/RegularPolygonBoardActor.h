#ifndef GGAF_DX_REGULARPOLYGONBOARDACTOR_H_
#define GGAF_DX_REGULARPOLYGONBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[ .
 * TransformedActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �e�N�X�`���̂P�s�N�Z�������̂܂܂P�h�b�g�ŕ\�����������Ɏg�p�B<BR>
 * 2D�[���X�v���C�g�I�ȋ@�\��z�肵���A�N�^�[�B<BR>
 * ��]�@�\(Z����]�̂�)�A�g��k���@�\�@�\����B<BR>
 * @version 1.00
 * @since 2018/10/30
 * @author Masatoshi Tsuge
 */
class RegularPolygonBoardActor : public FigureActor {
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
    RegularPolygonBoardModel* const _pRegularPolygonBoardModel;
    /** [r]�G�t�F�N�g */
    RegularPolygonBoardEffect* const _pRegularPolygonBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

    Align _align;
    Valign _valign;
    /** �������`�悷�邩 */
    int _draw_fan_num;
    /** ���p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu */
    angle _circumference_begin_position;
public:
    /**
     *
     * @param prm_name
     * @param prm_model_id
     * @param prm_effect_id
     * @param prm_technique
     */
    RegularPolygonBoardActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique );

    virtual void processDraw() override;

    virtual void processSettlementBehavior() override {
    }

    virtual ~RegularPolygonBoardActor(); //�f�X�g���N�^

    virtual void setAlign(Align prm_align, Valign prm_valign);
    virtual void setAlign(Align prm_align);
    virtual void setValign(Valign prm_valign);

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;
    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;
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

    /**
     * �`�悷��FAN(��^)�̖������擾
     * @return �`�悷��FAN(��^)�̖���
     */
    int getDrawFanNum() {
        return _draw_fan_num;
    }

    /**
     * �`�悷��FAN(��^)�̖������w�肷�� .
     * @param prm_draw_fan_num �`�悷��FAN(��^)�̖���
     */
    void setDrawFanNum(int prm_draw_fan_num) {
        _draw_fan_num = prm_draw_fan_num;
    }

    /**
     * ���p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu��ݒ肷�� .
     * @param prm_ang �ŏ��̒��_�̊p�x�ʒu
     */
    void setBeginAngPos(angle prm_ang) {
        _circumference_begin_position = prm_ang;
    }

    /**
     * ���݂̑��p�`�`����J�n����ŏ��̒��_�̊p�x�ʒu���擾
     * @return �ŏ��̒��_�̊p�x�ʒu
     */
    angle getBeginAngPos() {
        return _circumference_begin_position;
    }
};

}
#endif /*GGAF_DX_BOARDACTORD_H_*/