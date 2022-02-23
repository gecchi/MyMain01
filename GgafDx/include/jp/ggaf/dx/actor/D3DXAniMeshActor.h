#ifndef GGAF_DX_D3DXANIMESHACTOR_H_
#define GGAF_DX_D3DXANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"
namespace GgafDx {

/**
 * ���ݖ��g�p<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** ���f�� */
    D3DXAniMeshModel* _pD3DXAniMeshModel;
    /** �G�t�F�N�g���� */
    D3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** �p�y�b�^�[�i�A�j���[�V��������I�u�W�F�N�g) */
    Puppeteer* _pPuppeteer;
    BoneAniMeshWorldMatStack _stackWorldMat;
    LPD3DXANIMATIONSET* _papAnimationSet;

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
    D3DXAniMeshActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual ~D3DXAniMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_D3DXANIMESHACTOR_H_*/
