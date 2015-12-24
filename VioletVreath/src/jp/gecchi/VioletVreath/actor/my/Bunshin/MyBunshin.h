#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"
namespace VioletVreath {



HASHVAL(EVENT_MyBunshin_ChangeGeoFinal);


//class MyBunshin : public GgafLib::DefaultMorphMeshActor {
class MyBunshin : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_FIRE_LASER  ,
        SE_FIRE_SHOT   ,
        SE_FIRE_TORPEDO,
    };
    MyBunshinBase* pBase_;
    /** [r]ショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MyBunshinShot_;
    /** [r]スナイプショットのデポジトリ */
    GgafCore::GgafActorDepository* pDepo_MySnipeBunshinShot_;
    /** [r]レーザーチップのデポジトリ */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]ロックオンコントローラー */
    MyLockonController* pLockonCtrler_;
    /** [r]魚雷コントローラー */
    MyTorpedoController* pTorpedoCtrler_;

    /** [r]拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** [r]フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** [r]カラーリストさん */
    GgafDxCore::GgafDxColorist* pColorist_;
public:
    struct AimInfo {
        frame begining_frame_of_GameScene_;
        MyBunshinWateringLaserChip001* pLeaderChip_;
        GgafDxCore::GgafDxGeometricActor* pTarget;
        /** 目標1 */
        coord t1_x;
        coord t1_y;
        coord t1_z;
        frame _spent_frames_to_t1;
        /** 目標2 */
        coord t2_x;
        coord t2_y;
        coord t2_z;
        frame _spent_frames_to_t2;
        void setT2(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            double vx = x2 - x1;
            double vy = y2 - y1;
            double vz = z2 - z1;

            // 直線の座標(X,Y,Z)は
            //   X = x2 + t*vx;
            //   Y = y2 + t*vy;
            //   Z = z2 + t*vz;
            //である
            //これを球面の式
            //x^2 + y^2 + z^2 = r^2
            //に代入する
            //(x2 + t*vx)^2 + (y2 + t*vy)^2 + (z2 + t*vz)^2 = r^2
            //    t=-(sqrt((-vy^2-vx^2)*z2^2+(2*vy*vz*y2+2*vx*vz*x2)*z2+(-vz^2-vx^2)*y2^2+2*vx*vy*x2*y2+(-vz^2-vy^2)*
            //    x2^2+r^2*vz^2+r^2*vy^2+r^2*vx^2)+vz*z2+vy*y2+vx*x2)/(vz^2+vy^2+vx^2),
            //    t= (sqrt((-vy^2-vx^2)*z2^2+(2*vy*vz*y2+2*vx*vz*x2)*z2+(-vz^2-vx^2)*y2^2+2*vx*vy*x2*y2+(-vz^2-vy^2)*
            //    x2^2+r^2*vz^2+r^2*vy^2+r^2*vx^2)-vz*z2-vy*y2-vx*x2)/(vz^2+vy^2+vx^2)
            double vxvx = vx * vx;
            double vyvy = vy * vy;
            double vzvz = vz * vz;
            double x2x2 = x2 * x2;
            double y2y2 = y2 * y2;
            double z2z2 = z2 * z2;
            double rr = r * r;
            double t = (sqrt((-vyvy-vxvx)*z2z2+(2*vy*vz*y2+2*vx*vz*x2)*z2+(-vzvz-vxvx)*y2y2+2*vx*vy*x2*y2+(-vzvz-vyvy)*
                        x2x2+rr*vzvz+rr*vyvy+rr*vxvx)-vz*z2-vy*y2-vx*x2)/(vzvz+vyvy+vxvx);

            t2_x = x2 + t*vx;
            t2_y = y2 + t*vy;
            t2_z = z2 + t*vz;
        }
    };
    AimInfo pass_p_[20];
    int pass_p_seq_;
    AimInfo* getAimInfo() {
        pass_p_seq_++;
        if (pass_p_seq_ >= 20) {
            pass_p_seq_ = 0;
        }
        AimInfo* ap = &(pass_p_[pass_p_seq_]);
        ap->begining_frame_of_GameScene_ = P_GAME_SCENE->getBehaveingFrame();
        ap->pLeaderChip_ = nullptr;
        ap->pTarget = nullptr;
        ap->t1_x = 0;
        ap->t1_y = 0;
        ap->t1_z = 0;
        ap->_spent_frames_to_t1 = 0;
        ap->t2_x = 0;
        ap->t2_y = 0;
        ap->t2_z = 0;
        ap->_spent_frames_to_t2 = 0;
        return ap;
    }

public:
    MyBunshin(const char* prm_name, MyBunshinBase* prm_pBase);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processChangeGeoFinal() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

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

    void setRadiusPosition(coord prm_radius_position);
    void addRadiusPosition(coord prm_radius_position);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_position, frame prm_spent_frames);

    void setExpanse(angvelo prm_ang_expanse);
    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);
};

}
#endif /*MYBUNSHIN_H_*/

