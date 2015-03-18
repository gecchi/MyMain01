#ifndef ENEMYHISBELASERCHIP003_H_
#define ENEMYHISBELASERCHIP003_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

class EnemyHisbeLaserChip003 : public GgafLib::WateringLaserChip {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    int sp_index_;
    GgafLib::DefaultScene* pNearestScrollingScene_;
public:
    EnemyHisbeLaserChip003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;
    void processSettlementBehavior() override;
    void processJudgement() override;
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyHisbeLaserChip003();

};

}
#endif /*ENEMYHISBELASERCHIP003_H_*/

