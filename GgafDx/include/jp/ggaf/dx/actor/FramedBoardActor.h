#ifndef GGAF_DX_FRAMEDBOARDACTOR_H_
#define GGAF_DX_FRAMEDBOARDACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D�\���p�g����̔|���A�N�^�[ .
 * ������g�債�Ă��A�l���̉摜�͊g�傳�܂���B<BR>
 * �E�B���h�E�\�����ɗ��p��z��<BR>
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class FramedBoardActor : public FigureActor, public IAlignAbleActor {
private:

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
    FramedBoardModel* _pFramedBoardModel;
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
    /** [r]���f���̃I���W�i���̑S�̂̕�(px) */
    const pixcoord _model_total_width_px;
    /** [r]���f���̃I���W�i���̑S�̂̍���(px) */
    const pixcoord _model_total_height_px;
    /** [r]�p���䂪�܂Ȃ��ŕ\���ł�����E�� _sx */
    const scale _lim_center_sx;
    /** [r]�p���䂪�܂Ȃ��ŕ\���ł�����E�� _sy */
    const scale _lim_center_sy;

//    Align _align;
//    Valign _valign;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".fsprx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @return
     */
    FramedBoardActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique );

    virtual void processDraw() override;

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

//    virtual void setAlign(Align prm_align, Valign prm_valign);
//    virtual void setAlign(Align prm_align);
//    virtual void setValign(Valign prm_valign);

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

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }
    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~FramedBoardActor();
};

}
#endif /*GGAF_DX_FRAMEDBOARDACTOR_H_*/
