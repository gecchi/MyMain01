#ifndef GGAF_DX_FRAMEDSPRITEACTOR_H_
#define GGAF_DX_FRAMEDSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * �g����̃X�v���C�g�A�N�^�[.
 * @version 1.00
 * @since 2022/01/25
 * @author Masatoshi Tsuge
 */
class FramedSpriteActor : public FigureActor {

public:
    /** [r]���f������ */
    FramedSpriteModel* const _pFramedSpriteModel;
    /** [r]�G�t�F�N�g���� */
    FramedSpriteEffect* const _pFramedSpriteEffect;
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

    float _far_rate;
    Align _align;
    Valign _valign;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    FramedSpriteActor(const char* prm_name,
                const char* prm_model,
                const char* prm_effect_id,
                const char* prm_technique,
                Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~FramedSpriteActor();

    inline UvFlipper* getFrameUvFlipper() {
        return _pUvFlipper_frame;
    }

    /**
     * �����̍��W�ł������\�� .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }


    void setWidth(coord prm_width);
    void setHeight(coord prm_height);
    void addWidth(coord prm_width);
    void addHeight(coord prm_height);
    coord getWidth();
    coord getHeight();
};

}
#endif /*GGAF_DX_FRAMEDSPRITEACTOR_H_*/
