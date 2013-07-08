#ifndef ENEMYERMIONEARMHEAD_H_
#define ENEMYERMIONEARMHEAD_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

/**
 * 敵機エミオネの触手の頭 .
 * グラの触手に挑戦ッッ！！！
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArmHead : public EnemyErmioneArm {

public:
    /** [r/w]ハッチから発射されるアクターをメンバーに持つデポジトリ */
//    DepositoryConnection* pDepoConnection_;
//    GgafCore::GgafActorDepository* pDepo_Fired_;

public:
    EnemyErmioneArmHead(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyErmioneArmHead();
};

}
#endif /*ENEMYERMIONEARMHEAD_H_*/

