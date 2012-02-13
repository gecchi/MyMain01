#ifndef MYOPTIONCURVELASERCHIP001_H_
#define MYOPTIONCURVELASERCHIP001_H_
namespace VioletVreath {

/**
 * オプションレーザーのチップ .
 * WateringLaserChip に ロックオン機能を追加。
 * (WateringLaserChipから分離した)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyOptionWateringLaserChip001 : public GgafLib::WateringLaserChip {
    /** 耐久力初期設定値 */
    int _default_stamina;
    /** 加速度範囲( _max_velo_renge / _r_max_acce ) */
    float _max_acce_renge;
    /** チップの動きを計算 */
    void moveChip(int vTx, int vTy, int vTz);

public:
    /** [r]ロックオンしている場合 true */
    bool _isLockon;
    /** [r]0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int _lockon;
    /** [r]レーザー発射元 */
    MyOption* _pOrg;
    /** [r/w]速度範囲（この値を大きくすると、最高速度が早くなる。） */
    int _max_velo_renge;
    /** [r/w]速度に対する加速度の割合（この値を大きくすると、カーブが緩くなる） */
    int _r_max_acce;

    MyOptionWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOptionWateringLaserChip001();

};

}
#endif /*MYOPTIONCURVELASERCHIP001_H_*/

