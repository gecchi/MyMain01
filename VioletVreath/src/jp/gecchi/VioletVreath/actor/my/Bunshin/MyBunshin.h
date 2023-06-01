#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

namespace VioletVreath {
#define MAX_LASER_CHIP_NUM (85)
#define MAX_AIM_INFO_NUM (MAX_LASER_CHIP_NUM / 2)

#define LASER_KOANYA 0
#define LASER_THUNDER 1

/**
 * 分身 .
 * 階層構造、全て FK で追加
 * MyBunshinBase ＞ MyBunshinController ＞MyBunshin
 * @version 1.00
 * @since 2015/04/17
 * @author Masatoshi Tsuge
 */
class MyBunshin : public VvEffectActor<GgafLib::DefaultMeshSetActor> {

public:
    MyBunshinBase* pBase_;

    MyBunshinController* pBunshinController_;

    /** [r]ショットのデポジトリ */
    GgafCore::ActorDepository* pDepo_MyBunshinShot_;
//    /** [r]スナイプショットのデポジトリ */
//    GgafCore::ActorDepository* pDepo_MySnipeBunshinShot_;
    /** [r]レーザーチップのデポジトリ */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]ロックオンコントローラー */
    MyLockonController* pLockonCtrler_;
    /** [r]魚雷コントローラー */
    MyTorpedoController* pTorpedoCtrler_;

    int _laser_kind;

//    angle rz_local_copy_;
//    bool _is_thunder_lock;
    GgafLib::DefaultGeometricActor* pGeo2_;
public:
    struct AimInfo {
        MyBunshinWateringLaserChip001* pLeaderChip;
        GgafDx::GeometricActor* pTarget;
        /** T1 目標座標 */
        coord t1_x, t1_y, t1_z;
        coord t1_x_prev, t1_y_prev, t1_z_prev;
        coord t1_ahead_x, t1_ahead_y, t1_ahead_z;
        /** T1 へ到達した時点の active_frame が入る。 0 の場合 T1 へ Aim 中 */
        //frame spent_frames_to_t1;
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

    AimInfo pass_p_[MAX_AIM_INFO_NUM];
    int pass_p_seq_;
    AimInfo* getNewAimInfo() {
        pass_p_seq_++;
        if (pass_p_seq_ >= MAX_AIM_INFO_NUM) {
            pass_p_seq_ = 0;
        }
        AimInfo* ap = &(pass_p_[pass_p_seq_]);
        ap->pLeaderChip = nullptr;
        ap->pTarget = nullptr;
        ap->t1_x = 0;
        ap->t1_y = 0;
        ap->t1_z = 0;
        ap->t1_x_prev = 0;
        ap->t1_y_prev = 0;
        ap->t1_z_prev = 0;
        ap->t1_ahead_x = 0;
        ap->t1_ahead_y = 0;
        ap->t1_ahead_z = 0;
        ap->aim_time_out_t1 = 400;
        ap->t2_x = 0;
        ap->t2_y = 0;
        ap->t2_z = 0;
        ap->aim_time_out_t2 = 0;
        return ap;
    }

public:
    MyBunshin(const char* prm_name, MyBunshinController* prm_pBunshinController, MyBunshinBase* prm_pBase);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;


    void processSettlementBehavior() override;

    void processChangeGeoFinal() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~MyBunshin();

    /**
     * フリーモードへ移行時の点火エフェクト .
     */
    void effectFreeModeIgnited();
    /**
     * 点火エフェクト後の発射準備OKエフェクト .
     */
    void effectFreeModeReady();
    /**
     * 発射エフェクト
     */
    void effectFreeModeLaunch();
    /**
     * フリーモードへ一時停止時のエフェクト .
     */
    void effectFreeModePause();

};

}
#endif /*MYBUNSHIN_H_*/

