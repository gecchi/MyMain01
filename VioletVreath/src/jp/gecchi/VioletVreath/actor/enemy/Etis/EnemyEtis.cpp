#include "EnemyEtis.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

EnemyEtis::EnemyEtis(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Etis", StatusReset(EnemyEtis)) {
    _class_name = "EnemyEtis";
    width_x_ = 220*2*LEN_UNIT;
    height_z_ = 220*2*LEN_UNIT;
    depth_y_ = 36*2*LEN_UNIT;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
}

void EnemyEtis::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyEtis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (width_x_ - depth_y_) ; i+= depth_y_) {
        nArea++;
    }
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(nArea);
    for (int i = 0, n = 0; i < width_x_-depth_y_; i += depth_y_, n++) {
        pChecker->setColliAABox(n,
                             i - ((depth_y_/2.0)/1.5)-(width_x_/2.0 - depth_y_/2.0), -((depth_y_/2.0)/1.5), -(height_z_/2.0),
                             i + ((depth_y_/2.0)/1.5)-(width_x_/2.0 - depth_y_/2.0),  ((depth_y_/2.0)/1.5),  (height_z_/2.0),
                             false, false, true );
    }
}

void EnemyEtis::onActive() {
    getStatus()->reset();
    setAlpha(1.0);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setFaceAngVelo(AXIS_Z, D_ANG(1));
    pLocoVehicle->setRzRyMvAng(D0ANG, D180ANG);
    pLocoVehicle->setMvVelo(PX_C(3));
    const coord renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 4;
    const coord renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 4;
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right - 1000;
    _y = RND(-(renge_y/2) , +(renge_y/2));
    _z = RND(-(renge_z/2) , +(renge_z/2));
    setHitAble(true);
}

void EnemyEtis::processBehavior() {
    //座標に反映
    getLocoVehicle()->behave();
}

void EnemyEtis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEtis::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        getSeTransmitter()->play3D(SE_DAMAGED);
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyEtis::onInactive() {
    sayonara();
}

EnemyEtis::~EnemyEtis() {
}

