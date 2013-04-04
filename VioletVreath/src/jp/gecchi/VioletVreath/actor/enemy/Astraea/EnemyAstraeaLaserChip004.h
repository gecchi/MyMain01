#ifndef ENEMYASTRAEALASERCHIP004_H_
#define ENEMYASTRAEALASERCHIP004_H_
namespace VioletVreath {

class EnemyAstraeaLaserChip004 : public GgafLib::HomingLaserChip {

public:
    GgafLib::SplineManufactureConnection* pSplManufConnection_;
    GgafLib::SplineKurokoStepper* pKurokoStepper_;
//    static GgafDxCore::GgafDxTextureConnection* pTexCon1_;
//    static GgafDxCore::GgafDxTextureConnection* pTexCon2_;

public:
    EnemyAstraeaLaserChip004(const char* prm_name);

    void initialize() override;
    void onCreateModel() override;

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

