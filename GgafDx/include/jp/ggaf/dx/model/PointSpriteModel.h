#ifndef GGAF_DX_POINTSPRITEMODEL_H_
#define GGAF_DX_POINTSPRITEMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * PointSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class PointSpriteModel : public Model {
    friend class ModelManager;

public:
    struct VERTEX : public Model::VERTEX_POS {
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float tu, tv;     // テクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
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
    float _inv_texture_split_rowcol;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".psprx"を追加すると定義Xファイル名になる。
     */
    PointSpriteModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~PointSpriteModel();
};

}
#endif /*GGAF_DX_POINTSPRITEMODEL_H_*/
