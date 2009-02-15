#ifndef GGAFDX9SPRITEMODEL_H_
#define GGAFDX9SPRITEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteActor用モデルクラス.
 */
class GgafDx9SpriteModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:
    struct VERTEX {
        float x, y, z; // 頂点座標
        float nx, ny, nz; // 法線
        DWORD color; // 頂点の色
        float tu, tv; // テクスチャ座標
    };

    /** VERTEXのFVF */
    static DWORD FVF;
    /** 頂点バッファへのポインタ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** マテリアル */
    D3DMATERIAL9* _pD3DMaterial9_default;
    /** テクスチャ(アニメーションパターン） */
    GgafDx9TextureConnection* _pTextureCon;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertecs;
    /** 1頂点のサイズ */
    UINT _size_vertec_unit;
    /** アニメーショーンのためのテクスチャの座標の配列（要素数はアニメーション数） */
    GgafDx9RectUV* _paRectUV;

    /** 前回表示のUV */
    GgafDx9RectUV* _pRectUV_drawlast;

    //bool _isChangedAlpha;

    /**
     * コンストラクタ<BR>
     * @param prm_spritemodel_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9SpriteModel(char* prm_spritemodel_name);

public:
    /** 全アニメパターン数(0～) */
    int _pattno_ani_Max;
    float _fSize_SpriteModelWidthPx;
    float _fSize_SpriteModelHeightPx;
    int _row_texture_split;
    int _col_texture_split;
    //int	   _iChangeVertexAlpha;


    /**
     * GgafDx9SpriteModelオブジェクトの描画<BR>
     * @param	prm_pActor_Target 描画するGgafDx9SpriteActor
     * @return	HRESULT
     */
    virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target);

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
