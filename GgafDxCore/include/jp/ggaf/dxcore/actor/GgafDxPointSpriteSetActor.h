#ifndef GGAFDXCORE_GGAFDXPOINTSPRITESETACTOR_H_
#define GGAFDXCORE_GGAFDXPOINTSPRITESETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * ポイントスプライトセット .
 * GgafDxFigureActor を継承し、ポイントスプライト表示機能を<BR>
 * 追加、さらに同一モデル複数オブジェクトの頂点バッファを持ち、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class GgafDxPointSpriteSetActor : public GgafDxFigureActor {

public:
    /** [r]モデル資源 */
    GgafDxPointSpriteSetModel* const _pPointSpriteSetModel;
    /** [r]エフェクト資源 */
    GgafDxPointSpriteSetEffect* const _pPointSpriteSetEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* const _pUvFlipper;
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
    GgafDxPointSpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafCore::GgafStatus* prm_pStat,
                       GgafDxChecker* prm_pChecker );


    /**
     * 下位継承用コンストラクタ
     * @param prm_name アクター名称（任意）
     * @param prm_model_id モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxPointSpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char prm_model_type,
                       const char* prm_effect_id,
                       const char prm_effect_type,
                       const char* prm_technique,
                       GgafCore::GgafStatus* prm_pStat,
                       GgafDxChecker* prm_pChecker);

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual void processDraw() override;

    virtual ~GgafDxPointSpriteSetActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITESETACTOR_H_*/
