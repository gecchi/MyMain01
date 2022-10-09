#ifndef GGAF_DX_MASSMESHACTOR_H_
#define GGAF_DX_MASSMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassMeshModel.h"

namespace GgafDx {

/**
 * ���b�V���A�N�^�[�i��ʕ\���p�j .
 * X�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �C���X�^���V���O�ɂ��A��ʕ\���ɍœK�������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassMeshActor : public MassActor {

public:
    /** [r]���f������ */
    MassMeshModel* const _pMassMeshModel;
    /** [r]�G�t�F�N�g���� */
    MassMeshEffect* const _pMassMeshEffect;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[���́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���A������ ".meshx" ���������f����`�t�@�C�����ǂݍ��܂��B
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     * @return
     */
    MassMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect_id,
                  const char* prm_technique,
                  Checker* prm_pChecker );


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
    MassMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char prm_model_type,
                  const char* prm_effect_id,
                  const char prm_effect_type,
                  const char* prm_technique,
                  Checker* prm_pChecker);

    virtual ~MassMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_MASSMESHACTOR_H_*/
