#ifndef GGAF_DX_D3DXMESHMODEL_H_
#define GGAF_DX_D3DXMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


namespace GgafDx {

/**
 * ���b�V�����f���N���X(D3DXActor�p).
 * D3DXMeshModel �� D3DXLoadMeshFromX ���g�p���āAX�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �`�悷��@�\���������ÓI���f���p�̃N���X�ł��B
 * ��������
 * �ED3DXLoadMeshFromX ���g�p���ēǂݍ��ނ��߁A���G��X�t�@�C���ł����Ȃ��ǂ݂��ݕ`��ł���B
 * �E�@���D��B���f�����O�c�[���ō�����Ƃ���̌����ڂɂȂ�B
 * ���Z����
 * �E���̃��f���N���X�S�ɔ�ׂāA���x�ʂŗ��B�ǂݍ���� DrawSubset() ���邾���B
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class D3DXMeshModel : public Model {
    friend class ModelManager;

public:
    /** ���b�V��(�C���X�^���X�̓��f�����j */
    LPD3DXMESH _pID3DXMesh;
    /** D3DXLoadMeshFromX�̃I�v�V���� */
    DWORD _dwOptions;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model ���f���̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     * @param prm_dwOptions D3DXLoadMeshFromX�̃I�v�V����
     * @return
     */
    D3DXMeshModel(const char* prm_model, DWORD prm_dwOptions);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�D3DXMeshModelManager�ł���<BR>
     */
    virtual ~D3DXMeshModel(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_D3DXMESHMODEL_H_*/
