#ifndef GGAFDX9BOARDMODEL_H_
#define GGAFDX9BOARDMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9BoardActor用モデルクラス.
 */
class GgafDx9BoardModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;
    friend class GgafDx9BoardActor;
protected:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9BoardModel(char* prm_model_name);

public:
    struct VERTEX {
        float x, y, z; // 頂点座標
        float tu, tv; // テクスチャ座標
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;

    /** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
    GgafDx9RectUV* _paRectUV;

    /** 全アニメパターン数 */
    int _pattno_max;
    float _fSize_BoardModelWidthPx;
    float _fSize_BoardModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9BoardModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9BoardActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

    virtual void restore();

    virtual void onDeviceLost();

    virtual void release();

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9BoardModelManagerである<BR>
     */
    virtual ~GgafDx9BoardModel(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDMODEL_H_*/
