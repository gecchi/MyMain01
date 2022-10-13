#ifndef GGAF_DX_MASSBOARDACTOR_H_
#define GGAF_DX_MASSBOARDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassBoardModel.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D�\���p�|���A�N�^�[�i��ʕ\���p�j .
 * DirectX �� �C���X�^�V�C���O �ɂ��A���ꃂ�f���͑�ʕ\���ɍœK��<BR>
 * �A���A��]�@�\�͂Ȃ��A�g��k���@�\���Ȃ��B<BR>
 * �����\���Ɏg�p���邱�Ƃ�z��B<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassBoardActor : public MassActor, public IAlignAbleActor {
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
    MassBoardModel* const _pMassBoardModel;
    /** [r]�G�t�F�N�g */
    MassBoardEffect* const _pMassBoardEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

//    Align _align;
//    Valign _valign;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".sprx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @return
     */
    MassBoardActor(const char* prm_name,
                   const char* prm_model,
                   const char* prm_effect_id,
                   const char* prm_technique,
                   Checker* prm_pChecker = nullptr);

    virtual void processSettlementBehavior() override {
    }

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

//    virtual void setAlign(Align prm_align, Valign prm_valign);
//    virtual void setAlign(Align prm_align);
//    virtual void setValign(Valign prm_valign);
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
//    float getModelWidth();
//    float getModelHeight();

    virtual ~MassBoardActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_MASSBOARDACTOR_H_*/
