#ifndef GGAF_DX_FRAMEDBOARDMODEL_H_
#define GGAF_DX_FRAMEDBOARDMODEL_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/interface/IPlaneModel.h"

namespace GgafDx {

/**
 * FramedBoardActor用モデルクラス.
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class FramedBoardModel : public Model, public IPlaneModel {
    friend class ModelManager;
    friend class FramedBoardActor;

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
    struct VERTEX : public Model::VERTEX_POS {
        float index;      // psizeではなくてはなくて頂点番号を埋め込む。シェーダー側で何セット目かを判断するために使用。
        float tu, tv;     // 頂点のテクスチャ座標
    };

    /** 頂点バッファの各セット */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    UINT _nVertices;
    INDEXPARAM _indexParam;
    VERTEX* _paVertexBuffer_data;
    WORD* _paIndexBuffer_data;

    float _model_frame_width_px;
    float _model_frame_height_px;
    int _row_frame_texture_split;
    int _col_frame_texture_split;


public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    FramedBoardModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~FramedBoardModel(); //デストラクタ
};

}
#endif /*GGAF_DX_BOARDSETMODEL_H_*/
