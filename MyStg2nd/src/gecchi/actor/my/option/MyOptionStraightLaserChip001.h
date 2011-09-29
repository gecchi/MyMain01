#ifndef MYOPTIONSTRAIGHTLASERCHIP001_H_
#define MYOPTIONSTRAIGHTLASERCHIP001_H_
namespace MyStg2nd {

class MyOptionStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    /** 0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int _lockon;
    MyOption* _pOrg;
    bool _isLockon;

    int _default_stamina;
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

