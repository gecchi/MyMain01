#ifndef GGAFDX9MESHSETMODEL_H_
#define GGAFDX9MESHSETMODEL_H_
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
 * GgafDx9MeshSetActor�p�̃��f���N���X.
 * GgafDx9MeshSetModel �� D3DXLoadMeshFromX ���g�p�����AX�t�@�C������̃��f���f�[�^��ێ��A�`�悷��N���X�ł��B<BR>
 * <B>�����Ӂ�</B><BR>
 * �E�A�j���[�V�����͓ǂݍ��܂�܂���B�ÓI���f���ł��B(TODO:�����X�L�����b�V����)<BR>
 * �EFace�́A3�p�`�����ʖڂł��B�iD3DXLoadMeshFromX �� 3�p�` or 4�p�`���T�|�[�g�j<BR>
 * �EUV���W�ɂ��āA���_���ƈ�v���Ȃ��Ă��A�Ƃ肠�������Ԃɐݒ肷��B�f�[�^�[������UV���W��(0,0)�ɐݒ肳���B<BR>
 * �E���L���_�@���́A�Ǝ��v�Z�ŕ��ω������B
 *   �v�Z���@�́A���L���_����L�т�eFace�́u�����p�v�^�u�SFace�̐����p���v�́v�ɂ���Ė@���̊|���銄�������܂�B<BR>
 * �EGgafDx9MeshSetModel�͕��בւ��ɂ��C���f�b�N�X�̍œK�����Ȃ����s�Ȃ�Ȃ��B�s�Ȃ�Ȃ��̂�����ł�����B<BR>
 *   ���̂��߁A�`�掞�́AX�t�@�C������ǂݍ��񂾃}�e���A�����X�g�̏��Ԓʂ�ɕ`�悷��B<BR>
 *   X�t�@�C���̃}�e���A�����X�g�̃o������ɂ���ẮAD3DXLoadMeshFromX ���p�t�H�[�}���X��������������Ȃ��B<BR>
 *   �Ⴆ�΁AX�t�@�C���̃}�e���A�����X�g�� {0,0,1,1,2,0,1} �ȏꍇ�A�}�e���A������3�ł��A�`���5����s���邱�ƂɂȂ�B<BR>
 * �Evoid GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshSetModel* prm_pPrimModel) �Ŏ��ۂ̐ݒ���s�Ȃ��Ă��܂��B<BR>
 * <B>���g������</B><BR>
 * �E�P���ȕ��A��{�I�� D3DXLoadMeshFromX �� drawSubset(n) ���`��͍����B<BR>
 * �E���W�b�N�Œ��_�������肽���ꍇ���AD3DXLoadMeshFromX �ɂ��œK�����ꂽ��������Ȃ� ID3DXMesh ����A
 *   ���]�̒��_������o���̂�����ǂ��ꍇ�B<BR>
 * �E�s���S�Ɖ����Ă���X�t�@�C�����A�����ēǂ݂����ꍇ�B�i�f�[�^���[�_�[�I�ȈӖ��Ŏg���ꍇ�j<BR>
 */
class GgafDx9MeshSetModel : public GgafDx9Model {
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

    int _setnum;
    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9* _paIDirect3DIndexBuffer9;


    /** 1���_�̃T�C�Y */
    UINT _size_vertec_unit;
    /** ��{���f�����_�T�C�Y */
    UINT _size_vertecs;
    /** ��{���f�����_�� */
    UINT _nVertices;

    UINT _nFaces;

    INDEXPARAM** _papaIndexParam;

    UINT* _pa_nMaterialListGrp;

    VERTEX** _papaVtxBuffer_org;
    WORD** _papaIdxBuffer_org;

    /** Paul���񃂃f�� */
    Frm::Model3D* _pModel3D;
    /** Paul���񃁃b�V�� */
    Frm::Mesh* _pMeshesFront;




    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9MeshSetModel(char* prm_model_name);

public:

    /**
     * GgafDx9MeshSetModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9MeshSetActor
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
    virtual ~GgafDx9MeshSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHSETMODEL_H_*/
