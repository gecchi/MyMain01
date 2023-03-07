#ifndef GGAF_DX_FRAMEDSPRITEACTOR_H_
#define GGAF_DX_FRAMEDSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 枠ありのスプライトアクター.
 * いくら拡大しても、四隅の画像は拡大さません。<BR>
 * ウィンドウ表示等に利用を想定<BR>
 * @version 1.00
 * @since 2022/01/25
 * @author Masatoshi Tsuge
 */
class FramedSpriteActor : public FigureActor, public IAlignAbleActor {

public:
    /** [r]モデル資源 */
    FramedSpriteModel* _pFramedSpriteModel;
    /** [r]エフェクト資源 */
    FramedSpriteEffect* const _pFramedSpriteEffect;
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

    float _far_rate;
//    Align _align;
//    Valign _valign;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".fsprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    FramedSpriteActor(const char* prm_name,
                      const char* prm_model,
                      const char* prm_effect_id,
                      const char* prm_technique,
                      CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    inline UvFlipper* getFrameUvFlipper() {
        return _pUvFlipper_frame;
    }

    /**
     * 遠くの座標でも強制表示 .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
//    virtual void setAlign(Align prm_align, Valign prm_valign);
//    virtual void setAlign(Align prm_align);
//    virtual void setValign(Valign prm_valign);

    void setWidth(coord prm_width);
    void setHeight(coord prm_height);
    void addWidth(coord prm_width);
    void addHeight(coord prm_height);
    coord getWidth();
    coord getHeight();
    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~FramedSpriteActor();
};

}
#endif /*GGAF_DX_FRAMEDSPRITEACTOR_H_*/
