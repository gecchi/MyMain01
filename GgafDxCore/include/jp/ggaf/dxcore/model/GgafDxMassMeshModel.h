#ifndef GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * Mass���b�V�����f���N���X(GgafDxMeshActor�p) .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    class VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
    public:
        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
        float tu, tv;     // �e�N�X�`�����W
    };

    /** ���_�o�b�t�@�i���f���j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_model;
    /** ���_�o�b�t�@�i�C���X�^���X�F���[���h�ϊ��s����A�}�e���A���J���[���j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_instacedata;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** �V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;

    /** �P���_�̃T�C�Y�i���f���j */
    UINT _size_vertex_unit_model;
    /** �P���_�̃T�C�Y�i�C���X�^���X�j */
    UINT _size_vertex_unit_instacedata;
    /** �P���f�����_�T�C�Y�v */
    UINT _size_vertices_model;
    /** ���f�����_�� */
    UINT _nVertices;
    /** ���f���ʂ̐� */
    UINT _nFaces;

    VERTEX_model* _paVtxBuffer_data_model;

    WORD* _paIndexBuffer_data;

    void (*_pFunc_CreateVertexInstaceData)(D3DVERTEXELEMENT9** out_paVtxInstaceDataElement,
                                           int* out_elem_num,
                                           UINT* out_size_vertex_unit_instacedata,
                                           void** out_pInstancedata);
    void* _pInstancedata;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxMassMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMassMeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETMODEL_H_*/
