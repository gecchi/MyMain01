#include "EnemyRatislaviaEye.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EffectRatislaviaEye001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEyeStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_MOVE ,
    PROG_OPEN ,
    PROG_TURN ,
    PROG_FIRE_BEGIN,
    PROG_IN_FIRE   ,
    PROG_FIRE_END  ,
    PROG_CLOSE     ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyRatislaviaEye::EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "RatislaviaEye_1", StatusReset(EnemyRatislaviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "HaliaCM_1") {
    _class_name = "EnemyRatislaviaEye";
    setScaleR(0.3*10);
    pRatislavia_ = prm_pRatislavia;
    setPositionAt(pRatislavia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyRatislaviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::string name = "LaserChip("+ XTOS(i) + ")";
        pChip = NEW EnemyRatislaviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    appendGroupChild(pLaserChipDepo_);

    pEffect_ = NEW EffectRatislaviaEye001("EffectRatislaviaEye001");
    pEffect_->inactivate();
    appendGroupChild(pEffect_);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    is_wake_ = false;
}

void EnemyRatislaviaEye::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyRatislaviaEye::initialize() {
    setHitAble(true);
    getVecDriver()->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 200000);
}

void EnemyRatislaviaEye::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);
    getProgress()->reset(PROG_MOVE);
    setPositionAt(pRatislavia_);
    setFaceAngAs(pRatislavia_);
    getVecDriver()->setRzRyMvAngVelo(pRatislavia_->getVecDriver()->_angvelo_face[AXIS_Z],
                                  pRatislavia_->getVecDriver()->_angvelo_face[AXIS_Y]);
}

void EnemyRatislaviaEye::processBehavior() {
    setPositionAt(pRatislavia_);
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE: {
            break;
        }
        case PROG_OPEN: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 1.0, 180); //開く
            }
            if (pProg->getFrame() > 240) {
                pProg->changeNext();
            }
            pVecDriver->takeoverMvFrom(pRatislavia_->getVecDriver());
            pVecDriver->setRzRyMvAngVelo(pRatislavia_->getVecDriver()->_angvelo_face[AXIS_Z],
                                      pRatislavia_->getVecDriver()->_angvelo_face[AXIS_Y]);
            break;
        }

        case PROG_TURN: {
            if (pProg->hasJustChanged()) {
                pVecDriver->turnMvAngTwd(pMYSHIP,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (pProg->getFrame() > 240) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if (pProg->hasJustChanged()) {
                //_pVecDriver->turnMvAngTwd(pMYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->setPositionAt(this);
            if (pEffect_->hasJustChangedToInactive()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (pProg->hasJustChanged()) {
                pVecDriver->turnMvAngTwd(pMYSHIP,
                                        10, 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->getInfrontChip() == nullptr) {
                    getSeTransmitter()->play3D(SE_FIRE);
                }
            } else {
                pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_END: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 0.0, 180); //閉じる
                pVecDriver->setRzRyMvAngVelo(pRatislavia_->getVecDriver()->_angvelo_face[AXIS_Z],
                                          pRatislavia_->getVecDriver()->_angvelo_face[AXIS_Y]);
            }
            //硬直
            if (pProg->getFrame() >= 300) {
                pProg->change(PROG_OPEN);
            }
            break;
        }

        default: {
            break;
        }
    }

    pVecDriver->behave();
    getMorpher()->behave();
    getSeTransmitter()->behave();
}

void EnemyRatislaviaEye::processJudgement() {
//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyRatislaviaEye::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
        _TRACE_(FUNC_NAME<<" 上位になげるthrowEventUpperTree(RATISLAVIA_EXPLOSION)");
        throwEventUpperTree(RATISLAVIA_EXPLOSION); //親のEnemyRatislaviaを破壊するイベントを投げる
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyRatislaviaEye::onInactive() {
    //sayonara();
}

void EnemyRatislaviaEye::wake() {
    is_wake_ = true;
    getProgress()->change(PROG_OPEN);
}

EnemyRatislaviaEye::~EnemyRatislaviaEye() {
}
