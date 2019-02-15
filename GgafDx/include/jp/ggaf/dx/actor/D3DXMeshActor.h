#ifndef GGAF_DX_D3DXMESHACTOR_H_
#define GGAF_DX_D3DXMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * DirectX���b�V���A�N�^�[.
 * FigureActor ���p�����AX�t�@�C����`�̃��b�V���\���@�\��<BR>
 * �ǉ������A�N�^�[�ł�<BR>
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
    D3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         Checker* prm_pChecker);

    /**
     * D3DXMeshActor��`�� .
     */
    virtual void processDraw() override;

    virtual ~D3DXMeshActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_D3DXMESHACTOR_H_*/
