#include "stdafx.h"
#include "EnemyEresShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

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
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(veloTop_, veloBottom_);
    pKuroko->relateFaceWithMvAng(true);

    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyEresShot001::onActive() {
    _pStatus->reset();

    //出現時
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(velo1st_);
    pKuroko->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyEresShot001::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    GgafDxKuroko* pKuroko = getKuroko();
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
        pKuroko->_mv_ang_ry_target_flg = false;
        pKuroko->_mv_ang_rz_target_flg = false;
    }

    //behaveUvFlip();
    //座標に反映
    pKuroko->behave();
    //getSeTx()->behave();
}

void EnemyEresShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEresShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        getSeTx()->play3D(ERESSHOT001_SE_EXPLOSION);

        sayonara();
    }
}

void EnemyEresShot001::onInactive() {
    sayonara();
}

EnemyEresShot001::~EnemyEresShot001() {
}
