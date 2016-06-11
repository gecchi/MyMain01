#ifndef GGAFDXCORE_GGAFDXPOINTSPRITESETMODEL_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITESETMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteSetModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    struct VERTEX {
        float x, y, z;    // 頂点座標
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float ini_ptn_no, index;     //
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ（ｎキャラ分） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;

    /** オブジェクトの１辺のサイズ(px) */
    float _square_size_px;
    /** テクスチャの１辺の長さ(px) */
    float _texture_size_px;
    /** テクスチャ分割数(１で分割無し。２で４パターン、３で９パターン) */
    int _texture_split_rowcol;
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
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxPointSpriteSetModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxPointSpriteSetModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITESETMODEL_H_*/
