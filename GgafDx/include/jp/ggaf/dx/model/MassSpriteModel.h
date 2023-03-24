#ifndef GGAF_DX_MASSSPRITEMODEL_H_
#define GGAF_DX_MASSSPRITEMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/model/interface/IPlaneModel.h"

namespace GgafDx {

/**
 * MassSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteModel : public MassModel, public IPlaneModel {
    friend class ModelManager;

public:
    struct VERTEX_model : public Model::VERTEX_POS_NOMAL {
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    float _model_half_width_px;
    float _model_half_height_px;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    MassSpriteModel(const char* prm_model_id);

    static void createVertexModel(void* prm, MassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~MassSpriteModel();
};

}
#endif /*GGAF_DX_MASSSPRITEMODEL_H_*/
