#ifndef GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * Massメッシュモデルクラス(GgafDxMeshActor用) .
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    class VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
    public:
        DWORD color;      // 頂点の色（オブジェクトのマテリアルカラーとして使用）
        float tu, tv;     // テクスチャ座標
    };

    /** 頂点バッファ（モデル） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_model;
    /** 頂点バッファ（インスタンス：ワールド変換行列情報、マテリアルカラー情報） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_instacedata;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** シェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;

    /** １頂点のサイズ（モデル） */
    UINT _size_vertex_unit_model;
    /** １頂点のサイズ（インスタンス） */
    UINT _size_vertex_unit_instacedata;
    /** １モデル頂点サイズ計 */
    UINT _size_vertices_model;
    /** モデル頂点数 */
    UINT _nVertices;
    /** モデル面の数 */
    UINT _nFaces;

    VERTEX_model* _paVtxBuffer_data_model;

    WORD* _paIndexBuffer_data;

    void (*_pFunc_CreateVertexInstaceData)(D3DVERTEXELEMENT9** out_paVtxInstaceDataElement,
                                           int* out_elem_num,
                                           UINT* out_size_vertex_unit_instacedata,
                                           void** out_pInstancedata);
    void* _pInstancedata;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassMeshModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassMeshModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETMODEL_H_*/
