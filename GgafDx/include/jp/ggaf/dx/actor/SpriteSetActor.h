#ifndef GGAF_DX_SPRITESETACTOR_H_
#define GGAF_DX_SPRITESETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[.
 * �|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A���������`��ɍœK�����ꂽ�A�N�^�[�ł��B<BR>
 * setMaterialColor() �ɂ��ʐF�w��͂ł��܂���(�Z�b�g���Ă����ʂ�����܂���)<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class SpriteSetActor : public FigureActor {

public:
    /** [r]���f������ */
    SpriteSetModel* const _pSpriteSetModel;
    /** [r]�G�t�F�N�g���� */
    SpriteSetEffect* const _pSpriteSetEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

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
    SpriteSetActor(const char* prm_name,
                   const char* prm_model,
                   const char* prm_effect_id,
                   const char* prm_technique,
                   CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~SpriteSetActor();

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
};

}
#endif /*GGAF_DX_SPRITESETACTOR_H_*/
