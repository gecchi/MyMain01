#include "EnemyEresShot001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    ERESSHOT001_SE_EXPLOSION,
};

EnemyEresShot001::EnemyEresShot001(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "myvic", StatusReset(EnemyEresShot001)) {
    _class_name = "EnemyEresShot001";
    inactivateTree();

    /** 出現時の初速 */
    velo1st_ = 13000;
    /** 出現時の加速度（負で遅くなる） */
    iMoveAcce_1st_ = -150;
    /** 自身が出現してから、自機の方向に方向転換を開始するフレーム */
    frame_TurnBegin_ = 60;
    /** 移動速度上限 */
    veloTop_ = 30000;
    /** 最低保証移動速度 */
    veloBottom_ = 0;
    /** 方向転換に費やすことができるフレーム数 */
    frame_TurnInterval_ = 400;
    /** 方向転換中の角速度アングル値(正の値) */
    angVelo_Turn_ = 7000;
    /** 方向転換を開始（frame_TurnBegin_）から再設定される加速度 */
    iMoveAcce_2nd_ = 100;

    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(ERESSHOT001_SE_EXPLOSION, "SE_EXPLOSION_002");
}

void EnemyEresShot001::initialize() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->forceMvVeloRange(veloTop_, veloBottom_);
    pLocusVehicle->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
    setHitAble(true);
}

void EnemyEresShot001::onActive() {
    getStatus()->reset();

    //出現時
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvVelo(velo1st_);
    pLocusVehicle->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyEresShot001::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    //方向転換開始
    if (getActiveFrame() == frame_TurnBegin_) {
        pLocusVehicle->turnMvAngTwd(pMYSHIP,
                              angVelo_Turn_, 0,
                              TURN_CLOSE_TO, true);
        pLocusVehicle->setMvAcce(iMoveAcce_2nd_);
    }

    //方向転換終了
    if (getActiveFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        pLocusVehicle->setRzRyMvAngVelo(0,0);
        pLocusVehicle->_is_targeting_ry_mv = false;
        pLocusVehicle->_is_targeting_rz_mv = false;
    }

    //behaveUvFlip();
    //座標に反映
    pLocusVehicle->behave();
    //getSeXmtr()->behave();
}

void EnemyEresShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEresShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(ERESSHOT001_SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyEresShot001::onInactive() {
    sayonara();
}

EnemyEresShot001::~EnemyEresShot001() {
}
