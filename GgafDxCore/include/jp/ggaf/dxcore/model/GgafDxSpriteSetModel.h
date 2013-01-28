#ifndef GGAFDXSPRITESETMODEL_H_
#define GGAFDXSPRITESETMODEL_H_
namespace GgafDxCore {

/**
 * GgafDxSpriteSetActor�p���f���N���X.
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    /** ���_�\���� */
    class VERTEX : public GgafDxModel::VERTEX_3D_BASE {
    public:
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��𖄂ߍ��ށB�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };

    /** ���_�o�b�t�@�̊e�Z�b�g */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** ���_��FVF */
    static DWORD FVF;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;

    float _fSize_SpriteSetModelWidthPx;
    float _fSize_SpriteSetModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxSpriteSetModel(char* prm_model_name);


    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxSpriteSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXSPRITESETMODEL_H_*/
