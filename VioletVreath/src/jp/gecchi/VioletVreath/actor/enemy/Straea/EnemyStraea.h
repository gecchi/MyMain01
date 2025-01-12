#ifndef ENEMYSTRAEA_H_
#define ENEMYSTRAEA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * ストラエア .
 * 機雷。
 * @version 1.00
 * @since 2009/04/23
 * @author Masatoshi Tsuge
 */
class EnemyStraea : public VvEnemyActor<GgafLib::DefaultMeshActor> {

private:
    /** 発射済みレーザーチップ数 */
    int cnt_laserchip_;

    struct PosLaser {
        int x;
        int y;
        int z;
    };

public:
    /** レーザ発射間隔(frame) */
    int laser_interval_;
    /** 発射レーザーチップの数（レーザー長さ） */
    int laser_length_;
    /** レーザーWay数(n×n)の一辺の本数 */
    int laser_way_;
    /** レーザーとレーザーの間隔開き角度 */
    angle ang_clearance_;
    /** 方向転換角速度 */
    angvelo angvelo_turn_;
    /** レーザー発射ローカル座標 */
    PosLaser** papaPosLaser_;

    DepositoryConnection* pConn_pRefractionEffectDepository_;

    DepositoryConnection* pConn_pDepoStore_laser_set;

    GgafLib::LaserChipDepository*** papapLaserChipDepo_;

    DepositoryConnection* pConn_pShotDepo2_;
    DepositoryConnection* pConn_pShotDepo3_;

public:
    EnemyStraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    void onInactive() override;

    virtual ~EnemyStraea();
};

}
#endif /*ENEMYSTRAEA_H_*/

