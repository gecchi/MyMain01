#ifndef GGAFDXCORE_GGAFDXMASSSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXMASSSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * GgafDxMassSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassSpriteModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
    class VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
    public:
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassSpriteModel(const char* prm_model_name);

    static void createVertexModel(GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassSpriteModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMASSSPRITEMODEL_H_*/
