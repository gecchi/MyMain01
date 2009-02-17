#ifndef GGAFDX9PRIMITIVEMODEL_H_
#define GGAFDX9PRIMITIVEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PrimitiveActor�p���f���N���X.
 */
class GgafDx9PrimitiveModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:
    struct VERTEX {
        float x, y, z; // ���_���W
        float nx, ny, nz; // �@��
        DWORD color; // ���_�̐F
        float tu, tv; // �e�N�X�`�����W
    };

    /** VERTEX��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** �}�e���A�� */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** �e�N�X�`��(�A�j���[�V�����p�^�[���j */
    GgafDx9TextureConnection* _pTextureCon;


    UINT _size_vertecs;
    /** 1���_�̃T�C�Y */
    UINT _size_vertec_unit;

    VERTEX* _paVtxBuffer_org;
    WORD _paIdxBuffer_org;

    Frm::Model3D* _pModel3D;
    Frm::Mesh* _pMeshesFront;




    /**
     * �R���X�g���N�^<BR>
     * @param prm_spritemodel_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9PrimitiveModel(char* prm_spritemodel_name);

public:

    /**
     * GgafDx9PrimitiveModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9PrimitiveActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9PrimitiveModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9PRIMITIVEMODEL_H_*/
