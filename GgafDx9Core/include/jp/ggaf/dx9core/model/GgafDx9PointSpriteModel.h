#ifndef GGAFDX9POINTSPRITEMODEL_H_
#define GGAFDX9POINTSPRITEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PointSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:
    struct VERTEX {
        float x, y, z;    // ���_���W
        float psize;      // �|�C���g�T�C�Y
        DWORD color;      // ���_�̐F
        float tu, tv;     // �e�N�X�`�����W
    };

    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** ���_���z�� */
    VERTEX* _paVtxBuffer_org;
    /** ���_��(=�X�v���C�g��) */
    int _vertices_num;
    /** ���_��FVF */
    static DWORD FVF;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** �I�u�W�F�N�g�̂P�ӂ̃T�C�Y(px) */
    float _fSquareSize;
    /** �e�N�X�`���̂P�ӂ̒���(px) */
    float _fTexSize;
    /** �e�N�X�`��������(�P�ŕ��������B�Q�łS�p�^�[���A�R�łX�p�^�[��) */
    int _texture_split_rowcol;


    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".psprx"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9PointSpriteModel(char* prm_model_name);

public:
    /**
     * GgafDx9PointSpriteModel�I�u�W�F�N�g�̕`��<BR>
     * @param   prm_pActor_Target �`�悷��GgafDx9PointSpriteActor
     * @return  HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDx9PointSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9POINTSPRITEMODEL_H_*/
