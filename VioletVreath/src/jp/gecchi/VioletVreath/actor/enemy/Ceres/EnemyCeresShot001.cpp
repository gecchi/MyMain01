#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCeresShot001::EnemyCeresShot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyCeresShot001)) {
    _class_name = "EnemyCeresShot001";
    inactivateTree();

    /** 出現時の初速 */
    iMvVelo_1st_ = 13000;
    /** 出現時の加速度（負で遅くなる） */
    iMoveAcce_1st_ = -150;
    /** 自身が出現してから、自機の方向に方向転換を開始するフレーム */
    frame_TurnBegin_ = 60;
    /** 移動速度上限 */
    iMvVelo_Top_ = 30000;
    /** 最低保証移動速度 */
    iMvVelo_Bottom_ = 0;
    /** 方向転換に費やすことができるフレーム数 */
    frame_TurnInterval_ = 400;
    /** 方向転換中の角速度アングル値(正の値) */
    angVelo_Turn_ = 7000;
    /** 方向転換を開始（frame_TurnBegin_）から再設定される加速度 */
    iMoveAcce_2nd_ = 100;
    _pSeTx->set(CERESSHOT001_SE_EXPLOSION, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
}

void EnemyCeresShot001::initialize() {
    _pKurokoA->forceMvVeloRange(iMvVelo_Top_, iMvVelo_Bottom_);
    _pKurokoA->relateFaceAngWithMvAng(true);

    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyCeresShot001::onActive() {
    _pStatus->reset();

    //出現時
    _pKurokoA->setMvVelo(iMvVelo_1st_);
    _pKurokoA->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyCeresShot001::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //方向転換開始
    if (getActivePartFrame() == frame_TurnBegin_) {

        _pKurokoA->execTurnMvAngSequence(P_MYSHIP,
                                         angVelo_Turn_, 0,
                                         TURN_CLOSE_TO);
        _pKurokoA->setMvAcce(iMoveAcce_2nd_);
    }

    //方向転換終了
    if (getActivePartFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        _pKurokoA->setRzMvAngVelo(0);
        _pKurokoA->setRyMvAngVelo(0);
        _pKurokoA->_mv_ang_ry_target_flg = false;
        _pKurokoA->_mv_ang_rz_target_flg = false;
    }

    //behaveUvFlip();
    //座標に反映
    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyCeresShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyCeresShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発エフェクト
        GgafDxDrawableActor* pExplo = UTIL::activateExplosionEffectOf(this);
        if (pExplo) {
            pExplo->locateWith(this);
            pExplo->_pKurokoA->followMvFrom(_pKurokoA);
        }
        _pSeTx->play3D(CERESSHOT001_SE_EXPLOSION);

        sayonara();
    }
}

void EnemyCeresShot001::onInactive() {
    sayonara();
}

EnemyCeresShot001::~EnemyCeresShot001() {
}
