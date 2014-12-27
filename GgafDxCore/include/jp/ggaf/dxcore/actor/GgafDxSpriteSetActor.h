#ifndef GGAFDXCORE_GGAFDXSPRITESETACTOR_H_
#define GGAFDXCORE_GGAFDXSPRITESETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * スプライトセットアクター.
 * GgafDxDrawableActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、複数同時描画に最適化されたアクターです。<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetActor : public GgafDxDrawableActor {
private:
    void setMaterialColor(float r, float g, float b) override {
        throwGgafCriticalException("GgafDxSpriteSetActor::setMaterialColor は使用不可です。(1)");
    }
    void setMaterialColor(const GgafCore::GgafRgb* prm_rgb) override {
        throwGgafCriticalException("GgafDxSpriteSetActor::setMaterialColor は使用不可です。(2)");
    }
    void resetMaterialColor() override {
        throwGgafCriticalException("GgafDxSpriteSetActor::resetMaterialColor は使用不可です。");
    }

public:
    /** [r]モデル資源 */
    GgafDxSpriteSetModel* const _pSpriteSetModel;
    /** [r]エフェクト資源 */
    GgafDxSpriteSetEffect* const _pSpriteSetEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;

    GgafDxAlign _align;
    GgafDxValign _valign;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxSpriteSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteSetActor();

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }
};

}
#endif /*GGAFDXCORE_GGAFDXSPRITESETACTOR_H_*/
