#ifndef MYBUNSHINCURVELASERCHIP001_H_
#define MYBUNSHINCURVELASERCHIP001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "MyBunshin.h"
#include <fstream>

namespace VioletVreath {

/**
 * 分身レーザーのチップ .
 * WateringLaserChip に ロックオン機能を追加。
 * (WateringLaserChipから分離した)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyBunshinWateringLaserChip001 : public VvMyActor<GgafLib::WateringLaserChip> {
    /** 耐久力初期設定値 */
    int default_stamina_;
    /**
     * 的（ロックオン座標）へレーザーチップを移動させる為の座標を計算
     * @param vTx 目標X座標
     * @param vTy 目標Y座標
     * @param vTz 目標Z座標
     */
    void aimChip(int vTx, int vTy, int vTz);

public:

    /** [r]ロックオンしている場合 true */
    bool is_lockon_;
    /** [r]レーザー発射元 */
    MyBunshin* pOrg_;

    const LockonCursor001_Main* pLockonCursor_;


    /** [r/w]レーザー最大速度（この値を大きくすると、最高速度が早くなる。） */
    static const velo MAX_VELO;
    /** 加速度範囲(0, MAX_ACCE_RENGE) */
    static const acce MAX_ACCE_RENGE;

    /** [r/w]レーザー発射時の初期速度 */
    static const velo INITIAL_VELO;

    /** [r/w]速度に対する加速度の割合（この値を大きくすると、カーブが緩くなる） */
    static const int R_MAX_ACCE;
    /** 最低速度 */
    static const velo MIN_VELO_;

    static int tex_no_;
    static GgafDx::Model* pModel_;

    /** 先端チップのAimInfo */
    MyBunshin::AimInfo* pTipChip_AimInfo_;

    velo sgn_vx0_, sgn_vy0_, sgn_vz0_;
    int inv_cnt_;
public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void setOrg(MyBunshin* prm_pOrg);

    /**
     * レーザーのテクスチャを変える
     * @param prm_tex_no
     */
    static void chengeTex(int prm_tex_no);

    virtual ~MyBunshinWateringLaserChip001();

};

}
#endif /*MYBUNSHINCURVELASERCHIP001_H_*/

