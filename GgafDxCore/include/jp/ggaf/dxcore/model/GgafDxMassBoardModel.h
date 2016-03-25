#ifndef GGAFDXCORE_GGAFDXMASSBOARDMODEL_H_
#define GGAFDXCORE_GGAFDXMASSBOARDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * GgafDxMassBoardActor�p���f���N���X.
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassBoardModel : public GgafDxMassModel {
    friend class GgafDxModelManager;
    friend class GgafDxMassBoardActor;

public:
    struct VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
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
    GgafDxMassBoardModel(const char* prm_model_name);

    static void createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info);

    /**
     * ���f���̕`����s�� .
     * @param prm_pActor_target �`�悷�郂�f���̃A�N�^
     * @param prm_draw_set_num  �`�悷��C���X�^���X��
     * @param prm_pPrm �C���X�^���X�f�[�^�̐擪�A�h���X
     * @return
     */
    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * �f�X�g���N�^<BR>
     */
    virtual ~GgafDxMassBoardModel(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXMASSBOARDMODEL_H_*/
