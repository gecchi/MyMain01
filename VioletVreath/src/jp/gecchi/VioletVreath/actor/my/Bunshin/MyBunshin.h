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
        coord t1_x, t1_y, t1_z;
        frame _spent_frames_to_t1;
        /** 目標2 */
        coord t2_x, t2_y, t2_z;
        frame _spent_frames_to_t2;
        void setT2(double r, double x1, double y1, double z1, double x2, double y2, double z2) {
            UTIL::getIntersectionSphereAndVec(r, x1, y1, z1, x2, y2, z2,
                                              t2_x,t2_y,t2_z);
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

    void setRadiusPosition(coord prm_radius_place);
    void addRadiusPosition(coord prm_radius_place);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_place, frame prm_spent_frames);

    void setExpanse(angvelo prm_ang_expanse);
    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);
};

}
#endif /*MYBUNSHIN_H_*/

