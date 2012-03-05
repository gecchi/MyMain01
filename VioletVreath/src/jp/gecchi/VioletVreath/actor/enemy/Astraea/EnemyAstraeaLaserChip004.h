#ifndef ENEMYASTRAEALASERCHIP004_H_
#define ENEMYASTRAEALASERCHIP004_H_
namespace VioletVreath {

class EnemyAstraeaLaserChip004 : public GgafLib::HomingLaserChip {

public:

    GgafLib::SplineManufactureConnection* pSplManufCon_;
    GgafLib::SplineSequence* pSplSeq_;
    EnemyAstraeaLaserChip004(const char* prm_name);

    void initialize() override;

    void onActive() override;
    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyAstraeaLaserChip004();

};

}
#endif /*ENEMYASTRAEALASERCHIP004_H_*/

