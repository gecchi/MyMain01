#ifndef GGAFDXSPRITEMODEL_H_
#define GGAFDXSPRITEMODEL_H_
namespace GgafDxCore {

/**
 * GgafDxSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteModel : public GgafDxModel {
    friend class GgafDxModelManager;

protected:
public:

    /** ���_�\���� */
    struct VERTEX {
        float x, y, z;    // ���_���W
        float nx, ny, nz; // ���_�̖@��
        DWORD color;      // ���_�F�i���ݖ��g�p�j
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };

    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** ���_��FVF */
    static DWORD FVF;
    /** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
//    GgafDxRectUV* _paRectUV;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;

    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxSpriteModel(char* prm_model_name);

public:
    /** �S�A�j���p�^�[����(0�`) */
//    int _pattno_uvflip_Max;
    float _fSize_SpriteModelWidthPx;
    float _fSize_SpriteModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDxSpriteModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDxSpriteActor
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
    virtual ~GgafDxSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXSPRITEMODEL_H_*/
