#ifndef MYBUNSHIN_H_
#define MYBUNSHIN_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

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
    struct AimPoint {
        /** 目標1 */
        coord target01_x;
        coord target01_y;
        coord target01_z;
        /** 目標2 */
        coord target02_x;
        coord target02_y;
        coord target02_z;
        bool is_enable_target02;
    };
    AimPoint pass_p_[10];
    int pass_p_seq_;
    AimPoint* getAimPoint() {
        pass_p_seq_++;
        if (pass_p_seq_ >= 10) {
            pass_p_seq_ = 0;
        }
        pass_p_[pass_p_seq_].is_enable_target02 = false;
        return &(pass_p_[pass_p_seq_]);
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

