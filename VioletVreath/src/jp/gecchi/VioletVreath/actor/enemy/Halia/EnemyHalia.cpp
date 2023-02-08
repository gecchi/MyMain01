#include "EnemyHalia.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_FIRST_MOVE,
    PHASE_MOVE      ,
    PHASE_TURN_OPEN ,
    PHASE_FIRE_BEGIN,
    PHASE_IN_FIRE   ,
    PHASE_CLOSE     ,
    PHASE_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyHalia::EnemyHalia(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Halia", StatusReset(EnemyHalia)) {
        //VvEnemyActor<CubeMapMassMorphMeshActor>(prm_name, "HaliaCM", StatusReset(EnemyHalia)) {
    _class_name = "EnemyHalia";
    veloTopMv_ = 20000;
    pVehicleLeader_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1); //Halia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
        std::string name = "EnemyStraightLaserChip001["+XTOS(i)+"]";
        pChip = NEW EnemyStraightLaserChip001(name.c_str());
        pChip->setSource(this); //�ʒu��������
        pLaserChipDepo_->put(pChip);
    }
    appendGroupChild(pLaserChipDepo_);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "SE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

    //�����J����Z�ʒu
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
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
    getVecVehicle()->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHalia::onActive() {
    getStatus()->reset();
    setMorphWeight(0.0);
    getPhase()->reset(PHASE_INIT);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setRollFaceAngVelo(1000);
    pVecVehicle->setMvVelo(0);
    pVecVehicle->setMvAcce(0);
}

void EnemyHalia::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {  //�o��
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->change(PHASE_FIRST_MOVE);
            }
            break;
        }
        case PHASE_FIRST_MOVE: { //����ړ�
            if (pPhase->hasJustChanged()) {
                pVecVehicle->setRzRyMvAng(0, 0);
                pVecVehicle->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pVecVehicle->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pVecVehicle->asstMv()->isSliding()) {
                pPhase->change(PHASE_TURN_OPEN);
            }
            break;
        }
        case PHASE_MOVE: {  //�Q��ȍ~�̈ړ�
            if (pPhase->hasJustChanged()) {
                pVecVehicle->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pVecVehicle->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pVecVehicle->asstMv()->isSliding()) {
                pPhase->change(PHASE_TURN_OPEN);
            }
            break;
        }
        case PHASE_TURN_OPEN: {
            if (pPhase->hasJustChanged()) {
                pVecVehicle->turnMvAngTwd(pMYSHIP,
                                      0, 100,
                                      TURN_CLOSE_TO, false);
            }
            if (!pVecVehicle->isTurningMvAng()) {
                pVecVehicle->turnMvAngTwd(pMYSHIP,
                                      D_ANG(1), 0,
                                      TURN_CLOSE_TO, false);
                getMorpher()->transitionAcceUntil(1, 1.0, 0.0, 0.0004); //�J�� 0.0004 �J������
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_FIRE_BEGIN: {
            if (!getMorpher()->isTransitioning()) {
                if ( _x - pMYSHIP->_x > -dZ_camera_init_) {
                    pVecVehicle->setMvVelo(PX_C(1)); //������ƃo�b�N
                    pVecVehicle->setRollFaceAngVelo(D_ANG(5));//���˒��͑�����]
                    pPhase->change(PHASE_IN_FIRE);
                } else {
                    //�w�ォ��͌����Ȃ��B
                    pPhase->change(PHASE_CLOSE);
                }
            }
            break;
        }
        case PHASE_IN_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->getInfrontChip() == nullptr) {
                    getSeTransmitter()->play3D(SE_FIRE);
                }
            } else {
                pPhase->change(PHASE_CLOSE);
            }
            break;
        }
        case PHASE_CLOSE: {
            //�P�T�C�N�����[�U�[�ł��؂���
            getMorpher()->transitionLinearUntil(1, 0.0, 60); //����
            pPhase->change(PHASE_MOVE);
            break;
        }

        default: {
            break;
        }
    }
    pVecVehicle->behave();
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
    if (getMorphWeight(1) > 0.3) { //�����󂢂Ă���
        bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //�j�󂳂ꂽ��(�X�^�~�i <= 0)
            getSeTransmitter()->play3D(SE_EXPLOSION);
            sayonara();
        } else {
            //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
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
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
