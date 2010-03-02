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
 *  ("Mesh"��"TextureFilename"���j�� �n�[�h�R�[�f�B���O����Ă���B���^�Z�R�A�A3DSMAX����X�t�@�C���̃G�N�X�|�[�g��
 *  �ǂݍ��߂�Ηǂ��Ƃ����݌v�ŁA�\�����Ȃ����G��X�t�@�C���͂܂��ǂ߂Ȃ��B<BR>
 * �E����ɋ��L���_�̖@���𕽋ω����� <BR>
 * <BR>
 * <b>�u�o�܁v</b><BR>
 * �Ⴆ�Η����̂̏ꍇ�A���ʂ́A���_��8�A�@���x�N�g��6�A���_�C���f�b�N�X32�A�@���C���f�b�N�X32�ƂȂ邪�A
 * ���̂悤��X�t�@�C���� D3DXLoadMeshFromX�œǂݍ��ނƁA����ɒ��_��������B<BR>
 * ����͐e�؂ɂ��A�G�b�W���N�b�L�������邽�߂ɖ@�����D�悳��ď�������邽�߂��Ǝv���B<BR>
 * �������A�V�F�[�_�[�Ń��[�t����A�����I�u�W�F�N�g��DrawIndexedPrimitive�ł킯�ĕ\�����鎞���A
 * ����ɒ��_�̐����ς���Ă��܂��̂͒v���I�ȏꍇ������B<BR>
 * �uX�t�@�C���ɏ������ʂ�̒��_�Œ��_�o�b�t�@����肽���v<BR>
 * ���_������������͑z���ł��邪�A���_�̕�����œK���A���S���Y���̏ڍׂȎd�l���T���Ă������i�Ǝv���j�B<BR>
 * D3DXLoadMeshFromX�̃\�[�X�R�[�h��������Ή��������A����Ȃ̌��J����Ė����B<BR>
 * ����Ȃ킯�ŁAD3DXLoadMeshFromX�͎g���Ȃ��Ƃ������_�ɂȂ�A�Ǝ���X�t�@�C����ǂݍ��ނ悤�ɂ����B<BR>
 * �g���Ȃ��ƌ��f����܂Ŕ�풷�������B���A��X�t�@�C���}�X�^�[�ɂȂ�܂����B<BR>
 * ���_����ۏ؂��邽�߁A�@��������Ȃ��Ȃ��Ă��܂��ꍇ������B�����ŋ��L���_�̖@���͕��ω����s�����Ƃɂ��Ă���B<BR>
 * �����G�b�W���N�b�L���o�������ꍇ�́AX�t�@�C�����ōŏ����炿���Ɨ����̂Ȃ�Β��_��32�����΂悢�B<BR>
 * �܂��A�@���̖���X�t�@�C���ł����_�C���f�b�N�X���玩���Ŗ@�����v�Z����������B<BR>
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
