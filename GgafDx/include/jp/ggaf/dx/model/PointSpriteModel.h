#ifndef GGAF_DX_POINTSPRITEMODEL_H_
#define GGAF_DX_POINTSPRITEMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * PointSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class PointSpriteModel : public Model {
    friend class ModelManager;

public:
    struct VERTEX : public Model::VERTEX_POS {
        float psize;      // �|�C���g�T�C�Y
        DWORD color;      // ���_�̐F
        float tu, tv;     // �e�N�X�`�����W
    };

    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** ���_���z�� */
    VERTEX* _paVtxBuffer_data;
    /** ���_��(=�X�v���C�g��) */
    int _vertices_num;
    /** ���_��FVF */
    static DWORD FVF;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** �I�u�W�F�N�g�̂P�ӂ̃T�C�Y(px) */
    float _square_size_px;
    /** �e�N�X�`���̂P�ӂ̒���(px) */
    float _texture_size_px;
    /** �e�N�X�`��������(�P�ŕ��������B�Q�łS�p�^�[���A�R�łX�p�^�[��) */
    int _texture_split_rowcol;
    float _inv_texture_split_rowcol;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".psprx"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    PointSpriteModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~PointSpriteModel();
};

}
#endif /*GGAF_DX_POINTSPRITEMODEL_H_*/
