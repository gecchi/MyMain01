#ifndef GGAFDX9SPRITEMODEL_H_
#define GGAFDX9SPRITEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteActor�p���f���N���X.
 */
class GgafDx9SpriteModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:
    struct VERTEX {
        float x, y, z; // ���_���W
        float nx, ny, nz; // �@��
        DWORD color; // ���_�̐F
        float tu, tv; // �e�N�X�`�����W
    };

    /** VERTEX��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@�ւ̃|�C���^ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** �}�e���A�� */
    D3DMATERIAL9* _pD3DMaterial9_default;
    /** �e�N�X�`��(�A�j���[�V�����p�^�[���j */
    GgafDx9TextureLead* _pTexture;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _iSize_Vertecs;
    /** 1���_�̃T�C�Y */
    UINT _iSize_Vertec_unit;
    /** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
    GgafDx9RectUV* _paRectUV;

    /** �O��\����UV */
    GgafDx9RectUV* _pRectUV_drawlast;

    //bool _isChangedAlpha;

    /**
     * �R���X�g���N�^<BR>
     * @param prm_spritemodel_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9SpriteModel(char* prm_spritemodel_name);

public:
    /** �S�A�j���p�^�[����(0�`) */
    int _iAnimationPatternNo_Max;
    float _fSize_SpriteModelWidthPx;
    float _fSize_SpriteModelHeightPx;
    int _iRowNum_TextureSplit;
    int _iColNum_TextureSplit;
    //int	   _iChangeVertexAlpha;


    /**
     * GgafDx9SpriteModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9SpriteActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    void changeVertexAlpha(int prm_iVertexAlpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9SpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9SPRITEMODEL_H_*/
