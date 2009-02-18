#ifndef GGAFDX9PRIMITIVEMODEL_H_
#define GGAFDX9PRIMITIVEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PrimitiveActor�p�̃��f���N���X.
 * GgafDx9PrimitiveModel �� D3DXLoadMeshFromX ���g�p�����A�Ǝ���X�t�@�C�����烂�f���f�[�^��ǂݍ��ݐݒ肷��B<BR>
 * �����Ӂ�<BR>
 * �EFace�́A3�p�`�����ʖځB�iD3DXLoadMeshFromX �� 3�p�` or 4�p�`���T�|�[�g�j<BR>
 * �EUV���W�ɂ��āA���_���ƈ�v���Ȃ��Ă��A�Ƃ肠�������Ԃɐݒ肷��B�f�[�^�[������UV���W��(0,0)�ɐݒ肳���B<BR>
 * �E�@���ɂ��āAFace��3���_�ɓ����l��ݒ�B���L���_�̏ꍇ�A��ɐݒ肳�ꂽ�@���ŏ㏑�����B<BR>
 *   TODO:�@���̌����͕��ω��́A�������̂ł����܂����ĂȂ��B��������I<BR>
 * �EGgafDx9PrimitiveModel�͒��_�C���f�b�N�X�̍œK�����Ȃ����s�Ȃ�Ȃ��A�s�Ȃ�Ȃ��̂�����ł�����B<BR>
 *   ���̂��߁A�`�掞�́AX�t�@�C������ǂݍ��񂾃}�e���A�����X�g�̏��Ԓʂ�ɕ`�悷��B<BR>
 *   ����́ADrawIndexedPrimitive �́A�}�e���A�����X�g�̃}�e���A���ԍ����؂�ւ�邽�тɔ������邱�Ƃ��Ӗ����A<BR>
 *   �}�e���A�����X�g�̃o������ɂ���ẮAD3DXLoadMeshFromX ���p�t�H�[�}���X��������B<BR>
 *   �Ⴆ�΁AX�t�@�C���̃}�e���A�����X�g�� {0,0,1,1,0,1} �ȏꍇ�A�}�e���A������2�ł��A�`���4����s���邱�ƂɂȂ�B<BR>
 * ���g������<BR>
 * �E�s���S�Ɖ����Ă���X�t�@�C�����A�����ēǂ݂����ꍇ�B�i�f�[�^���[�_�[�Ŏg���ꍇ�j<BR>
 * �EX�t�@�C�����_��񓙂��AD3DXLoadMeshFromX�̍œK���ɂ���āA�������茸������ړ����ꂽ�肵�ė~�����Ȃ��ꍇ�B<BR>
 * �E�V�F�[�_�[�Ƀp�����[�^��n�������A���Ƃ��璸�_�������肽���ꍇ���AID3DXMesh ���炢�������T���̂��ʓ|���B<BR>
 */
class GgafDx9PrimitiveModel : public GgafDx9Model {
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

    /** VERTEX��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** �}�e���A���z�� */
    D3DMATERIAL9* _paD3DMaterial9_default;
    INDEXPARAM* _paIndexParam;
    /** �e�N�X�`���z��(�C���X�^���X�̓e�N�X�`�����A���f���Ƃ͕ʊǗ��j */
    GgafDx9TextureConnection** _papTextureCon;

    UINT _size_vertecs;
    /** 1���_�̃T�C�Y */
    UINT _size_vertec_unit;
    /** 1���_�̃T�C�Y */
    DWORD _dwNumMaterials;
    UINT _pFaceMaterials;

    VERTEX* _paVtxBuffer_org;
    WORD* _paIdxBuffer_org;

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
