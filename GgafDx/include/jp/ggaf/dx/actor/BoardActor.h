#ifndef GGAF_DX_BOARDACTORD_H_
#define GGAF_DX_BOARDACTORD_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D表示用板ポリアクター .
 * 板ポリゴンにテクスチャを貼り付けたアクター。<BR>
 * テクスチャの１ピクセルをそのまま１ドットで表示したい時に使用。<BR>
 * 表示に特化しており、深度で大きさが変わりません。<BR>
 * 当たり判定オブジェクトは保持しません。<BR>
 * 座標系は左上が (0,0) で 右下に向かって X座標、Y座標増加する仕様。<BR>
 * 回転機能(Z軸回転のみ)、拡大縮小機能機能あり。<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class BoardActor : public FigureActor, public IAlignAbleActor {

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GroupHead* appendGroupChildAsFk(kind_t prm_kind,
                                              GeometricActor* prm_pGeoActor,
                                              int prm_x_init_local,
                                              int prm_y_init_local,
                                              int prm_z_init_local,
                                              int prm_rx_init_local,
                                              int prm_ry_init_local,
                                              int prm_rz_init_local) override {
        throwCriticalException("使用不可です。");
        return nullptr;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GroupHead* appendGroupChildAsFk(GeometricActor* prm_pGeoActor,
                                             int prm_x_init_local,
                                             int prm_y_init_local,
                                             int prm_z_init_local,
                                             int prm_rx_init_local,
                                             int prm_ry_init_local,
                                             int prm_rz_init_local) override {
        throwCriticalException("使用不可です。");
        return nullptr;
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    BoardModel* const _pBoardModel;
    /** [r]エフェクト */
    BoardEffect* const _pBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

//    Align _align;
//    Valign _valign;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".sprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @return
     */
    BoardActor(const char* prm_name,
               const char* prm_model,
               const char* prm_effect_id,
               const char* prm_technique,
               CollisionChecker* prm_pChecker = nullptr);

    virtual void processDraw() override;

    virtual ~BoardActor(); //デストラクタ

//    virtual void setAlign(Align prm_align, Valign prm_valign);
//    virtual void setAlign(Align prm_align);
//    virtual void setValign(Valign prm_valign);

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;
    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;
    virtual void setScale(scale s) override;
    virtual void setScale(scale sx, scale sy) override;
    virtual void setScale(scale sx, scale sy, scale sz) override;
    virtual void setScaleR(float prm_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) override;
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override;
    virtual void addScaleX(scale dsx) override {
        _sx += dsx;
    }
    virtual void addScaleY(scale dsy) override {
        _sy += dsy;
    }
    virtual void addScaleZ(scale dsz) override {
        _sz += dsz;
    }

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

//    float getModelWidth();
//    float getModelHeight();

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }
};

}
#endif /*GGAF_DX_BOARDACTORD_H_*/
