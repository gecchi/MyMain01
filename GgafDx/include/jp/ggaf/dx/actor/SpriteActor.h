#ifndef GGAF_DX_SPRITEACTORD_H_
#define GGAF_DX_SPRITEACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * �X�v���C�g�A�N�^�[.
 * FigureActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ������A�N�^�[�ł��B<BR>
 * ������|��<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class SpriteActor : public FigureActor {

public:
    /** [r]���f������ */
    SpriteModel* const _pSpriteModel;
    /** [r]�G�t�F�N�g���� */
    SpriteEffect* const _pSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

    float _far_rate;
    Align _align;
    Valign _valign;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    SpriteActor(const char* prm_name,
                const char* prm_model_id,
                const char* prm_effect_id,
                const char* prm_technique,
                Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~SpriteActor();

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
};

}
#endif /*GGAF_DX_SPRITEACTORD_H_*/
