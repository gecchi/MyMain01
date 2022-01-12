#ifndef GGAF_DX_POINTSPRITESETMODEL_H_
#define GGAF_DX_POINTSPRITESETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class PointSpriteSetModel : public Model {
    friend class ModelManager;

public:
    struct VERTEX {
        float x, y, z;    // ���_���W
        float psize;      // �|�C���g�T�C�Y
        DWORD color;      // ���_�̐F
        float ini_ptn_no, index;     //
    };

    /** ���_��FVF */
    static DWORD FVF;
    /** ���_�o�b�t�@�i���L�������j */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;

    /** �I�u�W�F�N�g�̂P�ӂ̃T�C�Y(px) */
    float _square_size_px;
    /** �e�N�X�`���̂P�ӂ̒���(px) */
    float _texture_size_px;
    /** �e�N�X�`��������(�P�ŕ��������B�Q�łS�p�^�[���A�R�łX�p�^�[��) */
    int _texture_split_rowcol;

    float _inv_texture_split_rowcol;
    /** �P���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** ��{���f���i�P�L�������j���_�T�C�Y�v */
    UINT _size_vertices;
    /** ��{���f���i�P�L�������j���_�� */
    UINT _nVertices;

    VERTEX* _paVtxBuffer_data;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    PointSpriteSetModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~PointSpriteSetModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_POINTSPRITESETMODEL_H_*/
