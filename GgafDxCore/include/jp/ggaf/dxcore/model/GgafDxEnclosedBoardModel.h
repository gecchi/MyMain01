#ifndef GGAFDXCORE_GGAFDXENCLOSEDBOARDMODEL_H_
#define GGAFDXCORE_GGAFDXENCLOSEDBOARDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * GgafDxEnclosedBoardActor用モデルクラス.
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class GgafDxEnclosedBoardModel : public GgafDxModel {
    friend class GgafDxModelManager;
    friend class GgafDxEnclosedBoardActor;

public:
    struct INDEXPARAM {
        UINT MaterialNo;
        INT BaseVertexIndex;
        UINT MinIndex;
        UINT NumVertices;
        UINT StartIndex;
        UINT PrimitiveCount;
    };

    /** 頂点構造体 */
    struct VERTEX {
        float x, y, z;    // 頂点座標
        float index;      // psizeではなくてはなくて頂点番号を埋め込む。シェーダー側で何セット目かを判断するために使用。
        float tu, tv;     // 頂点のテクスチャ座標
    };

    /** 頂点バッファの各セット */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    INDEXPARAM _indexParam;

    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;


public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxEnclosedBoardModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxEnclosedBoardModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXBOARDSETMODEL_H_*/
