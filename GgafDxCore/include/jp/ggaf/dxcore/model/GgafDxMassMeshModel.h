#ifndef GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {


/**
 * Massメッシュモデルクラス(GgafDxMeshActor用) .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassMeshModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
    struct VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
        D3DCOLOR color;   // 頂点の色（オブジェクトのマテリアルカラーとして使用予定）
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassMeshModel(const char* prm_model_name);

    static void createVertexModel(GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    void changeVertexAlpha(int prm_vertex_alpha);
    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETMODEL_H_*/
