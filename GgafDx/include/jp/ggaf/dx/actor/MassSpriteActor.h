#ifndef GGAF_DX_MASSSPRITEACTOR_H_
#define GGAF_DX_MASSSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassSpriteModel.h"

namespace GgafDx {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[.
 * FigureActor ���p�����A�|���S���Ƀe�N�X�`����\��t����<BR>
 * �[���X�v���C�g�@�\��ǉ����A���������`��ɍœK�����ꂽ�A�N�^�[�ł��B<BR>
 * setMaterialColor() �ɂ��ʐF�w��͂ł��܂���(�Z�b�g���Ă����ʂ�����܂���)<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteActor : public MassActor {

public:
    /** [r]���f������ */
    MassSpriteModel* const _pMassSpriteModel;
    /** [r]�G�t�F�N�g���� */
    MassSpriteEffect* const _pMassSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

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
    MassSpriteActor(const char* prm_name,
                    const char* prm_model,
                    const char* prm_effect_id,
                    const char* prm_technique,
                    Checker* prm_pChecker );

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~MassSpriteActor();
};

}
#endif /*GGAF_DX_MASSSPRITEACTOR_H_*/
