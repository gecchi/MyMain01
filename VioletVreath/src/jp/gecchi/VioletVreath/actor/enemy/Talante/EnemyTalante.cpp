#include "EnemyTalante.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTalante::EnemyTalante(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Talante", STATUS(EnemyTalante)) {
    _class_name = "EnemyTalante";
    pDepo_shot_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    Z_ok_ = Y_ok_ = false;
    useProgress(PROG_BANPEI);
}

void EnemyTalante::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyTalante::initialize() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(5000);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyTalante::config(
        GgafCore::GgafActorDepository* prm_pDepo_shot
        ) {
    pDepo_shot_ = prm_pDepo_shot;
}

void EnemyTalante::onActive() {
    getStatus()->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvAcce(0);
    pKuroko->setMvVelo(4000);
    pKuroko->forceMvVeloRange(50000);
    getProgress()->reset(PROG_INIT);
}

void EnemyTalante::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }

        case PROG_MOVE01_1: {
            //ちょっとそのまま真っ直ぐ進む
            if (pProg->isJustChanged()) {
            }
            if (pProg->getFrame() > 60) {
                pProg->changeNext(); //次の動きへ
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (pProg->isJustChanged()) {
            }
            if (Z_ok_ == false && pMyShip->_z - PX_C(5) <= _z && _z <= pMyShip->_z + PX_C(5)) {
                //Z座標揃った
                Z_ok_ = true;
                pKuroko->addMvVelo(2000);
                if (pMyShip->_y <= _y) {
                    //真下へ折れる
                    pKuroko->turnRzRyMvAngTo(D270ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //真上へ折れる
                    pKuroko->turnRzRyMvAngTo(D90ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_y - PX_C(5) <= _y && _y <= pMyShip->_y + PX_C(5)) {
                //Y座標揃った
                Y_ok_ = true;
                pKuroko->addMvVelo(2000);
                if (pMyShip->_z <= _z) {
                    //奥の自機の方向折れる
                    pKuroko->turnRzRyMvAngTo(D0ANG, D90ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //手前の自機の方向折れる
                    pKuroko->turnRzRyMvAngTo(D0ANG, D270ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (pKuroko->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z座標Y座標揃ったら次の動きへ
                    pProg->changeNext();
                } else if (pProg->getFrame() >= 480) {
                    //Z座標Y座標揃わずとも一定時間で次の動きへ
                    pProg->changeNext();
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (pProg->isJustChanged()) {
                //X軸方向に動く
                if (pMyShip->_x <= _x) {
                    //左へ折れる
                    pKuroko->turnRzRyMvAngTo(D180ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //右へ折れる
                    pKuroko->turnRzRyMvAngTo(D0ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (pKuroko->isTurningMvAng() == false) {
                pProg->changeNext(); //次の動きへ
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (pProg->isJustChanged()) {
                pKuroko->setMvAcce(300);//加速開始
            }
            break;
        }

    }
    pKuroko->behave();

    //getSeTx()->behave();
}

void EnemyTalante::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyTalante::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
         //出現30フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
         return;
    }

    const bool was_destroyed = UTIL::transactEnemyHit(this, pOther);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyTalante::onInactive() {
}

EnemyTalante::~EnemyTalante() {
}


