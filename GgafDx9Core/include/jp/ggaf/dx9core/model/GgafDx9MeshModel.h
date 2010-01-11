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
 * ���b�V�����f���N���X(GgafDx9MeshActor�p).
 * GgafDx9MeshModel �͓Ǝ���X�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �I�u�W�F�N�g��`�悷��@�\���������ÓI���f���p�̃N���X�ł��B <BR>
 * ��������  <BR>
 * �EX�t�@�C���̒��_����ۏ؁B  <BR>
 * �EGgafDx9D3DXMeshModel ���ǂݍ��݂������B  <BR>
 * �EX�t�@�C���ɕ������b�V���o�^����Ă���ꍇ�A�����A�����Ĉ�̒��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�ƈ�������  <BR>
 *  �`�悪��荂���ɂȂ�B <BR>
 * ���Z����  <BR>
 * �ED3DXLoadMeshFromX���g�p���Ă��炸�AX�t�@�C���� template �錾�͌��Ă��Ȃ����߁A�f�[�^�\����  <BR>
 *  ("Mesh"��"TextureFilename"���j�� �n�[�h�R�[�f�B���O����Ă���B  <BR>
 *  �\�����Ȃ����G��X�t�@�C���͂��܂��ǂߖ����ꍇ�����邾�낤�B  <BR>
 * �E����ɋ��L���_�̖@���𕽋ω����� <BR>
 * <BR>
 * <b>�u�@�����ω����Ă��܂����R(������)�v</b><BR>
 * �Ⴆ�΁A�X���[�X���������̗����̂̏ꍇ�AX�t�@�C���ł́A���_���W��8�A�@���x�N�g��6�A���_�C���f�b�N�X32�A�@���C���f�b�N�X32�ƂȂ邪�A
 * D3DXLoadMeshFromX�œǂݍ��ނƁA�����Œ��_�������s���A���_�o�b�t�@��32�̒��_���쐬�����B<BR>
 * ����̓G�b�W���N�b�L���o�����߂ɖ@���D��ŏ�������邽�߂��Ǝv���B<BR>
 * ������DrawIndexedPrimitive����A�V�F�[�_�[���p���A����ɒ��_�̐����ς���Ă��܂��͍̂���ꍇ����B
 * �u�ǂ�Ȗ@����ݒ肵�悤�Ƃ��A�ň�X�t�@�C���ɏ������ʂ�̒��_���ŕ`�悵�����B
 *  ���܂��`��ł��Ȃ��ꍇ�A����Mesh�I�u�W�F�N�g���璸�_���𒲂ׂāAX�t�@�C�����`���R�`���R�C�������Ƃ͂������񂴂�v<BR>
 * �Ƃ������ƂŁA���̃��f���N���X���쐬�����B�iD3DXLoadMeshFromX�̃\�[�X�R�[�h������΂����̂ɂȁE�E�E�j<BR>
 * ���������āA���L���_�͖@��������Ȃ��Ȃ��Ă��܂����߁A����ɋ��L���_�̖@���𕽋ω����s�����Ƃɂ��Ă���B<BR>
 * �G�b�W���N�b�L���o�������ꍇ�́AX�t�@�C�����ōŏ����炿���ƒ��_��32�A�@����32�����΂悢�B<BR>
 * ���Ȃ݂ɖ@���̂Ȃ�X�t�@�C���ł����_�C���f�b�N�X���玩���Ŗ@�����v�Z����B<BR>
 *
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
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target);

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
