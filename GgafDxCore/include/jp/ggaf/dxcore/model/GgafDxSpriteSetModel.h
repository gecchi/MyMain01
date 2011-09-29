#ifndef GGAFDXSPRITESETMODEL_H_
#define GGAFDXSPRITESETMODEL_H_
namespace GgafDxCore {

/**
 * GgafDxSpriteSetActor用モデルクラス.
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetModel : public GgafDxModel {
    friend class GgafDxModelManager;

protected:
public:
    static int _draw_set_num_LastDraw;
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
        float nx, ny, nz; // 頂点の法線
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
//    GgafDxRectUV* _paRectUV;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    INDEXPARAM* _paIndexParam;
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxSpriteSetModel(char* prm_model_name);

public:
    /** 全アニメパターン数(0～) */
//    int _pattno_uvflip_Max;
    float _fSize_SpriteSetModelWidthPx;
    float _fSize_SpriteSetModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDxSpriteSetModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDxSpriteSetActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxSpriteSetModel(); //デストラクタ
};

}
#endif /*GGAFDXSPRITESETMODEL_H_*/
