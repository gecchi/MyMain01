#ifndef GGAFDXCORE_GGAFDXSPRITESETMODEL_H_
#define GGAFDXCORE_GGAFDXSPRITESETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

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
    struct VERTEX : public GgafDxModel::VERTEX_3D_BASE {
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��𖄂ߍ��ށB�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };

    /** ���_�o�b�t�@�̊e�Z�b�g */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** ���_��FVF */
    static DWORD FVF;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;

    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxSpriteSetModel(const char* prm_model_name);


    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

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
#endif /*GGAFDXCORE_GGAFDXSPRITESETMODEL_H_*/
