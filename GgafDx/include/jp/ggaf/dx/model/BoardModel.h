#ifndef GGAF_DX_BOARDMODEL_H_
#define GGAF_DX_BOARDMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/interface/IPlaneModel.h"

namespace GgafDx {

/**
 * BoardActor用モデルクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class BoardModel : public Model, public IPlaneModel {
    friend class ModelManager;
    friend class BoardActor;

public:
    struct VERTEX : public Model::VERTEX_POS {
        float tu, tv; // テクスチャ座標
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    /** 基本モデル（１キャラ分）頂点数 */
    UINT _nVertices;

    VERTEX* _paVertexBuffer_data;
//
//    float _model_width_px;
//    float _model_height_px;
//    int _row_texture_split;
//    int _col_texture_split;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".modelx"を追加するとモデル定義ファイル名になる。
     */
    BoardModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはBoardModelManagerである<BR>
     */
    virtual ~BoardModel();

};

}
#endif /*GGAF_DX_BOARDMODEL_H_*/
