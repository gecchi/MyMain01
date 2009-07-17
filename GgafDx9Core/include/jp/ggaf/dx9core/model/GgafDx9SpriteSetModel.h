#ifndef GGAFDX9SPRITESETMODEL_H_
#define GGAFDX9SPRITESETMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteSetActor�p���f���N���X.
 */
class GgafDx9SpriteSetModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:
    static int _draw_set_num_LastDraw;
    int _setnum;


    /** ���_�\���� */
    struct VERTEX {
        float x, y, z;    // ���_���W
        float nx, ny, nz; // ���_�̖@��
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��𖄂ߍ��ށB�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };

    /** ���_�o�b�t�@�̊e�Z�b�g */
    LPDIRECT3DVERTEXBUFFER9* _paIDirect3DVertexBuffer9;
    /** ���_��FVF */
    static DWORD FVF;
    /** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
    GgafDx9RectUV* _paRectUV;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertecs;
    /** 1���_�̃T�C�Y */
    UINT _size_vertec_unit;

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9SpriteSetModel(char* prm_model_name);

public:
    /** �S�A�j���p�^�[����(0�`) */
    int _pattno_ani_Max;
    float _fSize_SpriteSetModelWidthPx;
    float _fSize_SpriteSetModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9SpriteSetModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9SpriteSetActor
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
    virtual ~GgafDx9SpriteSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9SPRITESETMODEL_H_*/
