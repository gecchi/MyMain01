#include "EnemyEsperiaLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_MOVE_UP,
    PHASE_TURN1,
    PHASE_TURN2,
    PHASE_INTO_MYSHIP,
    PHASE_NOTHING,
    PHASE_BANPEI,
};
enum {
    SE_FIRE,
};

EnemyEsperiaLaserChip001::EnemyEsperiaLaserChip001(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "EsperiaLaserChip001", StatusReset(EnemyEsperiaLaserChip001)) {
    _class_name = "EnemyEsperiaLaserChip001";
    tx1_ = ty1_ = tz1_ = 0;
    tx2_ = ty2_ = tz2_ = 0;
    begin_y_ = 0;
    turn_dy_ = 0;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_FIRE , "SE_ENEMY_FIRE_LASER_001");
}

void EnemyEsperiaLaserChip001::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 20000);
    setHitAble(true, false);
    setScaleR(5.0);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->forceMvVeloRange(PX_C(100));
    pVecVehicle->linkFaceAngByMvAng(true);
}

void EnemyEsperiaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    begin_y_ = _y;
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->stopTurningMvAng();
    if (getInfrontChip() == nullptr) {
        pVecVehicle->setMvAngTwd(tx1_, ty1_, tz1_);
        getPhase()->reset(PHASE_MOVE_UP);
    } else {
        getPhase()->reset(PHASE_NOTHING);
    }
    setCullingDraw(false);
    //次のメンバーは EnemyEsperia 本体側から設定済みが前提
    //turn_dy_;
    //tx1_, ty1_, tz1_;
    //tx2_, ty2_, tz2_;
}

void EnemyEsperiaLaserChip001::processBehaviorHeadChip() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_MOVE_UP: {
            //レーザー上昇
            if (!pVecVehicle->isTurningMvAng()) {

                //補正
                pVecVehicle->turnMvAngTwd(tx1_, ty1_, tz1_,
                                      D_ANG(5), 0,
                                      TURN_CLOSE_TO, false);
            }
            if (_y > begin_y_+turn_dy_ || pPhase->getFrame() > 300) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_TURN1: {
            //自機より少し上の座標で屈折
            if (pPhase->hasJustChanged()) {
                pVecVehicle->setMvVelo(pVecVehicle->_velo_mv/3); //屈折時少しスローダウン
                pVecVehicle->turnMvAngTwd(tx2_, ty2_, tz2_,
                                      D_ANG(10), 0,
                                      TURN_CLOSE_TO, false);
            }
            if (!pVecVehicle->isTurningMvAng() || pPhase->getFrame() > 300) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_TURN2: {
            //屈折補正
            if (pPhase->getFrame() % 8U == 0) {
                pVecVehicle->turnMvAngTwd(tx2_, ty2_, tz2_,
                                      D_ANG(5), 0,
                                      TURN_CLOSE_TO, false);
                pVecVehicle->setMvVelo(pVecVehicle->_velo_mv*2);
            }
            if (pPhase->getFrame() > 60) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_INTO_MYSHIP: {
            if (pPhase->hasJustChanged()) {
                getSeTransmitter()->play3D(SE_FIRE);
            }
            if (pPhase->getFrame() % 16U == 0) {
                pVecVehicle->turnMvAngTwd(tx2_, ty2_, tz2_,
                                      100, 0,
                                      TURN_CLOSE_TO, false);
            }
            if (pPhase->getFrame() > 90) {
                pVecVehicle->stopTurningMvAng();
                pVecVehicle->setRzRyMvAngVelo(0,0);
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_NOTHING: {
            break;
        }
    }
    pVecVehicle->behave();
    getSeTransmitter()->behave();
}

void EnemyEsperiaLaserChip001::processJudgement() {
    HomingLaserChip::processJudgement();
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEsperiaLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyEsperiaLaserChip001::~EnemyEsperiaLaserChip001() {
}

