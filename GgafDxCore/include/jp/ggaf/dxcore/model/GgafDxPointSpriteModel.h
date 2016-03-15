#ifndef GGAFDXCORE_GGAFDXPOINTSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * GgafDxPointSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    struct VERTEX {
        float x, y, z;    // 頂点座標
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float tu, tv;     // テクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** 頂点情報配列 */
    VERTEX* _paVtxBuffer_data;
    /** 頂点数(=スプライト数) */
    int _vertices_num;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    /** オブジェクトの１辺のサイズ(px) */
    float _square_size_px;
    /** テクスチャの１辺の長さ(px) */
    float _texture_size_px;
    /** テクスチャ分割数(１で分割無し。２で４パターン、３で９パターン) */
    int _texture_split_rowcol;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".psprx"を追加すると定義Xファイル名になる。
     */
    GgafDxPointSpriteModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

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
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITEMODEL_H_*/
