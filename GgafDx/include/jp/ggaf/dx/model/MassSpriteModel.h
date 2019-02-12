#ifndef GGAF_DX_MASSSPRITEMODEL_H_
#define GGAF_DX_MASSSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {

/**
 * MassSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteModel : public MassModel {
    friend class ModelManager;

public:
    struct VERTEX_model : public Model::VERTEX_3D_BASE {
        float tu, tv;     // �e�N�X�`�����W
    };
    VERTEX_model* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    float _model_width_px;
    float _model_height_px;
    float _model_half_width_px;
    float _model_half_height_px;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    MassSpriteModel(const char* prm_model_name);

    static void createVertexModel(void* prm, MassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~MassSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_MASSSPRITEMODEL_H_*/
