#ifndef MYOPTIONCURVELASERCHIP001_H_
#define MYOPTIONCURVELASERCHIP001_H_
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

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
    int default_stamina_;
    /** 加速度範囲( max_velo_renge_ / r_max_acce_ ) */
    float max_acce_renge_;
    /** チップの動きを計算 */
    void moveChip(int vTx, int vTy, int vTz);

public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]ロックオンしている場合 true */
    bool is_lockon_;
    /** [r]0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int lockon_st_;
    /** [r]レーザー発射元 */
    MyOption* pOrg_;
    /** [r/w]速度範囲（この値を大きくすると、最高速度が早くなる。） */
    int max_velo_renge_;
    /** [r/w]速度に対する加速度の割合（この値を大きくすると、カーブが緩くなる） */
    int r_max_acce_;
    double rr_max_acce_;
    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;
    static char aaTextureName[3][51];

public:
    MyOptionWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    /**
     * レーザーのテクスチャを変える
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyOptionWateringLaserChip001();

};

}
#endif /*MYOPTIONCURVELASERCHIP001_H_*/

