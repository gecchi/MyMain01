#ifndef GGAFDXCORE_GGAFDXMASSMORPHMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMORPHMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * GgafDxMassMorphMeshModel用のモデルクラス.
 * GgafDxMassMorphMeshModel は GgafDxMeshModel の描画する機能に加え、モーフアニメーション機能を有するモデルです。<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMassMorphMeshModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
    struct VERTEX_model_primary : public GgafDxModel::VERTEX_3D_BASE {
        D3DCOLOR color;   // 頂点の色（オブジェクトのマテリアルカラーとして使用予定）
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model_primary* _paVtxBuffer_data_model;
    WORD* _paIndexBuffer_data;

    /** モーフターゲットの頂点フォーマット定義 */
    struct VERTEX_model_morph : public GgafDxModel::VERTEX_3D_BASE {
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
    LPDIRECT3DVERTEXBUFFER9* _pVertexBuffer_model_morph;


public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name モデル定義の識別名
     */
    GgafDxMassMorphMeshModel(const char* prm_model_name);

    static void createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;


    virtual void resetStreamSourceFreq() override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassMorphMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMASSMORPHMESHMODEL_H_*/
