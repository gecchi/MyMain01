#ifndef MYBUNSHINCURVELASERCHIP001_H_
#define MYBUNSHINCURVELASERCHIP001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

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
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    /** [r]ロックオンしている場合 true */
    bool is_lockon_;
    /** [r]0:非ロックオン（はじめから） 1:ロックオン 2:非ロックオン（ロックオン→非ロックオン） */
    int lockon_st_;

    /** [r]レーザー発射元 */
    const MyBunshin* pOrg_;
    /** ロックオンターゲットリストリング */
    const GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pOrg_pLockonCtrler_pRingTarget_;

    /** [r/w]速度範囲（この値を大きくすると、最高速度が早くなる。） */
    static const int MAX_VELO_RENGE;
    /** 加速度範囲(-MAX_ACCE_RENGE, MAX_ACCE_RENGE) */
    static const float MAX_ACCE_RENGE;

    /** [r/w]速度に対する加速度の割合（この値を大きくすると、カーブが緩くなる） */
    static const int R_MAX_ACCE;
    static const double RR_MAX_ACCE;

    static int tex_no_;
    static GgafDxCore::GgafDxModel* pModel_;
    GgafDxCore::GgafDxGeometricActor* pAimTarget_;
public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    /** 発射する */
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

