#ifndef GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

/**
 * GgafDxRegularPolygonSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2018/10/18
 * @author Masatoshi Tsuge
 */
class GgafDxRegularPolygonSpriteModel : public GgafDxModel {
    friend class GgafDxModelManager;

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
    /** FAN描画の円周開始位置(rad) */
    float _circumference_begin_position;
    /** FAN描画順方向 1:時計回り/1以外:反時計回り */
    int _drawing_order;
    /** 正何角形か */
    int _angle_num;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxRegularPolygonSpriteModel(const char* prm_model_name);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

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
     * FAN描画の円周開始位置(rad)を取得
     * @return FAN描画の円周開始位置(rad)
     */
    angle getCircumferenceBeginPosition() {
        return _circumference_begin_position;
    }

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxRegularPolygonSpriteModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXREGULARPOLYGONSPRITEMODEL_H_*/
