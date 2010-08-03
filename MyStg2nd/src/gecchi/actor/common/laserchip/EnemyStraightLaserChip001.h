#ifndef ENEMYSTRAIGHTLASERCHIP001_H_
#define ENEMYSTRAIGHTLASERCHIP001_H_
namespace EnemyStg2nd {

class EnemyStraightLaserChip001 : public GgafDx9LibStg::StraightLaserChip {

public:

    EnemyStraightLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyStraightLaserChip001();

};

}
#endif /*ENEMYSTRAIGHTLASERCHIP001_H_*/

