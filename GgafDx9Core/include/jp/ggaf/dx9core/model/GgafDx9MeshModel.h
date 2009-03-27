#ifndef GGAFDX9MESHMODEL_H_
#define GGAFDX9MESHMODEL_H_
namespace GgafDx9Core {


// ���̃N���X�� Paul Coppens ����̍쐬���ꂽ�AX�t�@�C����ǂݍ��ރT���v��
// �����ɁA�Ǝ��ɏC���i��f�o�b�O�j�����N���X���g�p���Ă��܂��B
// ���肪�Ƃ� Paul�B
//
// �y�Ώہz
// Frm ���O��Ԃ̃N���X
//
// �yLoading and displaying .X files without DirectX �z
// http://www.gamedev.net/reference/programming/features/xfilepc/
//
//                                         2009/03/06 Masatoshi Tsuge

/**
 * GgafDx9MeshActor�p�̃��f���N���X.
 * GgafDx9MeshModel �� D3DXLoadMeshFromX ���g�p�����AX�t�@�C������̃��f���f�[�^��ێ��A�`�悷��N���X�ł��B<BR>
 * �����Ӂ�<BR>
 * �E�A�j���[�V�����͓ǂݍ��܂�܂���B�ÓI���f���ł��B(TODO:�����X�L�����b�V��������)
 * �EFace�́A3�p�`�����ʖڂł��B�iD3DXLoadMeshFromX �� 3�p�` or 4�p�`���T�|�[�g�j<BR>
 * �EUV���W�ɂ��āA���_���ƈ�v���Ȃ��Ă��A�Ƃ肠�������Ԃɐݒ肷��B�f�[�^�[������UV���W��(0,0)�ɐݒ肳���B<BR>
 * �E���L���_�@���́A�Ǝ��v�Z�ŕ��ω������B
 *   �v�Z���@�́A���L���_����L�т�eFace�́u�����p�v�^�u�SFace�̐����p���v�́v�ɂ���Ė@���̊|���銄�������܂�B<BR>
 * �EGgafDx9MeshModel�͕��בւ��ɂ��C���f�b�N�X�̍œK�����Ȃ����s�Ȃ�Ȃ��B�s�Ȃ�Ȃ��̂�����ł�����B<BR>
 *   ���̂��߁A�`�掞�́AX�t�@�C������ǂݍ��񂾃}�e���A�����X�g�̏��Ԓʂ�ɕ`�悷��B<BR>
 *   X�t�@�C���̃}�e���A�����X�g�̃o������ɂ���ẮAD3DXLoadMeshFromX ���p�t�H�[�}���X��������������Ȃ��B<BR>
 *   �Ⴆ�΁AX�t�@�C���̃}�e���A�����X�g�� {0,0,1,1,2,0,1} �ȏꍇ�A�}�e���A������3�ł��A�`���5����s���邱�ƂɂȂ�B<BR>
 * �Evoid GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pPrimModel) �Ŏ��ۂ̐ݒ���s�Ȃ��Ă��܂��B
 * ���g������<BR>
 * �E�P���ȕ��A��{�I�� D3DXLoadMeshFromX �� drawSubset(n) ���`��͍����B<BR>
 * �E���W�b�N�Œ��_�������肽���ꍇ���AD3DXLoadMeshFromX �ɂ��œK�����ꂽ��������Ȃ� ID3DXMesh ����A
 *   ���]�̒��_������o���̂�����ǂ��ꍇ�B<BR>
 * �E�s���S�Ɖ����Ă���X�t�@�C�����A�����ēǂ݂����ꍇ�B�i�f�[�^���[�_�[�I�ȈӖ��Ŏg���ꍇ�j<BR>
 */
class GgafDx9MeshModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:

    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    struct VERTEX {
        float x, y, z; // ���_���W
        float nx, ny, nz; // �@��
        DWORD color; // ���_�̐F
        float tu, tv; // �e�N�X�`�����W
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** �}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9_default;
    /** �e�N�X�`���z��(�C���X�^���X�̓e�N�X�`�����A���f���Ƃ͕ʊǗ��j */
    GgafDx9TextureConnection** _papTextureCon;

    UINT _size_vertecs;
    /** 1���_�̃T�C�Y */
    UINT _size_vertec_unit;
    /** 1���_�̃T�C�Y */
    DWORD _dwNumMaterials;
    INDEXPARAM* _paIndexParam;

    UINT _nMaterialListGrp;

    VERTEX* _paVtxBuffer_org;
    WORD* _paIdxBuffer_org;

    /** Paul���񃂃f�� */
    Frm::Model3D* _pModel3D;
    /** Paul���񃁃b�V�� */
    Frm::Mesh* _pMeshesFront;




    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9MeshModel(char* prm_model_name);

public:

    /**
     * GgafDx9MeshModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9MeshActor
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
    virtual ~GgafDx9MeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHMODEL_H_*/
