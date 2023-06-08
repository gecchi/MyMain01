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

