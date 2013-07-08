#ifndef ENEMYHISBELASERCHIP002_H_
#define ENEMYHISBELASERCHIP002_H_
#include "jp/ggaf/lib/actor/laserchip/RefractionLaserChip.h"

namespace VioletVreath {

class EnemyHisbeLaserChip002 : public GgafLib::RefractionLaserChip {

public:
    static frame end_active_frame_;
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    GgafLib::DefaultScene* pNearestScrollingScene_;
public:
    EnemyHisbeLaserChip002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onRefractionBegin(int prm_num_refraction) override;

    void onRefractionFinish(int prm_num_refraction) override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHisbeLaserChip002();

};

}
#endif /*ENEMYHISBELASERCHIP002_H_*/

