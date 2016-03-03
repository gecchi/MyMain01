#ifndef GGAFDXCORE_GGAFDXMASSSPRITEACTOR_H_
#define GGAFDXCORE_GGAFDXMASSSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMassSpriteModel.h"

namespace GgafDxCore {

/**
 * スプライトセットアクター.
 * GgafDxFigureActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、複数同時描画に最適化されたアクターです。<BR>
 * setMaterialColor() による個別色指定はできません(セットしても効果がありません)<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class GgafDxMassSpriteActor : public GgafDxMassActor {

public:
    /** [r]モデル資源 */
    GgafDxMassSpriteModel* const _pMassSpriteModel;
    /** [r]エフェクト資源 */
    GgafDxMassSpriteEffect* const _pMassSpriteEffect;
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
    GgafDxMassSpriteActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafCore::GgafStatus* prm_pStat,
                          GgafDxChecker* prm_pChecker );

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign);
    virtual void setAlign(GgafDxAlign prm_align);
    virtual void setValign(GgafDxValign prm_valign);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~GgafDxMassSpriteActor();
};

}
#endif /*GGAFDXCORE_GGAFDXMASSSPRITEACTOR_H_*/
