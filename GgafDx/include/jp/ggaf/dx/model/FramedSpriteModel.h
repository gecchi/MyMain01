#ifndef GGAF_DX_FRAMEDSPRITEMODEL_H_
#define GGAF_DX_FRAMEDSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * FramedSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2022/01/25
 * @author Masatoshi Tsuge
 */
class FramedSpriteModel : public Model {
    friend class ModelManager;

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
    struct VERTEX : public VERTEX_POS_NOMAL {
        float index;      // psizeではなくてはなくて頂点番号を埋め込む。シェーダー側で何セット目かを判断するために使用。
        DWORD color;      // 頂点色（現在未使用）
        float tu, tv;     // 頂点のテクスチャ座標
    };
    INDEXPARAM _indexParam;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** 頂点のFVF */
    static DWORD FVF;

    VERTEX* _paVertexBuffer_data;
    WORD* _pIndexBuffer_data;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    /** 基本モデル（１キャラ分）頂点数 */
    UINT _nVertices;

    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

    float _model_frame_width_px;
    float _model_frame_height_px;
    int _row_frame_texture_split;
    int _col_frame_texture_split;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    FramedSpriteModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~FramedSpriteModel(); //デストラクタ
};

}
#endif /*GGAF_DX_FRAMEDSPRITEMODEL_H_*/
