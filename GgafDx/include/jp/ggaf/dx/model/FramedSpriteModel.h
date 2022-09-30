#ifndef GGAF_DX_FRAMEDSPRITEMODEL_H_
#define GGAF_DX_FRAMEDSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/interface/IPlaneModel.h"

namespace GgafDx {

/**
 * FramedSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2022/01/25
 * @author Masatoshi Tsuge
 */
class FramedSpriteModel : public Model, public IPlaneModel {
    friend class ModelManager;

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
    struct VERTEX : public VERTEX_POS_NOMAL {
        float index;      // psize�ł͂Ȃ��Ă͂Ȃ��Ē��_�ԍ��𖄂ߍ��ށB�V�F�[�_�[���ŉ��Z�b�g�ڂ��𔻒f���邽�߂Ɏg�p�B
        DWORD color;      // ���_�F�i���ݖ��g�p�j
        float tu, tv;     // ���_�̃e�N�X�`�����W
    };
    INDEXPARAM _indexParam;
    /** ���_�o�b�t�@ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** �C���f�b�N�X�o�b�t�@ */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;
    /** ���_��FVF */
    static DWORD FVF;

    VERTEX* _paVertexBuffer_data;
    WORD* _paIndexBuffer_data;
    /** ��`�̒��_���v�̃T�C�Y */
    UINT _size_vertices;
    /** 1���_�̃T�C�Y */
    UINT _size_vertex_unit;
    /** ��{���f���i�P�L�������j���_�� */
    UINT _nVertices;

    float _model_frame_width_px;
    float _model_frame_height_px;
    int _row_frame_texture_split;
    int _col_frame_texture_split;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_id �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    FramedSpriteModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~FramedSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_FRAMEDSPRITEMODEL_H_*/
