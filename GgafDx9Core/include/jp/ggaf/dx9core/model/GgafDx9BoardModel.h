#ifndef GGAFDX9BOARDMODEL_H_
#define GGAFDX9BOARDMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardActor�p���f���N���X.
 */
class GgafDx9BoardModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9BoardActor;
protected:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDx9BoardModel(char* prm_model_name);

public:
    struct VERTEX {
        float x, y, z; // ���_���W
        float tu, tv; // �e�N�X�`�����W
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;

    /** �A�j���[�V���[���̂��߂̃e�N�X�`���̍��W�̔z��i�v�f���̓A�j���[�V�������j */
    GgafDx9RectUV* _paRectUV;

    /** �S�A�j���p�^�[���� */
    int _pattno_max;
    float _fSize_BoardModelWidthPx;
    float _fSize_BoardModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9BoardModel�I�u�W�F�N�g�̕`��<BR>
     * @param	prm_pActor_Target �`�悷��GgafDx9BoardActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * �f�X�g���N�^<BR>
     * delete����̂�GgafDx9BoardModelManager�ł���<BR>
     */
    virtual ~GgafDx9BoardModel(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9BOARDMODEL_H_*/
