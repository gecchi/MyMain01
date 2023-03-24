#ifndef GGAF_DX_CUBEMAPMESHSETACTOR_H_
#define GGAF_DX_CUBEMAPMESHSETACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

namespace GgafDx {

/**
 * ���}�b�v���b�V���Z�b�g�A�N�^�[.
 * ���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public MeshSetActor, public ICubeMapActor {

public:

    /** ���f������ */
    CubeMapMeshSetModel* _pCubeMapMeshSetModel;
    /** �G�t�F�N�g���� */
    CubeMapMeshSetEffect* _pCubeMapMeshSetEffect;

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
    CubeMapMeshSetActor(const char* prm_name,
                        const char* prm_model,
                        const char* prm_effect_id,
                        const char* prm_technique,
                        CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
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

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*GGAF_DX_CUBEMAPMESHSETACTOR_H_*/
