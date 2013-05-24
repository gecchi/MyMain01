#ifndef MYOPTIONSTRAIGHTLASERCHIP001_H_
#define MYOPTIONSTRAIGHTLASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

class MyOptionStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    /** 0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int lockon_st_;
    MyOption* pOrg_;
    bool is_lockon_;

    int default_stamina_;

public:
    MyOptionStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOptionStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

