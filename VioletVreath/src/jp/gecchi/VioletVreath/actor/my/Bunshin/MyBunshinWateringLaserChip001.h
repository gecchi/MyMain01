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
     * @param chk_done true:まだAimさせる必要があるのかチェックする ／ false:チェックしない
     * @return chk_done が true の場合のみ戻り値に意味がある
     *         true：目標に到達したのでもういいよ。あるいは、目標を通り過ぎちゃったのでもういいよ。／false:まだまだAim頑張る
     */
    bool aimChip(int vTx, int vTy, int vTz, bool chk_done = false);

public:

    struct AimInfo {
        MyBunshinWateringLaserChip001* pLeaderChip;
        GgafDx::GeometricActor* pTarget;
        /** T1 目標座標 */
        coord t1_x, t1_y, t1_z;
        coord t1_x_prev, t1_y_prev, t1_z_prev;
        coord t1_ahead_x, t1_ahead_y, t1_ahead_z;
        /** T1 へ到達する見込みの active_frame。 */
        frame aim_time_out_t1;
        /** T2 目標座標 */
        coord t2_x, t2_y, t2_z;
        /** T2 へ到達する見込みの active_frame。*/
        frame aim_time_out_t2;
        /**
         * T1 目標座標設定 .
         * @param x
         * @param y
         * @param z
         */
        void setT1_and_T1Ahead(coord x, coord y, coord z) {
            t1_x_prev = t1_x = t1_ahead_x = x;
            t1_y_prev = t1_y = t1_ahead_y = y;
            t1_z_prev = t1_z = t1_ahead_z = z;
        }
        /**
         * T1 目標座標更新 .
         * @param x
         * @param y
         * @param z
         */
        void updateT1(coord x, coord y, coord z) {
            t1_x_prev = t1_x;
            t1_y_prev = t1_y;
            t1_z_prev = t1_z;
            t1_x = x;
            t1_y = y;
            t1_z = z;
        }
        void setT1Ahead(coord x, coord y, coord z) {
            t1_ahead_x = x;
            t1_ahead_y = y;
            t1_ahead_z = z;
        }
        /**
         * T2 目標座標を、球面とベクトルの延長線との交点に設定 .
         * @param r 球面半径
         * @param x1
         * @param y1
         * @param z1
         * @param x2
         * @param y2
         * @param z2
         */
        void setT2BySphere(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            UTIL::getIntersectionSphereAndVec(r, x1, y1, z1, x2, y2, z2,
                                              t2_x,t2_y,t2_z);
        }
        void setT2(coord x, coord y, coord z) {
            t2_x = x;
            t2_y = y;
            t2_z = z;
        }
    };

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

    /** 現在自身を制御している リーダーチップのAimInfo */
    AimInfo* pLeaderChip_AimInfo_;
    /** 自身の AimInfoインスタンス */
    AimInfo aim_info_;

    /**
      * 新しい状態で AimInfo を取得 .
      * @return 新しい AimInfo
      */
     AimInfo* getNewAimInfo() {
         aim_info_.pLeaderChip = nullptr;
         aim_info_.pTarget = nullptr;
         aim_info_.t1_x = 0;
         aim_info_.t1_y = 0;
         aim_info_.t1_z = 0;
         aim_info_.t1_x_prev = 0;
         aim_info_.t1_y_prev = 0;
         aim_info_.t1_z_prev = 0;
         aim_info_.t1_ahead_x = 0;
         aim_info_.t1_ahead_y = 0;
         aim_info_.t1_ahead_z = 0;
         aim_info_.aim_time_out_t1 = 400;
         aim_info_.t2_x = 0;
         aim_info_.t2_y = 0;
         aim_info_.t2_z = 0;
         aim_info_.aim_time_out_t2 = 0;
         return &aim_info_;
     }

     /**
      * 新しい コピー AimInfo を取得 .
      * @param pOrg
      * @return
      */
     AimInfo* getNewAimInfoCopy(AimInfo* pOrg) {
         aim_info_ = (*pOrg); //コピー
         return &aim_info_;
     }

    velo sgn_vx0_, sgn_vy0_, sgn_vz0_;
    int inv_cnt_;
public:
    MyBunshinWateringLaserChip001(const char* prm_name);

    void initialize() override;

    void onCreateModel() override;

    void onActive() override;

    void onInactive() override;

    void processBehavior() override;

    void processBehavior_Aiming();

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

