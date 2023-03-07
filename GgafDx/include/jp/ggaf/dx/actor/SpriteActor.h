#ifndef GGAF_DX_SPRITEACTORD_H_
#define GGAF_DX_SPRITEACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * �X�v���C�g�A�N�^�[.
 * �|���S���Ƀe�N�X�`����\��t����<BR>
 * �����[���X�v���C�g�̃A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class SpriteActor : public FigureActor, public IAlignAbleActor {

public:
    /** [r]���f������ */
    SpriteModel* _pSpriteModel;
    /** [r]�G�t�F�N�g���� */
    SpriteEffect* const _pSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

    float _far_rate;
//    Align _align;
//    Valign _valign;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".sprx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    SpriteActor(const char* prm_name,
                const char* prm_model,
                const char* prm_effect_id,
                const char* prm_technique,
                CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

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

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~SpriteActor();
};

}
#endif /*GGAF_DX_SPRITEACTORD_H_*/
