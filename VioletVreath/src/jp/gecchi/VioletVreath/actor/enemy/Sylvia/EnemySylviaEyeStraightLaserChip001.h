#ifndef ENEMYSYLVIAEYESTRAIGHTLASERCHIP001_H_
#define ENEMYSYLVIAEYESTRAIGHTLASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class EnemySylviaEyeStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    EnemySylviaEyeStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemySylviaEyeStraightLaserChip001();

};

}
#endif /*ENEMYSYLVIAEYESTRAIGHTLASERCHIP001_H_*/

