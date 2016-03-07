#include "EnemyEresShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEresShot001::EnemyEresShot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyEresShot001)) {
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

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(ERESSHOT001_SE_EXPLOSION, "WAVE_EXPLOSION_002");
}

void EnemyEresShot001::initialize() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(veloTop_, veloBottom_);
    pKuroko->linkFaceAngByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyEresShot001::onActive() {
    getStatus()->reset();

    //出現時
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(velo1st_);
    pKuroko->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyEresShot001::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    //方向転換開始
    if (getActiveFrame() == frame_TurnBegin_) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              angVelo_Turn_, 0,
                              TURN_CLOSE_TO, true);
        pKuroko->setMvAcce(iMoveAcce_2nd_);
    }

    //方向転換終了
    if (getActiveFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        pKuroko->setRzRyMvAngVelo(0,0);
        pKuroko->_is_targeting_ang_ry_mv = false;
        pKuroko->_is_targeting_ang_rz_mv = false;
    }

    //behaveUvFlip();
    //座標に反映
    pKuroko->behave();
    //getSeTx()->behave();
}

void EnemyEresShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEresShot001::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(ERESSHOT001_SE_EXPLOSION);
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
