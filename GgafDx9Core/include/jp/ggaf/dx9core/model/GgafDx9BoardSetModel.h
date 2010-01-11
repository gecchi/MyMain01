#ifndef GGAFDX9BOARDSETMODEL_H_
#define GGAFDX9BOARDSETMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardSetActor用モデルクラス.
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardSetModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9BoardSetActor;
protected:
public:
    static int _draw_set_num_LastDraw;
    int _set_num;
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
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** インデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIDirect3DIndexBuffer9;
    /** 頂点のFVF */
    static DWORD FVF;
    /** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
    GgafDx9RectUV* _paRectUV;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9BoardSetModel(char* prm_model_name);

public:
    /** 全アニメパターン数(0～) */
    int _pattno_max;
    float _fSize_BoardSetModelWidthPx;
    float _fSize_BoardSetModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9BoardSetModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9BoardSetActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9BoardSetModel(); //デストラクタ
};

}
#endif /*GGAFDX9BOARDSETMODEL_H_*/
