#ifndef GGAF_DX_POINTSPRITESETMODEL_H_
#define GGAF_DX_POINTSPRITESETMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class PointSpriteSetModel : public Model {
    friend class ModelManager;

public:
    struct VERTEX : public Model::VERTEX_POS {
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float ini_ptn_no, index;     //
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ（ｎキャラ分） */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;

    /** オブジェクトの１辺のサイズ(px) */
    float _square_size_px;
    /** テクスチャの１辺の長さ(px) */
    float _texture_size_px;
    /** テクスチャ分割数(１で分割無し。２で４パターン、３で９パターン) */
    int _texture_split_rowcol;

    float _inv_texture_split_rowcol;
    /** １頂点のサイズ */
    UINT _size_vertex_unit;
    /** 基本モデル（１キャラ分）頂点サイズ計 */
    UINT _size_vertices;
    /** 基本モデル（１キャラ分）頂点数 */
    UINT _nVertices;

    VERTEX* _paVtxBuffer_data;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    PointSpriteSetModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~PointSpriteSetModel();
};

}
#endif /*GGAF_DX_POINTSPRITESETMODEL_H_*/
