#ifndef GGAFDX9BOARDSETMODEL_H_
#define GGAFDX9BOARDSETMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardSetActor�p���f���N���X.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardSetModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9BoardSetActor;
protected:
public:
    static int _draw_set_num_LastDraw;
    int _set_num;
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    /** ���_�\���� */
    struct VERTEX {
        float x, y, z;    // ���_���W
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��𖄂ߍ��ށB�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };

    /** ���_�o�b�t�@�̊e�Z�b�g */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** ���_��FVF */
    static DWORD FVF;
    /** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
    GgafDx9RectUV* _paRectUV;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9BoardSetModel(char* prm_model_name);

public:
    /** �S�A�j���p�^�[����(0�`) */
    int _pattno_max;
    float _fSize_BoardSetModelWidthPx;
    float _fSize_BoardSetModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9BoardSetModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9BoardSetActor
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
    virtual ~GgafDx9BoardSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9BOARDSETMODEL_H_*/
