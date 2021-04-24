#include "EnemyHalia.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_FIRST_MOVE,
    PROG_MOVE      ,
    PROG_TURN_OPEN ,
    PROG_FIRE_BEGIN,
    PROG_IN_FIRE   ,
    PROG_CLOSE     ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyHalia::EnemyHalia(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "20,Halia_1", StatusReset(EnemyHalia)) {
        //VvEnemyActor<CubeMapMassMorphMeshActor>(prm_name, "1,HaliaCM", StatusReset(EnemyHalia)) {
    _class_name = "EnemyHalia";
    veloTopMv_ = 20000;
    pDriverLeader_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //レーザーストック
        std::string name = "EnemyStraightLaserChip001["+XTOS(i)+"]";
        pChip = NEW EnemyStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    appendGroupChild(pLaserChipDepo_);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    //初期カメラZ位置
    const Camera* const pCam = pGOD->getSpacetime()->getCamera();
    dZ_camera_init_ = -1 * DX_C(pCam->getZOrigin());
}

void EnemyHalia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyHalia::initialize() {
    setHitAble(true);
    getVecDriver()->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHalia::onActive() {
    getStatus()->reset();
    setMorphWeight(0.0);
    getProgress()->reset(PROG_INIT);
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->setRollFaceAngVelo(1000);
    pVecDriver->setMvVelo(0);
    pVecDriver->setMvAcce(0);
}

void EnemyHalia::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {  //登場
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->change(PROG_FIRST_MOVE);
            }
            break;
        }
        case PROG_FIRST_MOVE: { //初回移動
            if (pProg->hasJustChanged()) {
                pVecDriver->setRzRyMvAng(0, 0);
                pVecDriver->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pVecDriver->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pVecDriver->asstMv()->isSliding()) {
                pProg->change(PROG_TURN_OPEN);
            }
            break;
        }
        case PROG_MOVE: {  //２回以降の移動
            if (pProg->hasJustChanged()) {
                pVecDriver->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pVecDriver->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pVecDriver->asstMv()->isSliding()) {
                pProg->change(PROG_TURN_OPEN);
            }
            break;
        }
        case PROG_TURN_OPEN: {
            if (pProg->hasJustChanged()) {
                pVecDriver->turnMvAngTwd(pMYSHIP,
                                      0, 100,
                                      TURN_CLOSE_TO, false);
            }
            if (!pVecDriver->isTurningMvAng()) {
                pVecDriver->turnMvAngTwd(pMYSHIP,
                                      D_ANG(1), 0,
                                      TURN_CLOSE_TO, false);
                getMorpher()->transitionAcceUntil(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
                pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_BEGIN: {
            if (!getMorpher()->isTransitioning()) {
                if ( _x - pMYSHIP->_x > -dZ_camera_init_) {
                    pVecDriver->setMvVelo(PX_C(1)); //ちょっとバック
                    pVecDriver->setRollFaceAngVelo(D_ANG(5));//発射中は速い回転
                    pProg->change(PROG_IN_FIRE);
                } else {
                    //背後からは撃たない。
                    pProg->change(PROG_CLOSE);
                }
            }
            break;
        }
        case PROG_IN_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->getInfrontChip() == nullptr) {
                    getSeTransmitter()->play3D(SE_FIRE);
                }
            } else {
                pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            getMorpher()->transitionLinearUntil(1, 0.0, 60); //閉じる
            pProg->change(PROG_MOVE);
            break;
        }

        default: {
            break;
        }
    }
    pVecDriver->behave();
    getMorpher()->behave();
    getSeTransmitter()->behave();
    getAlphaFader()->behave();
}

void EnemyHalia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHalia::onHit(const GgafCore::Actor* prm_pOtherActor) {
    if (getMorphWeight(1) > 0.3) { //口が空いてたら
        bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊された時(スタミナ <= 0)
            getSeTransmitter()->play3D(SE_EXPLOSION);
            sayonara();
        } else {
            //破壊されなかった時(スタミナ > 0)
            getSeTransmitter()->play3D(SE_DAMAGED);
        }
    } else {
        getSeTransmitter()->play3D(SE_UNDAMAGED);
    }
}

void EnemyHalia::onInactive() {
    //sayonara();
}

EnemyHalia::~EnemyHalia() {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
}
