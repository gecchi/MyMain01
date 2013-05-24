#ifndef ENEMYHERMIONEARMHEAD_H_
#define ENEMYHERMIONEARMHEAD_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Hermione/EnemyHermioneArm.h"

namespace VioletVreath {

/**
 * 敵機ヘルミオネの触手の頭 .
 * グラの触手に挑戦ッッ！！！
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArmHead : public EnemyHermioneArm {

public:
    /** [r/w]ハッチから発射されるアクターをメンバーに持つデポジトリ */
//    DepositoryConnection* pDepoConnection_;
//    GgafCore::GgafActorDepository* pDepo_Fired_;

public:
    EnemyHermioneArmHead(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHermioneArmHead();
};

}
#endif /*ENEMYHERMIONEARMHEAD_H_*/

