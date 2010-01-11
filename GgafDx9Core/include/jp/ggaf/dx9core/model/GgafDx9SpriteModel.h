#ifndef GGAFDX9SPRITEMODEL_H_
#define GGAFDX9SPRITEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteActor用モデルクラス.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:

    /** 頂点構造体 */
    struct VERTEX {
        float x, y, z;    // 頂点座標
        float nx, ny, nz; // 頂点の法線
        DWORD color;      // 頂点色（現在未使用）
        float tu, tv;     // 頂点のテクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** 頂点のFVF */
    static DWORD FVF;
    /** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
    GgafDx9RectUV* _paRectUV;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9SpriteModel(char* prm_model_name);

public:
    /** 全アニメパターン数(0～) */
    int _pattno_ani_Max;
    float _fSize_SpriteModelWidthPx;
    float _fSize_SpriteModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;

    /**
     * GgafDx9SpriteModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9SpriteActor
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
    virtual ~GgafDx9SpriteModel(); //デストラクタ
};

}
#endif /*GGAFDX9SPRITEMODEL_H_*/
