#ifndef ENEMYHISBELASERCHIP001_H_
#define ENEMYHISBELASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

/**
 * 敵機ヒズビーのレーザーチップその1 .
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyHisbeLaserChip001 : public VvEnemyActor<GgafLib::HomingLaserChip> {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineLeader* pRikishaLeader_;
    GgafLib::DefaultScene* pScrollingScene_;

public:
    EnemyHisbeLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;
    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~EnemyHisbeLaserChip001();

};

}
#endif /*ENEMYHISBELASERCHIP001_H_*/

