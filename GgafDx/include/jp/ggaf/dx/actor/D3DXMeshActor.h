#ifndef GGAF_DX_D3DXMESHACTOR_H_
#define GGAF_DX_D3DXMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * DirectX���b�V���A�N�^�[.
 * D3DXLoadMeshFromX()�œǂݍ��݁A�\������A�N�^�[<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class D3DXMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** [r]���f�� */
    D3DXMeshModel* _pD3DXMeshModel;
    /** [r]�G�t�F�N�g���� */
    MeshEffect* _pMeshEffect;

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
    D3DXMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect_id,
                  const char* prm_technique,
                  CollisionChecker* prm_pChecker);

    /**
     * D3DXMeshActor��`�� .
     */
    virtual void processDraw() override;

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModel(int prm_model_index) override;

    virtual ~D3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_D3DXMESHACTOR_H_*/
