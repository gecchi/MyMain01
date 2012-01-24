#ifndef GGAFDXBOARDMODEL_H_
#define GGAFDXBOARDMODEL_H_
namespace GgafDxCore {

/**
 * GgafDxBoardActor用モデルクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class GgafDxBoardModel : public GgafDxModel {
    friend class GgafDxModelManager;
    friend class GgafDxBoardActor;
protected:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxBoardModel(char* prm_model_name);

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
//    GgafDxRectUV* _paRectUV;

    /** 全アニメパターン数 */
//    int _pattno_max;
    float _fSize_BoardModelWidthPx;
    float _fSize_BoardModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxBoardModelManagerである<BR>
     */
    virtual ~GgafDxBoardModel(); //デストラクタ

};

}
#endif /*GGAFDXBOARDMODEL_H_*/
