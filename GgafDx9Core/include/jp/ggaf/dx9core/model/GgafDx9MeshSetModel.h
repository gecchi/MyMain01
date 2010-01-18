#ifndef GGAFDX9MESHSETMODEL_H_
#define GGAFDX9MESHSETMODEL_H_
namespace GgafDx9Core {

/**
 * ���b�V�����f���N���X(GgafDx9MeshActor�p) .
 * GgafDx9MeshSetModel �͓Ǝ���X�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �I�u�W�F�N�g��`�悷��@�\���������ÓI���f���p�̃N���X�ł��B <BR>
 * �ǂݍ��ݎ��A���f���̒��_�o�b�t�@���A�����R�s�[���ĘA�����A��̒��_�o�b�t�@�Ƃ��ăZ�b�g���܂��B<BR>
 * �����̃I�u�W�F�N�g��1��ŕ`�悵�A��������ڎw���N���X�B <BR>
 * �ґ���g�ޓG��A�e�A�ȂǂɎg�p���邱�Ƃ�z�肷��B <BR>
 * ��������  <BR>
 * �EGgafDx9MeshModel �̒����Ɠ��������B
 * �E�����I�u�W�F�N�g��`�悷��ꍇ�́AGgafDx9MeshModel ��肳��ɍ����`��B  <BR>
 * ���Z����  <BR>
 * �EGgafDx9MeshModel �̒Z���Ɠ����Z���B
 * �E�`��L�������̒��_�̃R�s�[�A�����Ē��_�o�b�t�@�Ɏ����߁A1�L�����N�^�̒��_�����A 65536/�����`�搔 ��<BR>
 *  �𒴂���Ƒʖڂł���B<BR>
 * �E����ɁA�}�e���A����1��ނ��]�܂����B����͑S�̂�1��ނł͂Ȃ��A<BR>
 *  �e�L�������Ƃɂ��ꂼ��}�e���A���F��1��ނ������蓖�Ă�Ȃ��Ƃ����Ӗ��B�������A�e�N�X�`���͑S�̂�1��ނ����ʖځB<BR>
 *  �������}�e���A����X�t�@�C�����w�肵�Ă��G���[�ɂ͂Ȃ�Ȃ����A�����}�e���A���̏ꍇ�A�}�e���A�����ɃV�F�[�_�[�̃��W�X�^���X�V
 *  �iCommitChanges�������j���Ă��܂����߁A�I�u�W�F�N�g���ꂼ��`�悵�Ă��邱�ƂɂȂ�A��⍂�����̈Ӗ��������Ȃ�B<BR>
 * @version 1.00
 * @since 2009/06/15
 * @author Masatoshi Tsuge
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
        float x, y, z;    // ���_���W
        float nx, ny, nz; // �@��
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��𖄂ߍ��ށB�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        DWORD color;      // ���_�̐F�i���ݖ��g�p�j
        float tu, tv;     // �e�N�X�`�����W

    };

    /** �O��\���̓����`�悵���Z�b�g���i�L�����N�^���j*/
    static int _draw_set_num_LastDraw;
    /** �ő哯���`��Z�b�g���i�L�����N�^���j�A���݂�16�L���������`��\ */
    int _set_num;

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@�i�W�L�������j */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@�i�W�L�������j */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;


    /** �P���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** ��{���f���i�P�L�������j���_�T�C�Y�v */
    UINT _size_vertices;
    /** ��{���f���i�P�L�������j���_�� */
    UINT _nVertices;
    /** ��{���f���i�P�L�������j�̖ʂ̐� */
    UINT _nFaces;

    INDEXPARAM** _papaIndexParam;

    /** �}�e���A�����X�g�̘A���œ���̃}�e���A���ԍ��̉�i�O���[�v�j������邩 */
    UINT* _pa_nMaterialListGrp;

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
    GgafDx9MeshSetModel(char* prm_model_name);

public:

    /**
     * GgafDx9MeshSetModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9MeshSetActor
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
    virtual ~GgafDx9MeshSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9MESHSETMODEL_H_*/
