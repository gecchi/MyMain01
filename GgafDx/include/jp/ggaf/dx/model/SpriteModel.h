#ifndef GGAF_DX_SPRITEMODEL_H_
#define GGAF_DX_SPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * SpriteActor用モデルクラス.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class SpriteModel : public Model {
    friend class ModelManager;

public:
    /** 頂点構造体 */
    struct VERTEX : public VERTEX_3D_BASE {
        DWORD color;      // 頂点色（現在未使用）
        float tu, tv;     // 頂点のテクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    SpriteModel(const char* prm_model_name);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~SpriteModel(); //デストラクタ
};

}
#endif /*GGAF_DX_SPRITEMODEL_H_*/
