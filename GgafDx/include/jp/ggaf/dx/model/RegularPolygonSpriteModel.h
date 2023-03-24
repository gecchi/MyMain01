#ifndef GGAF_DX_REGULARPOLYGONSPRITEMODEL_H_
#define GGAF_DX_REGULARPOLYGONSPRITEMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/interface/IPlaneModel.h"

namespace GgafDx {

/**
 * RegularPolygonSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class RegularPolygonSpriteModel : public Model, public IPlaneModel {
    friend class ModelManager;

public:
    /** 頂点構造体 */
    struct VERTEX : public VERTEX_POS_NOMAL {
        DWORD color;      // 頂点色（現在未使用）
        float tu, tv;     // 頂点のテクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    VERTEX* _paVertexBuffer_data;
    /** FAN描画順方向 1:時計回り/1以外:反時計回り */
    int _drawing_order;
    /** 正何角形か */
    int _angle_num;
    /** 最初の頂点の u 座標 */
    float _u_center;
    /** 最初の頂点の v 座標 */
    float _v_center;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    RegularPolygonSpriteModel(const char* prm_model_id);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * FAN描画順方向を取得。
     * @return 1:時計回り/1以外:反時計回り
     */
    int getDrawingOrder() {
        return _drawing_order;
    }

    /**
     * 正何角形の描画かを返す
     * @return 正何角形の描画か(=FANの数)
     */
    int getAngleNum() {
        return _angle_num;
    }

    /**
     * デストラクタ<BR>
     */
    virtual ~RegularPolygonSpriteModel();
};

}
#endif /*GGAF_DX_REGULARPOLYGONSPRITEMODEL_H_*/
