#include "EnemyIrce.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};

EnemyIrce::EnemyIrce(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Eres", StatusReset(EnemyErmione)) {
    _class_name = "EnemyIrce";
    iMovePatternNo_ = 0;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyIrce::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyIrce::initialize() {
    setHitAble(true);
    setScale(1000);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setMvVelo(3000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _x = PX_C(200);
}

void EnemyIrce::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0;
}

void EnemyIrce::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->turnMvAngTwd(pMYSHIP,
                          50, 0, TURN_CLOSE_TO, true);
    pKuroko->behave();
    getScaler()->behave();
    //getSeTransmitter()->behave();
}


void EnemyIrce::processJudgement() {
//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyIrce::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyIrce::onInactive() {
    sayonara();
}

EnemyIrce::~EnemyIrce() {
}
