#ifndef GGAF_DX_DYNAD3DXMESHACTOR_H_
#define GGAF_DX_DYNAD3DXMESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

//���ӁF���̃N���X�͌��ݖ��g�p�ł��B�폜�\��B
//     �Œ�@�\�p�C�v���C�����ɒ��_���������̂��ߍ쐬�������A
//     ���݂͑S�ăv���O���}�u���V�F�[�_�[�ł��邽�߁A�����g��Ȃ��B
/**
 * ���b�V���A�N�^�[.
 * X�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł��B<BR>
 * D3DXMeshActor �Ƃ̈Ⴂ�́A���_�o�b�t�@�ɒ��ڃA�N�Z�X�����Ƃɍl�����āA<BR>
 * D3DXMESH_DYNAMIC �I�v�V�������g�p���Ă���Ƃ��낾���ł��B<BR>
 * ���_�����b�N����ꍇ��D3DXMeshActor�ł͂Ȃ��A��������p�����Ă��������B<BR>
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DynaD3DXMeshActor : public FigureActor {

public:
    static DWORD FVF;
    D3DXMeshModel* _pD3DXMeshModel;
    /** �G�t�F�N�g���� */
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
    DynaD3DXMeshActor(const char* prm_name,
                      const char* prm_model,
                      const char* prm_effect_id,
                      const char* prm_technique,
                      CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * ���f������(MeshModel)��؂�ւ���i�\�����؂�ւ��܂��j .
     * @param prm_model_index ���f�������ێ����X�g�̃C���f�b�N�X�B
     *                        �ŏ���   addModel() �ɐ؂�ւ� => 0 ��ݒ�
     *                        �Q��ڂ� addModel() �ɐ؂�ւ� => 1 ��ݒ�
     *                        �R��ڂ� addModel() �ɐ؂�ւ� => 2 ��ݒ�
     *                         �c
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~DynaD3DXMeshActor();
};

}
#endif /*GGAF_DX_DYNAD3DXMESHACTOR_H_*/
