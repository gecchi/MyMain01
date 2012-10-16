#ifndef ENEMYTORUSEYESTRAIGHTLASERCHIP001_H_
#define ENEMYTORUSEYESTRAIGHTLASERCHIP001_H_
namespace VioletVreath {

class EnemyTorusEyeStraightLaserChip001 : public GgafLib::StraightLaserChip {

public:

    EnemyTorusEyeStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyTorusEyeStraightLaserChip001();

};

}
#endif /*ENEMYTORUSEYESTRAIGHTLASERCHIP001_H_*/

