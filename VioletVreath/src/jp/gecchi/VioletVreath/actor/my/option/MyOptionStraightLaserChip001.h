#ifndef MYOPTIONSTRAIGHTLASERCHIP001_H_
#define MYOPTIONSTRAIGHTLASERCHIP001_H_
namespace VioletVreath {

class MyOptionStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:
    /** 0:�񃍃b�N�I���i�͂��߂���j 1:���b�N�I�� 2:�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j */
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

