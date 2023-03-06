#ifndef GGAF_DX_MASSACTOR_H_
#define GGAF_DX_MASSACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/model/MassModel.h"

namespace GgafDx {

/**
 * メッシュアクター（大量表示用） .
 * Xファイル定義のメッシュ表示機能を<BR>
 * インスタンシングにより、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassActor : public FigureActor {

public:
    /** [r]モデル資源 */
    MassModel* _pMassModel;
    /** [r]エフェクト資源 */
    MassEffect* const _pMassEffect;

public:

    /**
     * 下位継承用コンストラクタ
     * @param prm_name アクター名称（任意）
     * @param prm_model モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    MassActor(const char* prm_name,
              const char* prm_model,
              const char prm_model_type,
              const char* prm_effect_id,
              const char prm_effect_type,
              const char* prm_technique,
              CollisionChecker* prm_pChecker);


    virtual ~MassActor(); //デストラクタ
};

}
#endif /*GGAF_DX_MASSMESHACTOR_H_*/
