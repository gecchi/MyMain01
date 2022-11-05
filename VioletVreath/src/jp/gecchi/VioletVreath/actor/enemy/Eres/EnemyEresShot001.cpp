#include "EnemyEresShot001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
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

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(ERESSHOT001_SE_EXPLOSION, "SE_EXPLOSION_002");
}

void EnemyEresShot001::initialize() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->forceMvVeloRange(veloTop_, veloBottom_);
    pVecVehicle->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
    setHitAble(true);
}

void EnemyEresShot001::onActive() {
    getStatus()->reset();

    //出現時
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setMvVelo(velo1st_);
    pVecVehicle->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyEresShot001::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    //方向転換開始
    if (getActiveFrame() == frame_TurnBegin_) {
        pVecVehicle->turnMvAngTwd(pMYSHIP,
                              angVelo_Turn_, 0,
                              TURN_CLOSE_TO, true);
        pVecVehicle->setMvAcce(iMoveAcce_2nd_);
    }

    //方向転換終了
    if (getActiveFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        pVecVehicle->setRzRyMvAngVelo(0,0);
        pVecVehicle->_is_targeting_ry_mv = false;
        pVecVehicle->_is_targeting_rz_mv = false;
    }

    //behaveUvFlip();
    //座標に反映
    pVecVehicle->behave();
    //getSeTransmitter()->behave();
}

void EnemyEresShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEresShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(ERESSHOT001_SE_EXPLOSION);
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
