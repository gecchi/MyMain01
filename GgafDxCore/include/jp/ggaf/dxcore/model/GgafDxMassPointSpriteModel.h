#ifndef GGAFDXCORE_GGAFDXMASSPOINTSPRITEMODEL_H_
#define GGAFDXCORE_GGAFDXMASSPOINTSPRITEMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {


/**
 * TODO:現在使えません。ビデオカード依存が高い為。
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class GgafDxMassPointSpriteModel : public GgafDxMassModel {
    friend class GgafDxModelManager;

public:
//    struct VERTEX_model : public GgafDxModel::VERTEX_3D_BASE {
//        D3DCOLOR color;   // 頂点の色（オブジェクトのマテリアルカラーとして使用予定）
//        float tu, tv;     // テクスチャ座標
//    };

    struct VERTEX_model {
        float x, y, z;    // 頂点座標
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float tu, tv;     // テクスチャ座標
    };
    VERTEX_model* _paVtxBuffer_data_model;
//    WORD* _paIndexBuffer_data;

    /** オブジェクトの１辺のサイズ(px) */
    float _square_size_px;
    /** テクスチャの１辺の長さ(px) */
    float _texture_size_px;
    /** テクスチャ分割数(１で分割無し。２で４パターン、３で９パターン) */
    int _texture_split_rowcol;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassPointSpriteModel(const char* prm_model_name);

    static void createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassPointSpriteModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMASSPOINTSPRITEMODEL_H_*/
