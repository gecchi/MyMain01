#ifndef GGAFDXCORE_GGAFDXMASSSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXMASSSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * GgafDxMassSpriteActor�p���f���N���X.
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassSpriteModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
    class VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
    public:
        float tu, tv;     // �e�N�X�`�����W
    };
    VERTEX_model* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
     */
    GgafDxMassSpriteModel(const char* prm_model_name);

    static void createVertexModel(GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMassSpriteModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMASSSPRITEMODEL_H_*/
