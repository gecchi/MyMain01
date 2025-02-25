#ifndef GGAF_DX_MASSBOARDACTOR_H_
#define GGAF_DX_MASSBOARDACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassBoardModel.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D表示用板ポリアクター（大量表示用） .
 * DirectX の インスタシイング により、同一モデルは大量表示に最適化<BR>
 * 但し、回転機能はなし、拡大縮小機能もなし。<BR>
 * 文字表示に使用することを想定。<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassBoardActor : public MassActor, public IAlignAbleActor {
private:

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void appendChildAsFk(GeometricActor* prm_pGeoActor,
                          int prm_x_init_local,
                          int prm_y_init_local,
                          int prm_z_init_local,
                          int prm_rx_init_local,
                          int prm_ry_init_local,
                          int prm_rz_init_local) override {
        throwCriticalException("使用不可です。");
    }
public:
    /** [r]モデルオブジェクトへのポインタ */
    MassBoardModel* _pMassBoardModel;
    /** [r]エフェクト */
    MassBoardEffect* const _pMassBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".sprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @return
     */
    MassBoardActor(const char* prm_name,
                   const char* prm_model,
                   const char* prm_effect_id,
                   const char* prm_technique);

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

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~MassBoardActor();
};

}
#endif /*GGAF_DX_MASSBOARDACTOR_H_*/
