#ifndef GGAF_DX_MASSMORPHMESHMODEL_H_
#define GGAF_DX_MASSMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {

/**
 * MassMorphMeshModel用のモデルクラス.
 * MassMorphMeshModel は MeshModel の描画する機能に加え、モーフアニメーション機能を有するモデルです。<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MassMorphMeshModel : public MassModel {
    friend class ModelManager;

public:
    struct VERTEX_model_primary : public Model::VERTEX_POS_NOMAL {
        D3DCOLOR color;   // 頂点の色（オブジェクトのマテリアルカラーとして使用予定）
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model_primary* _paVtxBuffer_data_model;
    bool _is_65535;
    uint16_t* _paIndex16Buffer_data;
    uint32_t* _paIndex32Buffer_data;

    /** モーフターゲットの頂点フォーマット定義 */
    struct VERTEX_model_morph : public Model::VERTEX_POS_NOMAL {
    };
    /** モーフターゲット頂点バッファの写しコピーの頂点配列のモーフターゲット数配列 */
    VERTEX_model_morph**  _papaVtxBuffer_data_morph_model;
    /** 頂点のサイズ（モーフターゲット） */
    UINT _size_vertices_morph_model;
    /** 1頂点のサイズ（モーフターゲット） */
    UINT _size_vertex_unit_morph_model;
    /** モーフターゲット数 */
    int _morph_target_num;
    /** モーフターゲット頂点バッファの配列（要素数＝モーフターゲット数） */
    LPDIRECT3DVERTEXBUFFER9* _paVertexBuffer_model_morph;


public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id モデル定義の識別名
     */
    MassMorphMeshModel(const char* prm_model_id);

    static void createVertexModel(void* prm, MassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;


    virtual void resetStreamSourceFreq() override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~MassMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAF_DX_MASSMORPHMESHMODEL_H_*/
