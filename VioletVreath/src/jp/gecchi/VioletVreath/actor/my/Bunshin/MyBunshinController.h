#ifndef MYBUNSHINCONTROLLER_H_
#define MYBUNSHINCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

namespace VioletVreath {

//DECLARE_EVENT_VAL(EVENT_MyBunshin_ChangeGeoFinal);

#define MAX_LASER_CHIP_NUM (85)
#define MAX_AIM_INFO_NUM (MAX_LASER_CHIP_NUM / 2)

#define LASER_KOANYA 0
#define LASER_THUNDER 1
//class MyBunshinController : public VvEffectActor<GgafLib::DefaultMeshSetActor> {
class MyBunshinController : public GgafLib::DefaultGeometricActor {

public:
    MyBunshinBase* pBase_;


    MyBunshin* pBunshin_;
//    /** [r]ショットのデポジトリ */
//    GgafCore::ActorDepository* pDepo_MyBunshinShot_;
//    /** [r]スナイプショットのデポジトリ */
//    GgafCore::ActorDepository* pDepo_MySnipeBunshinShot_;
//    /** [r]レーザーチップのデポジトリ */
//    GgafLib::LaserChipDepository* pLaserChipDepo_;
//    /** [r]ロックオンコントローラー */
//    MyLockonController* pLockonCtrler_;
//    /** [r]魚雷コントローラー */
//    MyTorpedoController* pTorpedoCtrler_;

//    int _laser_kind;

//    angle rz_local_copy_;
//    bool _is_thunder_lock;
//    GgafLib::DefaultGeometricActor* pGeo2_;
public:
    struct AimInfo {
        MyBunshinWateringLaserChip001* pLeaderChip;
        GgafDx::GeometricActor* pTarget;
        /** 目標1 */
        coord t1_x, t1_y, t1_z;
        frame spent_frames_to_t1;
        frame aim_time_out_t1;
        /** 目標2 */
        coord t2_x, t2_y, t2_z;
        frame spent_frames_to_t2;

        void setT2(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            UTIL::getIntersectionSphereAndVec(r, x1, y1, z1, x2, y2, z2,
                                              t2_x,t2_y,t2_z);
        }
    };
    AimInfo pass_p_[MAX_AIM_INFO_NUM];
    int pass_p_seq_;
    AimInfo* getAimInfo() {
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
        ap->spent_frames_to_t1 = 0;
        ap->aim_time_out_t1 = 400;
        ap->t2_x = 0;
        ap->t2_y = 0;
        ap->t2_z = 0;
        ap->spent_frames_to_t2 = 0;
        return ap;
    }

public:
    MyBunshinController(const char* prm_name, MyBunshinBase* prm_pBase);

//    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

//    void processChangeGeoFinal() override;

    void processJudgement() override;

    void onInactive() override;

//    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~MyBunshinController();

    /**
     * フリーモードへ移行時の点火エフェクト .
     */
    void effectFreeModeIgnited();
    /**
     * 点火エフェクト後の発射準備OKエフェクト .
     */
//    void effectFreeModeReady();
    /**
     * 発射エフェクト
     */
//    void effectFreeModeLaunch();
    /**
     * フリーモードへ一時停止時のエフェクト .
     */
    void effectFreeModePause();

    void setRadiusPosition(coord prm_radius_pos);
    void addRadiusPosition(coord prm_radius_pos);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_pos, frame prm_spent_frames);

//    void setExpanse(angvelo prm_ang_expanse);
    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);

//    bool setFaceAngAsMainLockon();
};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

