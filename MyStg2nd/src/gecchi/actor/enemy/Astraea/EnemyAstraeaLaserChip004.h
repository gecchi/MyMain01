#ifndef ENEMYASTRAEALASERCHIP004_H_
#define ENEMYASTRAEALASERCHIP004_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip004 : public GgafDx9LibStg::HomingLaserChip {

public:

    GgafDx9LibStg::SplineManufactureConnection* _pSplManufCon;
    GgafDx9LibStg::SplineSequence* _pSplSeq;
    EnemyAstraeaLaserChip004(const char* prm_name);

    void initialize() override;

    void onActive() override;
    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyAstraeaLaserChip004();

};

}
#endif /*ENEMYASTRAEALASERCHIP004_H_*/

