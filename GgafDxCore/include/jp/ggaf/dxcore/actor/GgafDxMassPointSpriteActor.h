#ifndef GGAFDXCORE_GGAFDXMASSPOINTSPRITEACTOR_H_
#define GGAFDXCORE_GGAFDXMASSPOINTSPRITEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMassPointSpriteModel.h"

namespace GgafDxCore {

/**
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class GgafDxMassPointSpriteActor : public GgafDxMassActor {

public:
    /** [r]モデル資源 */
    GgafDxMassPointSpriteModel* const _pMassPointSpriteModel;
    /** [r]エフェクト資源 */
    GgafDxMassPointSpriteEffect* const _pMassPointSpriteEffect;
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
    GgafDxMassPointSpriteActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafCore::GgafStatus* prm_pStat,
                               GgafDxChecker* prm_pChecker );

    inline GgafDxUvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    virtual ~GgafDxMassPointSpriteActor();
};

}
#endif /*GGAFDXCORE_GGAFDXMASSSPRITEACTOR_H_*/
