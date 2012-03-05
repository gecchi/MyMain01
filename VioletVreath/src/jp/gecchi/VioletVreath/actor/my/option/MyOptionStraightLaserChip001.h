#ifndef MYOPTIONSTRAIGHTLASERCHIP001_H_
#define MYOPTIONSTRAIGHTLASERCHIP001_H_
namespace VioletVreath {

class MyOptionStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    /** 0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int lockon_;
    MyOption* pOrg_;
    bool isLockon_;

    int default_stamina_;
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

