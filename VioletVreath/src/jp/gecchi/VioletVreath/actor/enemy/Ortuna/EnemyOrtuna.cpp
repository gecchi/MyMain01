#include "EnemyOrtuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOrtuna::EnemyOrtuna(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ortuna", STATUS(EnemyOrtuna)) {
    _class_name = "EnemyOrtuna";
    pAFader_ = NEW GgafDxAlphaFader(this);
    _sx=_sy=_sz=100;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyOrtuna::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOrtuna::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyOrtuna::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyOrtuna::processBehavior() {
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             positionAs(&entry_pos_);
             setAlpha(0);
             pKuroko->setMvVelo(0);
             pKuroko->relateFaceByMvAng(true);
             pKuroko->setMvAngTwd(&hanging_pos_);
             velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
             pKuroko->setFaceAngVelo(AXIS_X, mv_velo); //ぐるぐる～
             setMorphWeight(0.0);
             UTIL::activateEntryEffectOf(this);
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             if (pProg->hasArrivedAt(60)) {
                 pAFader_->transitionLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: {
             if (pProg->isJustChanged()) {
                 //折り返しポイントへGO!
                 //velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
                 velo mv_velo = PX_C(20);
                 coord d = UTIL::getDistance(this, &hanging_pos_);
                 pKuroko->setMvVelo(mv_velo);//勢いよくポーンと
                 hanging_pos_frames_ = pKuroko->setMvAcceByD(d, PX_C(1));
             }

             pKuroko->setFaceAngVelo(AXIS_X, pKuroko->_velo_mv); //勢いに比例してぐるぐる～

             if (pProg->getFrame() > hanging_pos_frames_) {
                 pKuroko->setMvVelo(PX_C(1));
                 pKuroko->setMvAcce(0);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE02: {
             if (pProg->isJustChanged()) {
                 //方向転換
                 //ゆっくり自機の方へ向かせる
                 pKuroko->turnMvAngTwd(P_MYSHIP,
                                        D_ANG(3), 0, TURN_CLOSE_TO, true);
                 getMorpher()->transitionLinerUntil(MPH_OPEN, 1.0, 60);
             }
             //滞留中
             if (pProg->getFrame() % 16U == 0) {
                 if (pKuroko->isTurningMvAng()) {
                     //ちょくちょく自機を見つめる
                     pKuroko->turnFaceAngTwd(P_MYSHIP,
                                              D_ANG(1), 0, TURN_CLOSE_TO, true);
                 }
             }

             if (pProg->hasArrivedAt(60)) {
                 //自機の方に向いたら敵弾発射！
                 int shot_num = RF_EnemyOrtuna_ShotWay(G_RANK); //弾数、ランク変動
                 velo shot_velo = RF_EnemyOrtuna_ShotMvVelo(G_RANK); //弾速、ランク変動
                 for (int i = 0; i < shot_num; i++) {
                     GgafDxFigureActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //ばらつかせ。activate タイミング上書き！
                         GgafDxKuroko* pShot_pKuroko = pShot->getKuroko();
                         pShot_pKuroko->setRzRyMvAng(_rz, _ry);
                         pShot_pKuroko->setMvVelo(shot_velo);
                         pShot_pKuroko->setMvAcce(100);
                     }
                 }
             }
             if (pProg->hasArrivedAt(60)) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //さよなら～
             if (pProg->isJustChanged()) {
                 pKuroko->setMvVelo(PX_C(4));
                 pKuroko->setMvAcce(100);
             }
             break;
         }

         default: {
             break;
         }
     }

    pKuroko->behave();
    getMorpher()->behave();
    //getSeTx()->behave();
}

void EnemyOrtuna::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyOrtuna::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyOrtuna::onInactive() {
    sayonara();
}

EnemyOrtuna::~EnemyOrtuna() {
    GGAF_DELETE(pAFader_);
}
