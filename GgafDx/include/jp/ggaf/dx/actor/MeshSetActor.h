#ifndef GGAF_DX_MESHSETACTOR_H_
#define GGAF_DX_MESHSETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * ���b�V���A�N�^�[.
 * X�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ��A����ɓ��ꃂ�f�������I�u�W�F�N�g�̒��_�o�b�t�@�������A��ʕ\���ɍœK�������A�N�^�[�ł�<BR>
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class MeshSetActor : public FigureActor {

public:
    /** [r]���f������ */
    MeshSetModel* _pMeshSetModel;
    /** [r]�G�t�F�N�g���� */
    MeshSetEffect* const _pMeshSetEffect;

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
    MeshSetActor(const char* prm_name,
                       const char* prm_model,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       CollisionChecker* prm_pChecker );


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
    MeshSetActor(const char* prm_name,
                 const char* prm_model,
                 const char prm_model_type,
                 const char* prm_effect_id,
                 const char prm_effect_type,
                 const char* prm_technique,
                 CollisionChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * ���f������(MeshSetModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~MeshSetActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_MESHSETACTOR_H_*/
