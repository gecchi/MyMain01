#ifndef ENEMYTHISBELASERCHIP003_H_
#define ENEMYTHISBELASERCHIP003_H_
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

class EnemyThisbeLaserChip003 : public GgafLib::WateringLaserChip {

public:
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    int sp_index_;
    GgafLib::DefaultScene* pNearestScrollingScene_;
public:
    EnemyThisbeLaserChip003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;
    void processSettlementBehavior() override;
    void processJudgement() override;
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyThisbeLaserChip003();

};

}
#endif /*ENEMYTHISBELASERCHIP003_H_*/

