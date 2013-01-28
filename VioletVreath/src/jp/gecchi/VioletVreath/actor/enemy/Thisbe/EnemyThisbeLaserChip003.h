#ifndef ENEMYTHISBELASERCHIP003_H_
#define ENEMYTHISBELASERCHIP003_H_
namespace VioletVreath {

class EnemyThisbeLaserChip003 : public GgafLib::WateringLaserChip {

public:
    GgafLib::SplineManufactureConnection* pSplManufCon_;
    GgafLib::SplineSequence* pSplSeq_;
    int sp_index_;

public:
    EnemyThisbeLaserChip003(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;
    void processSettlementBehavior() override;
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyThisbeLaserChip003();

};

}
#endif /*ENEMYTHISBELASERCHIP003_H_*/

