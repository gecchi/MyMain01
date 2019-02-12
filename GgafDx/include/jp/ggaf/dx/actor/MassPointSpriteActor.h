#ifndef GGAF_DX_MASSPOINTSPRITEACTOR_H_
#define GGAF_DX_MASSPOINTSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassPointSpriteModel.h"

namespace GgafDx {

/**
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class MassPointSpriteActor : public MassActor {

public:
    /** [r]���f������ */
    MassPointSpriteModel* const _pMassPointSpriteModel;
    /** [r]�G�t�F�N�g���� */
    MassPointSpriteEffect* const _pMassPointSpriteEffect;
    /** [r]UV�t���b�p�[(�p���p���A�j��) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model_id ���f����`���A������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pStat �g�p����X�e�[�^�X�I�u�W�F�N�g(�g�p���Ȃ��� nullptr�ł悢)
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    MassPointSpriteActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafCore::Status* prm_pStat,
                               Checker* prm_pChecker );

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~MassPointSpriteActor();
};

}
#endif /*GGAF_DX_MASSSPRITEACTOR_H_*/
