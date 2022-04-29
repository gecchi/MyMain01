#include "EnemyRatislaviaEye.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EffectRatislaviaEye001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEyeStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_MOVE ,
    PHASE_OPEN ,
    PHASE_TURN ,
    PHASE_FIRE_BEGIN,
    PHASE_IN_FIRE   ,
    PHASE_FIRE_END  ,
    PHASE_CLOSE     ,
    PHASE_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyRatislaviaEye::EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "RatislaviaEye", StatusReset(EnemyRatislaviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "HaliaCM") {
    _class_name = "EnemyRatislaviaEye";
    setScaleR(0.3*10);
    pRatislavia_ = prm_pRatislavia;
    setPositionAt(pRatislavia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1); //Halia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    EnemyRatislaviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //���[�U�[�X�g�b�N
        std::string name = "LaserChip("+ XTOS(i) + ")";
        pChip = NEW EnemyRatislaviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //�ʒu��������
        pLaserChipDepo_->put(pChip);
    }
    appendGroupChild(pLaserChipDepo_);

    pEffect_ = NEW EffectRatislaviaEye001("EffectRatislaviaEye001");
    pEffect_->inactivate();
    appendGroupChild(pEffect_);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
    pSeTx->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

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
    getVecVehicle()->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 200000);
}

void EnemyRatislaviaEye::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);
    getPhase()->reset(PHASE_MOVE);
    setPositionAt(pRatislavia_);
    setFaceAngAs(pRatislavia_);
    getVecVehicle()->setRzRyMvAngVelo(pRatislavia_->getVecVehicle()->_angvelo_face[AXIS_Z],
                                  pRatislavia_->getVecVehicle()->_angvelo_face[AXIS_Y]);
}

void EnemyRatislaviaEye::processBehavior() {
    setPositionAt(pRatislavia_);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_MOVE: {
            break;
        }
        case PHASE_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 1.0, 180); //�J��
            }
            if (pPhase->getFrame() > 240) {
                pPhase->changeNext();
            }
            pVecVehicle->takeoverFrom(pRatislavia_->getVecVehicle());
            pVecVehicle->setRzRyMvAngVelo(pRatislavia_->getVecVehicle()->_angvelo_face[AXIS_Z],
                                      pRatislavia_->getVecVehicle()->_angvelo_face[AXIS_Y]);
            break;
        }

        case PHASE_TURN: {
            if (pPhase->hasJustChanged()) {
                pVecVehicle->turnMvAngTwd(pMYSHIP,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (pPhase->getFrame() > 240) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_FIRE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                //_pVecVehicle->turnMvAngTwd(pMYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->setPositionAt(this);
            if (pEffect_->hasJustChangedToInactive()) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_IN_FIRE: {
            if (pPhase->hasJustChanged()) {
                pVecVehicle->turnMvAngTwd(pMYSHIP,
                                        10, 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->getInfrontChip() == nullptr) {
                    getSeTransmitter()->play3D(SE_FIRE);
                }
            } else {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_FIRE_END: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 0.0, 180); //����
                pVecVehicle->setRzRyMvAngVelo(pRatislavia_->getVecVehicle()->_angvelo_face[AXIS_Z],
                                          pRatislavia_->getVecVehicle()->_angvelo_face[AXIS_Y]);
            }
            //�d��
            if (pPhase->getFrame() >= 300) {
                pPhase->change(PHASE_OPEN);
            }
            break;
        }

        default: {
            break;
        }
    }

    pVecVehicle->behave();
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
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
        _TRACE_(FUNC_NAME<<" ��ʂɂȂ���throwEventUpperTree(RATISLAVIA_EXPLOSION)");
        throwEventUpperTree(RATISLAVIA_EXPLOSION); //�e��EnemyRatislavia��j�󂷂�C�x���g�𓊂���
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyRatislaviaEye::onInactive() {
    //sayonara();
}

void EnemyRatislaviaEye::wake() {
    is_wake_ = true;
    getPhase()->change(PHASE_OPEN);
}

EnemyRatislaviaEye::~EnemyRatislaviaEye() {
}
