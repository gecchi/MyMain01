#ifndef ENEMYASTRAEALASERCHIP002_H_
#define ENEMYASTRAEALASERCHIP002_H_
namespace MyStg2nd {

class EnemyAstraeaLaserChip002 : public GgafDx9LibStg::RefractionLaserChip {


public:
    /** 反射時エフェクトディスパッチャーへの接続 */
    DispatcherConnection* _pDispatcherCon_RefractionEffect;


    EnemyAstraeaLaserChip002(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize() override;

    void onActive() override;

    void onRefractionBegin(int prm_num_refraction) override;

    void onRefractionFinish(int prm_num_refraction) override;


    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyAstraeaLaserChip002();

};

}
#endif /*ENEMYASTRAEALASERCHIP002_H_*/

