#ifndef GGAF_DX_SPRITEACTORD_H_
#define GGAF_DX_SPRITEACTORD_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

#include "jp/ggaf/dx/Config.h"

namespace GgafDx {

/**
 * スプライトアクター.
 * 板ポリゴンにテクスチャを貼り付けた<BR>
 * 所謂擬似スプライトのアクターです。<BR>
 * @version 1.00
 * @since 2007/11/14
 * @author Masatoshi Tsuge
 */
class SpriteActor : public FigureActor, public IAlignAbleActor {

public:
    /** [r]モデル資源 */
    SpriteModel* _pSpriteModel;
    /** [r]エフェクト資源 */
    SpriteEffect* const _pSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".sprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pColliChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    SpriteActor(const char* prm_name,
                const char* prm_model,
                const char* prm_effect_id,
                const char* prm_technique);

    virtual void processDraw() override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
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

    virtual ~SpriteActor();
};

}
#endif /*GGAF_DX_SPRITEACTORD_H_*/
