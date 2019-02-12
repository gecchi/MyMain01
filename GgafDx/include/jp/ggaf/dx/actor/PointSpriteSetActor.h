#ifndef GGAF_DX_POINTSPRITESETACTOR_H_
#define GGAF_DX_POINTSPRITESETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * ポイントスプライトセット .
 * FigureActor を継承し、ポイントスプライト表示機能を<BR>
 * 追加、さらに同一モデル複数オブジェクトの頂点バッファを持ち、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class PointSpriteSetActor : public FigureActor {

public:
    /** [r]モデル資源 */
    PointSpriteSetModel* const _pPointSpriteSetModel;
    /** [r]エフェクト資源 */
    PointSpriteSetEffect* const _pPointSpriteSetEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;
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
    PointSpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       GgafCore::Status* prm_pStat,
                       Checker* prm_pChecker );


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
    PointSpriteSetActor(const char* prm_name,
                       const char* prm_model_id,
                       const char prm_model_type,
                       const char* prm_effect_id,
                       const char prm_effect_type,
                       const char* prm_technique,
                       GgafCore::Status* prm_pStat,
                       Checker* prm_pChecker);

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual void processDraw() override;

    virtual ~PointSpriteSetActor(); //デストラクタ
};

}
#endif /*GGAF_DX_POINTSPRITESETACTOR_H_*/
