#ifndef GGAFDXCORE_GGAFDXMASSBOARDMODEL_H_
#define GGAFDXCORE_GGAFDXMASSBOARDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * GgafDxMassBoardActor用モデルクラス.
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassBoardModel : public GgafDxMassModel {
    friend class GgafDxModelManager;
    friend class GgafDxMassBoardActor;

public:
    struct VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
        float tu, tv;     // テクスチャ座標
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
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassBoardModel(const char* prm_model_name);

    static void createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info);

    /**
     * モデルの描画を行う .
     * @param prm_pActor_target 描画するモデルのアクタ
     * @param prm_draw_set_num  描画するインスタンス数
     * @param prm_pPrm インスタンスデータの先頭アドレス
     * @return
     */
    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassBoardModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMASSBOARDMODEL_H_*/
