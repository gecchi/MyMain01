#ifndef GGAF_DX_MASSSPRITEACTOR_H_
#define GGAF_DX_MASSSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassSpriteModel.h"

namespace GgafDx {

/**
 * スプライトセットアクター.
 * FigureActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、複数同時描画に最適化されたアクターです。<BR>
 * setMaterialColor() による個別色指定はできません(セットしても効果がありません)<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteActor : public MassActor {

public:
    /** [r]モデル資源 */
    MassSpriteModel* const _pMassSpriteModel;
    /** [r]エフェクト資源 */
    MassSpriteEffect* const _pMassSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

//    Align _align;
//    Valign _valign;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    MassSpriteActor(const char* prm_name,
                    const char* prm_model_id,
                    const char* prm_effect_id,
                    const char* prm_technique,
                    Checker* prm_pChecker );

//    virtual void setAlign(Align prm_align, Valign prm_valign);
//    virtual void setAlign(Align prm_align);
//    virtual void setValign(Valign prm_valign);

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~MassSpriteActor();
};

}
#endif /*GGAF_DX_MASSSPRITEACTOR_H_*/
