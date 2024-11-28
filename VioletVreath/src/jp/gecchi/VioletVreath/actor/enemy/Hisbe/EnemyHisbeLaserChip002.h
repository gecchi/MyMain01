#ifndef ENEMYHISBELASERCHIP002_H_
#define ENEMYHISBELASERCHIP002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

namespace VioletVreath {

class EnemyHisbeLaserChip002 : public VvEnemyActor<GgafLib::RefractionLaserChip> {

public:
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader_;
    GgafLib::DefaultScene* pFeatureScene_;
public:
    EnemyHisbeLaserChip002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onRefractionInto(int prm_num_refraction) override;

    void onRefractionOutOf(int prm_num_refraction) override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~EnemyHisbeLaserChip002();

};

}
#endif /*ENEMYHISBELASERCHIP002_H_*/

