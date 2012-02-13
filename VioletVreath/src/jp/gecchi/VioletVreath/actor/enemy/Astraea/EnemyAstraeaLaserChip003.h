#ifndef ENEMYASTRAEALASERCHIP003_H_
#define ENEMYASTRAEALASERCHIP003_H_
namespace VioletVreath {

class EnemyAstraeaLaserChip003 : public GgafLib::WateringLaserChip {

public:
    GgafLib::SplineManufactureConnection* _pSplManufCon;
    GgafLib::SplineSequence* _pSplSeq;

    EnemyAstraeaLaserChip003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAstraeaLaserChip003();

};

}
#endif /*ENEMYASTRAEALASERCHIP003_H_*/

