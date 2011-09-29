#ifndef GGAFDXPOINTSPRITEMODEL_H_
#define GGAFDXPOINTSPRITEMODEL_H_
namespace GgafDxCore {

/**
 * GgafDxPointSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteModel : public GgafDxModel {
    friend class GgafDxModelManager;

protected:
public:
    struct VERTEX {
        float x, y, z;    // 頂点座標
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float tu, tv;     // テクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** 頂点情報配列 */
    VERTEX* _paVtxBuffer_org;
    /** 頂点数(=スプライト数) */
    int _vertices_num;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    /** オブジェクトの１辺のサイズ(px) */
    float _fSquareSize;
    /** テクスチャの１辺の長さ(px) */
    float _fTexSize;
    /** テクスチャ分割数(１で分割無し。２で４パターン、３で９パターン) */
    int _texture_split_rowcol;


    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".psprx"を追加すると定義Xファイル名になる。
     */
    GgafDxPointSpriteModel(char* prm_model_name);

public:
    /**
     * GgafDxPointSpriteModelオブジェクトの描画<BR>
     * @param   prm_pActor_Target 描画するGgafDxPointSpriteActor
     * @return  HRESULT
     */
    virtual HRESULT draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxPointSpriteModel(); //デストラクタ
};

}
#endif /*GGAFDXPOINTSPRITEMODEL_H_*/
