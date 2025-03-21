#include "EnemyTalante.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT    ,
    PHASE_MOVE01_1,
    PHASE_MOVE01_2,
    PHASE_MOVE01_3,
    PHASE_MOVE01_4,
    PHASE_FINISH  ,
    PHASE_BANPEI,
};

EnemyTalante::EnemyTalante(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Talante", StatusReset(EnemyErmione)) {
    _class_name = "EnemyTalante";
    pDepo_shot_ = nullptr;
    Z_ok_ = Y_ok_ = false;
}

void EnemyTalante::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyTalante::initialize() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(5000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyTalante::config(
        GgafCore::ActorDepository* prm_pDepo_shot
        ) {
    pDepo_shot_ = prm_pDepo_shot;
}

void EnemyTalante::onActive() {
    getStatus()->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvAcce(0);
    pLocusVehicle->setMvVelo(4000);
    pLocusVehicle->forceMvVeloRange(50000);
    getPhase()->reset(PHASE_INIT);
}

void EnemyTalante::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }

        case PHASE_MOVE01_1: {
            //ちょっとそのまま真っ直ぐ進む
            if (pPhase->hasJustChanged()) {
            }
            if (pPhase->getFrame() > 60) {
                pPhase->changeNext(); //次の動きへ
            }
            break;
        }

        case PHASE_MOVE01_2: {
            if (pPhase->hasJustChanged()) {
            }
            if (Z_ok_ == false && pMyShip->_z - PX_C(5) <= _z && _z <= pMyShip->_z + PX_C(5)) {
                //Z座標揃った
                Z_ok_ = true;
                pLocusVehicle->addMvVelo(2000);
                if (pMyShip->_y <= _y) {
                    //真下へ折れる
                    pLocusVehicle->turnRzRyMvAngTo(D270ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //真上へ折れる
                    pLocusVehicle->turnRzRyMvAngTo(D90ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_y - PX_C(5) <= _y && _y <= pMyShip->_y + PX_C(5)) {
                //Y座標揃った
                Y_ok_ = true;
                pLocusVehicle->addMvVelo(2000);
                if (pMyShip->_z <= _z) {
                    //奥の自機の方向折れる
                    pLocusVehicle->turnRzRyMvAngTo(D0ANG, D90ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //手前の自機の方向折れる
                    pLocusVehicle->turnRzRyMvAngTo(D0ANG, D270ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (pLocusVehicle->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z座標Y座標揃ったら次の動きへ
                    pPhase->changeNext();
                } else if (pPhase->getFrame() >= 480) {
                    //Z座標Y座標揃わずとも一定時間で次の動きへ
                    pPhase->changeNext();
                }
            }
            break;
        }

        case PHASE_MOVE01_3: {
            if (pPhase->hasJustChanged()) {
                //X軸方向に動く
                if (pMyShip->_x <= _x) {
                    //左へ折れる
                    pLocusVehicle->turnRzRyMvAngTo(D180ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //右へ折れる
                    pLocusVehicle->turnRzRyMvAngTo(D0ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (pLocusVehicle->isTurningMvAng() == false) {
                pPhase->changeNext(); //次の動きへ
            }
            break;
        }

        case PHASE_MOVE01_4: {
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->setMvAcce(300);//加速開始
            }
            break;
        }

    }
    pLocusVehicle->behave();

    //getSeXmtr()->behave();
}

void EnemyTalante::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyTalante::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    if (getActiveFrame() < 30 && (prm_pOppHitChecker->_kind & KIND_CHIKEI)) {
         //出現30フレーム以内でヒット相手が地形ならば無視（出現即地形による破壊されを回避）
         return;
    }
    VvEnemyActor<DefaultMassMeshActor>::onHit(prm_pThisHitChecker, prm_pOppHitChecker);
}

void EnemyTalante::onInactive() {
}

EnemyTalante::~EnemyTalante() {
}


