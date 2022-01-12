#ifndef GGAF_DX_CUBEMAPMESHACTOR_H_
#define GGAF_DX_CUBEMAPMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

namespace GgafDx {

/**
 * ���}�b�v���b�V���A�N�^�[.
 * MeshActor ���p�����A���}�b�v�e�N�X�`�������������A�N�^�[�ł��B<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMeshActor : public MeshActor, public ICubeMapActor  {

public:
    /** ���f������ */
    CubeMapMeshModel* _pCubeMapMeshModel;
    /** �G�t�F�N�g���� */
    CubeMapMeshEffect* _pCubeMapMeshEffect;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name ���f�����́i�f�o�b�O���O�ŕ\���A�Ȃ�ł��ǂ��j
     * @param prm_model ���f����`���B������ ".x" ������X�t�@�C�����ɂȂ邱�ƁB
     * @param prm_effect_id �G�t�F�N�g��`���B������ ".fx" �����ăG�t�F�N�g�t�@�C�����ɂȂ邱�ƁB
     * @param prm_technique �G�t�F�N�g�̃e�N�j�b�N��
     * @param prm_pChecker �g�p����`�F�b�J�[�I�u�W�F�N�g�i�`�F�b�J�[���g�p����nullptr�ł悢�j
     */
    CubeMapMeshActor(const char* prm_name,
                            const char* prm_model,
                            const char* prm_effect_id,
                            const char* prm_technique,
                            Checker* prm_pChecker );


    virtual void processDraw() override;


    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~CubeMapMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_CUBEMAPMESHACTOR_H_*/
