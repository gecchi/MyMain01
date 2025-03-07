#ifndef GGAF_DX_FRAMEDBOARDACTOR_H_
#define GGAF_DX_FRAMEDBOARDACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D表示用枠ありの板ポリアクター .
 * いくら拡大しても、四隅の画像は拡大さません。<BR>
 * ウィンドウ表示等に利用を想定<BR>
 * @version 1.00
 * @since 2017/08/21
 * @author Masatoshi Tsuge
 */
class FramedBoardActor : public FigureActor, public IAlignAbleActor {
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
    FramedBoardModel* _pFramedBoardModel;
    /** [r]エフェクト */
    FramedBoardEffect* const _pFramedBoardEffect;
    /** [r]UVフリッパー(中心のメイン) */
    UvFlipper* const _pUvFlipper;
    /** [r]UVフリッパー(周囲フレーム) */
    UvFlipper* const _pUvFlipper_frame;

    /** [r]モデルのオリジナルの周囲フレームの幅(px) */
    const pixcoord _model_frame_width_px;
    /** [r]モデルのオリジナルの周囲フレームの高さ(px) */
    const pixcoord _model_frame_height_px;
    /** [r]モデルのオリジナルの中心のメインの幅(px) */
    const pixcoord _model_center_width_px;
    /** [r]モデルのオリジナルの中心のメインの高さ(px) */
    const pixcoord _model_center_height_px;
    /** [r]モデルのオリジナルの全体の幅(px) */
    const pixcoord _model_total_width_px;
    /** [r]モデルのオリジナルの全体の高さ(px) */
    const pixcoord _model_total_height_px;
    /** [r]角がゆがまないで表示できる限界の _sx */
    const scale _lim_center_sx;
    /** [r]角がゆがまないで表示できる限界の _sy */
    const scale _lim_center_sy;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".fsprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @return
     */
    FramedBoardActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique );

    virtual void processDraw() override;

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    inline UvFlipper* getFrameUvFlipper() {
        return _pUvFlipper_frame;
    }
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

    /**
     * 外枠も含めたトータルの横幅を設定する .
     * 内部的には、_sx を計算して設定します。
     * @param prm_width 横幅
     */
    virtual void setWidth(coord prm_width);

    /**
     * 外枠も含めたトータルの高さを設定する .
     * 内部的には、_sy を計算して設定します。
     * @param prm_height
     */
    virtual void setHeight(coord prm_height);

    /**
     * 横幅を増やす .
     * 基本的に四隅の枠の大きさはそのままで、中心さが変化しますが、
     * 限界を越えると 四隅も伸縮します。
     * 内部的には、_sx を計算して設定します。
     * @param prm_width 横幅増分
     */
    virtual void addWidth(coord prm_width);

    /**
     * 高さを増やす .
     * 基本的に四隅の枠の大きさはそのままで、中心さが変化しますが、
     * 限界を越えると 四隅も伸縮します。
     * 内部的には、_sy を計算して設定します。
     * @param prm_height 高さ増分
     */
    virtual void addHeight(coord prm_height);

    /**
     * 外枠も含めたトータルの横幅を取得 .
     * @return
     */
    virtual coord getWidth();

    /**
     * 外枠も含めたトータルの高さを取得 .
     * @return
     */
    virtual coord getHeight();


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

    virtual ~FramedBoardActor();
};

}
#endif /*GGAF_DX_FRAMEDBOARDACTOR_H_*/
