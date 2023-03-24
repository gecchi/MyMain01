#ifndef GGAF_DX_MASSMESHMODEL_H_
#define GGAF_DX_MASSMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {


/**
 * Massメッシュモデルクラス(MeshActor用) .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassMeshModel : public MassModel {
    friend class ModelManager;

public:
    struct VERTEX_model : public Model::VERTEX_POS_NOMAL {
        D3DCOLOR color;   // 頂点の色（オブジェクトのマテリアルカラーとして使用予定）
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model* _paVtxBuffer_data_model;
    bool _is_65535;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    MassMeshModel(const char* prm_model_id);

    static void createVertexModel(void* prm, MassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;


    void addAnotherModel(const char* prm_model_id);
    /**
     * デストラクタ<BR>
     */
    virtual ~MassMeshModel();
};

}
#endif /*GGAF_DX_MESHSETMODEL_H_*/
