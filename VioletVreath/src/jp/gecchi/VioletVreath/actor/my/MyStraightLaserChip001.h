#ifndef MYSTRAIGHTLASERCHIP001_H_
#define MYSTRAIGHTLASERCHIP001_H_
namespace VioletVreath {

class MyStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    int default_stamina_;
    MyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onActive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyStraightLaserChip001();

};

}
#endif /*MYSTRAIGHTLASERCHIP001_H_*/

