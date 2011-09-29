#ifndef ENEMYASTRAEALASERCHIP002_H_
#define ENEMYASTRAEALASERCHIP002_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip002 : public GgafLib::RefractionLaserChip {


public:
    /** 反射時エフェクトデポジトリへの接続 */
    DepositoryConnection* _pCon_RefractionEffectDepository;


    EnemyAstraeaLaserChip002(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    void onActive() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onRefractionBegin(int prm_num_refraction) override;

    void onRefractionFinish(int prm_num_refraction) override;


    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyAstraeaLaserChip002();

};

}
#endif /*ENEMYASTRAEALASERCHIP002_H_*/

