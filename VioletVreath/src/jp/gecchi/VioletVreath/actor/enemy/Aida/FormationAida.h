#ifndef FORMATIONAIDA_H_
#define FORMATIONAIDA_H_
#include "jp/ggaf/lib/actor/FkFormation.h"

namespace VioletVreath {

/**
 * 敵機アイーダ用フォーメーション基底 .
 * @version 1.00
 * @since 2011/06/28
 * @author Masatoshi Tsuge
 */
class FormationAida : public GgafLib::FkFormation {
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_spl_id スプライン定義ID(XXX.spl の XXX)
     */
    FormationAida(const char* prm_name) ;

    virtual void onActive() override;

    virtual void onCallUpAida(EnemyAida* pEnemyAida) = 0;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合の処理実装 .
     * @param prm_pActor_last_destroyed  最後に破壊されたアクター
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationAida();
};

}
#endif /*FORMATIONAIDA_H_*/
