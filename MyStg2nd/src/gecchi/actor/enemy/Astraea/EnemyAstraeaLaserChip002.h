#ifndef ENEMYASTRAEALASERCHIP002_H_
#define ENEMYASTRAEALASERCHIP002_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip002 : public RefractionLaserChip {


public:
    EnemyAstraeaLaserChip002(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize() override;

    void onActive() override;

    void processOnRefraction(int prm_num_refraction) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyAstraeaLaserChip002();

};

}
#endif /*ENEMYASTRAEALASERCHIP002_H_*/

