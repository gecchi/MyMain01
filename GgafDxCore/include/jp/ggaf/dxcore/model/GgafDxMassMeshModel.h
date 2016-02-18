#ifndef GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"


#define MAX_INSTACE 256
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

    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    class VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
    public:
        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
        float tu, tv;     // �e�N�X�`�����W
    };

    class VERTEX_instancedata {
    public:
        float _11, _12, _13, _14;   // : TEXCOORD1  World�ϊ��s��A�P�s��
        float _21, _22, _23, _24;   // : TEXCOORD2  World�ϊ��s��A�Q�s��
        float _31, _32, _33, _34;   // : TEXCOORD3  World�ϊ��s��A�R�s��
        float _41, _42, _43, _44;   // : TEXCOORD4  World�ϊ��s��A�S�s��
        float r, g, b, a;           // : TEXCOORD5  �}�e���A���J���[
    };

    /** ���_��FVF */
//    static DWORD FVF;
    /** ���_�o�b�t�@�i���f���j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_model;
    /** ���_�o�b�t�@�i�C���X�^���X�F���[���h�ϊ��s����A�}�e���A���J���[���j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_instacedata;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** �V�F�[�_�[���͒��_�t�H�[�}�b�g */
    LPDIRECT3DVERTEXDECLARATION9 _pIDirect3DVertexDeclaration9;

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

    /** �}�e���A�����X�g�̘A���œ���̃}�e���A���ԍ��̉�i�O���[�v�j������邩 */
    UINT* _paUint_material_list_grp_num;

    VERTEX_model* _paVtxBuffer_org_model;

    VERTEX_instancedata _aInstancedata[MAX_INSTACE];

    WORD* _paIdxBuffer_org;

    /** Paul���񃂃f�� */
    Frm::Model3D* _pModel3D;
    /** Paul���񃁃b�V�� */
    Frm::Mesh* _pMeshesFront;

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
