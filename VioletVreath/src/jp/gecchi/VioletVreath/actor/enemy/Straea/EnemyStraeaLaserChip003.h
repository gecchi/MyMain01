#ifndef ENEMYSTRAEALASERCHIP003_H_
#define ENEMYSTRAEALASERCHIP003_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip003 : public GgafLib::WateringLaserChip {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineLeader* pKurokoLeader_;

public:
    EnemyStraeaLaserChip003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyStraeaLaserChip003();

};

}
#endif /*ENEMYSTRAEALASERCHIP003_H_*/

