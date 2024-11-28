#ifndef ENEMYSTRAEALASERCHIP003_H_
#define ENEMYSTRAEALASERCHIP003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

namespace VioletVreath {

class EnemyStraeaLaserChip003 : public VvEnemyActor<GgafLib::WateringLaserChip> {

public:
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader_;

public:
    EnemyStraeaLaserChip003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~EnemyStraeaLaserChip003();

};

}
#endif /*ENEMYSTRAEALASERCHIP003_H_*/

