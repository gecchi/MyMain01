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
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyIrce::onCreateModel() {
    _pModel->setBlinkPower(0.1, 0.9);
    _pModel->_pTexBlinker->forceRange(0.1, 1.0);
    _pModel->_pTexBlinker->beat(120, 60, 0, 60, -1);
}

void EnemyIrce::initialize() {
    setHitAble(true);
    setScale(1000);
    _pKuroko->relateFaceWithMvAng(true);
    _pKuroko->setMvVelo(3000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _x = PX_C(200);
}

void EnemyIrce::onActive() {
    _pStatus->reset();
    iMovePatternNo_ = 0;
}

void EnemyIrce::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKuroko->turnMvAngTwd(P_MYSHIP,
                            50, 0, TURN_CLOSE_TO, true);
    _pKuroko->behave();
    pScaler_->behave();
    //_pSeTx->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
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
