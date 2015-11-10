#ifndef MYBUNSHINCURVELASERCHIP001_H_
#define MYBUNSHINCURVELASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "MyBunshin.h"

namespace VioletVreath {

/**
 * 分身レーザーのチップ .
 * WateringLaserChip に ロックオン機能を追加。
 * (WateringLaserChipから分離した)
 * @version 1.00
 * @since 2010/10/6
 * @author Masatoshi Tsuge
 */
class MyBunshinWateringLaserChip001 : public GgafLib::WateringLaserChip {
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
    enum {
        PROG_AIM_AT_NOTHING,                 /** 何も狙うものが無い */
        PROG_AIM_AT_LOCK_ON_TARGET01,        /** 移動中のメインロックオンを狙って移動 */
        PROG_AIM_AT_TARGET01,                /** 固定の目標1を狙って移動 */
        PROG_AIM_AT_NOTHING_TARGET01_AFTER,  /** 目標1を狙って移動し、到達後の目標2が無い時の移動 */
        PROG_AIM_AT_TARGET02,                /** 固定の目標2を狙って移動 */
        PROG_AIM_AT_NOTHING_TARGET02_AFTER,  /** 目標2を狙って移動し、到達後の目標が無い時の移動 */
        PROG_BANPEI,
    };
    int aim_status_;

    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]ロックオンしている場合 true */
    bool is_lockon_;

    /** [r]レーザー発射元 */
    MyBunshin* pOrg_;
    /** ロックオンターゲットリストリング */
//    const GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pOrg_pLockonCtrler_pRingTarget_;


    const EffectLockon001_Main* pLockon_;


    /** [r/w]速度範囲（この値を大きくすると、最高速度が早くなる。） */
    static const int MAX_VELO_RENGE;
    /** 加速度範囲(-MAX_ACCE_RENGE, MAX_ACCE_RENGE) */
    static const float MAX_ACCE_RENGE;

    /** [r/w]速度に対する加速度の割合（この値を大きくすると、カーブが緩くなる） */
    static const int R_MAX_ACCE;
    static const double RR_MAX_ACCE;

    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;

    MyBunshin::AimPoint* pAimPoint_;

public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

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

