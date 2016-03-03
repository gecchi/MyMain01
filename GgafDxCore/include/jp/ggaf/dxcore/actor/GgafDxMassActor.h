#ifndef GGAFDXCORE_GGAFDXMASSACTOR_H_
#define GGAFDXCORE_GGAFDXMASSACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"

namespace GgafDxCore {

/**
 * メッシュアクター.
 * GgafDxFigureActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * インスタンシングにより、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassActor : public GgafDxFigureActor {

public:
    /** [r]モデル資源 */
    GgafDxMassModel* const _pMassModel;
    /** [r]エフェクト資源 */
    GgafDxMassEffect* const _pMassEffect;

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
    GgafDxMassActor(const char* prm_name,
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
    GgafDxMassActor(const char* prm_name,
                    const char* prm_model_id,
                    const char* prm_model_type,
                    const char* prm_effect_id,
                    const char* prm_effect_type,
                    const char* prm_technique,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDxChecker* prm_pChecker);


    virtual ~GgafDxMassActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMASSMESHACTOR_H_*/
