#include "EnemyGeria.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyGeria::EnemyGeria(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Geria", STATUS(EnemyGeria)) {
    _class_name = "EnemyGeria";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    iMovePatternNo_ = 0;
    max_shots_ = 1;
    shot_num_ = 0;
    can_Shot_ = false;
    do_Shot_ = false;
    velo_mv_begin_ = 0;
    frame_when_shot_ = 0;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_SHOT_001");     //発射
    pAFader_ = NEW GgafDxAlphaFader(this);
    useProgress(PROG_BANPEI);
    migration_length_ = PX_C(10000);
    mvd_ = 0;
}

void EnemyGeria::onCreateModel() {
}

void EnemyGeria::initialize() {
    setHitAble(false);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 45000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Z, -7000);
}

void EnemyGeria::onActive() {
    getStatus()->reset();
    setHitAble(true);
    do_Shot_ = false;
    can_Shot_ = true;
    shot_num_ = 0;
    frame_when_shot_ = 0;
    GgafDxKuroko* pKuroko = getKuroko();
    velo_mv_begin_ = pKuroko->getMvVelo(); //初期移動速度を保存
    pKuroko->setMvVelo(0);
    setRzFaceAng(0);
    setRxFaceAng(0);
    mvd_ = 0;
    getProgress()->reset(PROG_INIT);
}

void EnemyGeria::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            max_shots_ = 1; //移動中に撃つ事ができるショットの最大回数
            shot_num_ = 0;  //撃ったショット回数
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {  //登場
            if (pProg->isJustChanged()) {
                pAFader_->transitionAcceStep(1.0, 0, 0.001);
            }
            if (getAlpha() > 0.8) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE: {  //移動
            if (pProg->isJustChanged()) {
                pKuroko->setMvVelo(velo_mv_begin_);
                do_Shot_ = false;
            }

            if (max_shots_ > shot_num_) {
                MyShip* pM = P_MYSHIP;
                if (pM->_z - 500000 < _z && _z < pM->_z + 500000 &&
                    pM->_y - 500000 < _y && _y < pM->_y + 500000 )
                {
                    frame_when_shot_ = pProg->getFrameInProgress() + RND(1, 20); //ショット撃ち初めまでのラグを設けて散らばらせる
                    do_Shot_ = true;
                }
            }
            if (do_Shot_) {
                if (pProg->getFrameInProgress() == frame_when_shot_) {
                    pProg->change(PROG_FIRE);
                }
            }
            break;
        }
        case PROG_FIRE: {  //発射
            if (pProg->isJustChanged()) {
                pKuroko->setMvVelo(PX_C(3)); //減速
                pKuroko->spinRxFaceAngTo(D180ANG, D_ANG(3), 0, TURN_CLOCKWISE); //予備動作のぐるっと回転
            }

            if (!pKuroko->isTurningFaceAng()) {
                MyShip* pM = P_MYSHIP;
                GgafDxGeometricActor* pLast =
                      UTIL::shotWay001(_x, _y, _z,
                                       pM->_x, pM->_y, pM->_z,
                                       getCommonDepository(Shot004),
                                       PX_C(10),
                                       10000, 100,
                                       3, 5, 0.9,
                                       EnemyGeria::callbackDispatched);
                if (pLast) {
                    shot_num_++;
                    do_Shot_ = false;
                    effectFlush(2); //フラッシュ
                    getSeTx()->play3D(SE_FIRE);
                }
                pProg->change(PROG_MOVE);
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                setHitAble(false);
                pKuroko->setMvVelo(0);
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->getFrameInProgress() == 60) {
                sayonara();
                pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }
//    if (do_Shot_) {
//        if (getActiveFrame() == frame_when_shot_) {
//            pKuroko->setMvVelo(PX_C(3)); //減速
//            pKuroko->spinRxFaceAngTo(D180ANG, D_ANG(3), 0, TURN_CLOCKWISE);
//        } else if (getActiveFrame() == frame_when_shot_ + 60) {
//            MyShip* pM = P_MYSHIP;
//            GgafDxGeometricActor* pLast =
//                  UTIL::shotWay001(_x, _y, _z,
//                                   pM->_x, pM->_y, pM->_z,
//                                   getCommonDepository(Shot004),
//                                   PX_C(10),
//                                   10000, 100,
//                                   3, 5, 0.9,
//                                   EnemyGeria::callbackDispatched);
//            if (pLast) {
//                shot_num_++;
//                do_Shot_ = false;
//                effectFlush(2); //フラッシュ
//                getSeTx()->play3D(SE_FIRE);
//            }
////                GgafDxDrawableActor* pShot = (GgafDxDrawableActor*)pDepo_shot_->dispatch();
////                if (pShot) {
////                    shot_num_++;
////                    pShot->positionAs(this);
////                    pShot->getKuroko()->relateFaceByMvAng(true);
////                    pShot->getKuroko()->setMvAngTwd(P_MYSHIP);
////                    pShot->reset();
////                    do_Shot_ = false;
////                    effectFlush(2); //フラッシュ
////                    getSeTx()->play3D(1);
////                }
//
//            pKuroko->setMvVelo(velo_mv_begin_); //再加速
//        }
//    } else {
//        if (can_Shot_) {
//            MyShip* pM = P_MYSHIP;
//            if (pM->_z - 500000 < _z && _z < pM->_z + 500000 &&
//                pM->_y - 500000 < _y && _y < pM->_y + 500000 &&
//                max_shots_ > shot_num_
//            ) {
//                frame_when_shot_ = getActiveFrame() + RND(0,60) + 1;
//                do_Shot_ = true;
//            }
//        }
//    }
    pAxsMver_->behave();
    pKuroko->behave();
    pAFader_->behave();
    mvd_ += pKuroko->getMvVelo();
}

void EnemyGeria::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
    if (mvd_ > migration_length_) {
        getProgress()->change(PROG_LEAVE);
    }
}

void EnemyGeria::onInactive() {
    setHitAble(false);
}

void EnemyGeria::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

EnemyGeria::~EnemyGeria() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pAxsMver_);
}

void EnemyGeria::callbackDispatched(GgafDxDrawableActor* prm_pDispatched, int prm_dispatched_seq, int prm_set_seq) {
}

