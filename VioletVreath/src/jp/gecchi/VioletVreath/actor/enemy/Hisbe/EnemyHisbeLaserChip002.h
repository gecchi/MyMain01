#ifndef ENEMYHISBELASERCHIP002_H_
#define ENEMYHISBELASERCHIP002_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

namespace VioletVreath {

class EnemyHisbeLaserChip002 : public GgafLib::RefractionLaserChip {

public:
    static frame end_active_frame_;
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    GgafLib::DefaultScene* pScrollingScene_;
public:
    EnemyHisbeLaserChip002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onRefractionInto(int prm_num_refraction) override;

    void onRefractionOutOf(int prm_num_refraction) override;

    void processBehavior() override;

    void processJudgement() override;

    bool isOutOfSpacetime() const override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHisbeLaserChip002();

};

}
#endif /*ENEMYHISBELASERCHIP002_H_*/

