#include "stdafx.h"
#include "EnemyIrce.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyIrce::EnemyIrce(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Eres", STATUS(EnemyIrce)) { //8/をいれとかないとユニークにならない
    _class_name = "EnemyIrce";
    pScaler_ = NEW GgafDxScaler(this);
    iMovePatternNo_ = 0;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyIrce::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->forceRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyIrce::initialize() {
    setHitAble(true);
    setScale(1000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->setMvVelo(3000);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _x = PX_C(200);
}

void EnemyIrce::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0;
}

void EnemyIrce::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->turnMvAngTwd(P_MYSHIP,
                          50, 0, TURN_CLOSE_TO, true);
    pKuroko->behave();
    pScaler_->behave();
    //getSeTx()->behave();
}


void EnemyIrce::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyIrce::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyIrce::onInactive() {
    sayonara();
}

EnemyIrce::~EnemyIrce() {
    GGAF_DELETE(pScaler_);
}
