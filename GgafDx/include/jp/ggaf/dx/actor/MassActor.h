#ifndef GGAF_DX_MASSACTOR_H_
#define GGAF_DX_MASSACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {

/**
 * ���b�V���A�N�^�[�i��ʕ\���p�j .
 * X�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �C���X�^���V���O�ɂ��A��ʕ\���ɍœK�������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassActor : public FigureActor {

public:
    /** [r]���f������ */
    MassModel* _pMassModel;
    /** [r]�G�t�F�N�g���� */
    MassEffect* const _pMassEffect;

public:

    /**
     * ���ʌp���p�R���X�g���N�^
     * @param prm_name �A�N�^�[���́i�C�Ӂj
     * @param prm_model ���f����`��
     * @param prm_model_type ���f���^�C�v
     * @param prm_effect_id �G�t�F�N�g��`��
     * @param prm_effect_type �G�t�F�N�g�^�C�v
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    MassActor(const char* prm_name,
              const char* prm_model,
              const char prm_model_type,
              const char* prm_effect_id,
              const char prm_effect_type,
              const char* prm_technique,
              CollisionChecker* prm_pChecker);


    virtual ~MassActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_MASSMESHACTOR_H_*/
