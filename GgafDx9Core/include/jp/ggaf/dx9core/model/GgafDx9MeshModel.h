#ifndef GGAFDX9MESHMODEL_H_
#define GGAFDX9MESHMODEL_H_
namespace GgafDx9Core {


// �{�v���O������ Paul Coppens ����̍쐬���ꂽ�AX�t�@�C����ǂݍ��ރT���v��
// �����ɁA�Ǝ��ɉ��ǏC���i��f�o�b�O�j�����N���X���g�p���Ă��܂��B
// ���肪�Ƃ� Paul����B
//
// �y�Ώہz
// Frm ���O��Ԃ̃N���X
//
// �yLoading and displaying .X files without DirectX �z
// http://www.gamedev.net/reference/programming/features/xfilepc/
//
//                                         2009/03/06 Masatoshi Tsuge

/**
 * ���b�V�����f���N���X(GgafDx9MeshActor�p).
 * GgafDx9MeshModel �͓Ǝ���X�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �I�u�W�F�N�g��`�悷��@�\���������ÓI���f���p�̃N���X�ł��B <BR>
 * <b>��������</b>  <BR>
 * �EX�t�@�C���̒��_����ۏ؁B <BR>
 * �EGgafDx9D3DXMeshModel ���ǂݍ��݂������itemplate�Ƃ����ĂȂ��j�B <BR>
 * �EX�t�@�C���ɕ������b�V���o�^����Ă���ꍇ�A�����A�����Ĉ�̒��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�ƈ�������
 *   �`�悪��荂���ɂȂ�B <BR>
 * <b>���Z����</b> <BR>
 * �ED3DXLoadMeshFromX���g�p���Ă��炸�AX�t�@�C���� template �錾�͌��Ă��Ȃ����߁A�f�[�^�\�����̃w�b�_��
 *  ("Mesh"��"TextureFilename"���j�� �n�[�h�R�[�f�B���O����Ă���B�\�����Ȃ����G��X�t�@�C���͂܂��ǂ߂Ȃ��B<BR>
 * �E����ɋ��L���_�̖@���𕽋ω����� <BR>
 * <BR>
 * �u���̑����ӓ_�v<BR>
 * ���_����ۏ؂��邽�߁A�@��������Ȃ��Ȃ��Ă��܂��ꍇ������B�����ŋ��L���_�̖@���͓Ǝ��v�Z�ŕ��ω����s�����Ƃɂ��Ă���B<BR>
 * �����G�b�W���N�b�L���o�������ꍇ�́AX�t�@�C�����ōŏ����炿���Ɨ����̂Ȃ�Β��_��32�����΂悢�B<BR>
 * �܂��A�@���̖���X�t�@�C���ł����_�C���f�b�N�X���玩���Ŗ@�����v�Z����������B<BR>
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
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
        DWORD color; // ���_�̐F�i���ݖ��g�p�j
        float tu, tv; // �e�N�X�`�����W
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;

    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
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
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    virtual void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9MeshModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHMODEL_H_*/

