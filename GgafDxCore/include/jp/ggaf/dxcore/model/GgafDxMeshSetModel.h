#ifndef GGAFDXMESHSETMODEL_H_
#define GGAFDXMESHSETMODEL_H_
namespace GgafDxCore {

/**
 * ���b�V�����f���N���X(GgafDxMeshActor�p) .
 * GgafDxMeshSetModel �͓Ǝ���X�t�@�C�����烂�f���f�[�^��ǂݍ��݁A<BR>
 * �I�u�W�F�N�g��`�悷��@�\���������ÓI���f���p�̃N���X�ł��B <BR>
 * �ǂݍ��ݎ��A���f���̒��_�o�b�t�@���A�����R�s�[���ĘA�����A��̒��_�o�b�t�@�Ƃ��ăZ�b�g���܂��B<BR>
 * ���ꃂ�f���̕����̃I�u�W�F�N�g��1��ŕ`�悵�A��������ڎw���N���X�B <BR>
 * �ґ���g�ޓG��A�e�A�ȂǂɎg�p���邱�Ƃ�z�肷��B <BR>
 * ��������  <BR>
 * �EGgafDxMeshModel �̒����Ɠ��������B
 * �E�����I�u�W�F�N�g��`�悷��ꍇ�́AGgafDxMeshModel ��肳��ɍ����`��B  <BR>
 * ���Z����  <BR>
 * �EGgafDxMeshModel �̒Z���Ɠ����Z���B
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
class GgafDxMeshSetModel : public GgafDxModel {
    friend class GgafDxModelManager;

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
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��Ƃ��Ďg�p�B�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        DWORD color;      // ���_�̐F�i�I�u�W�F�N�g�̃}�e���A���J���[�Ƃ��Ďg�p�j
        float tu, tv;     // �e�N�X�`�����W
    };

    /** �O��\���̓����`�悵���Z�b�g���i�L�����N�^���j*/
    static int _draw_set_num_LastDraw;

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@�i���L�������j */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@�i���L�������j */
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
    GgafDxMeshSetModel(char* prm_model_name);

public:

    /**
     * GgafDxMeshSetModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDxMeshSetActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMeshSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXMESHSETMODEL_H_*/