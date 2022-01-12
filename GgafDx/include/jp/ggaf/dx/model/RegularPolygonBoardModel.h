#ifndef GGAF_DX_REGULARPOLYGONBOARDMODEL_H_
#define GGAF_DX_REGULARPOLYGONBOARDMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

/**
 * RegularPolygonBoardActor用モデルクラス.
 * @version 1.00
 * @since 2009/03/10
 * @author Masatoshi Tsuge
 */
class RegularPolygonBoardModel : public Model {
    friend class ModelManager;
    friend class RegularPolygonBoardActor;

public:
    struct VERTEX {
        float x, y, z; // 頂点座標
        float tu, tv; // テクスチャ座標
    };

    /** 頂点のFVF */
    static DWORD FVF;
    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    VERTEX* _pVertexBuffer_data;
    float _model_width_px;
    float _model_height_px;
    int _row_texture_split;
    int _col_texture_split;

    /** FAN描画順方向 1:時計回り/1以外:反時計回り */
    int _drawing_order;
    /** 正何角形か */
    int _angle_num;
    /** 最初の頂点の x 座標 */
    float _y_center;
    /** 最初の頂点の y 座標 */
    float _x_center;
    /** 最初の頂点の u 座標 */
    float _u_center;
    /** 最初の頂点の v 座標 */
    float _v_center;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    RegularPolygonBoardModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはRegularPolygonBoardModelManagerである<BR>
     */
    virtual ~RegularPolygonBoardModel(); //デストラクタ

};

}
#endif /*GGAF_DX_REGULARPOLYGONBOARDMODEL_H_*/
