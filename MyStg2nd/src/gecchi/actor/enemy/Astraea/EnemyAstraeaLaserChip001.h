#ifndef ENEMYASTRAEALASERCHIP001_H_
#define ENEMYASTRAEALASERCHIP001_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip001 : public HomingLaserChip {


public:
    EnemyAstraeaLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehaviorHeadChip();

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyAstraeaLaserChip001();

};

}
#endif /*ENEMYASTRAEALASERCHIP001_H_*/

