#ifndef FORMATIONIDA_H_
#define FORMATIONIDA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FkFormation.h"

namespace VioletVreath {

/**
 * 敵機イーダ用フォーメーション基底 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class FormationIda : public GgafLib::FkFormation {

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_ldr_id 曲線移動の情報ID(XXX.ldr の XXX)
     */
    FormationIda(const char* prm_name) ;

    virtual void onActive() override;

    virtual void onCalledUpIda(EnemyIda* pEnemyIda) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual ~FormationIda();
};

}
#endif /*FORMATIONIDA_H_*/
