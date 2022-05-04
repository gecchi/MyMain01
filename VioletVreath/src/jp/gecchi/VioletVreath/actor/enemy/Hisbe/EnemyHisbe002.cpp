#include "EnemyHisbe002.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hisbe/EnemyHisbeLaserChip003.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_WAIT,
    PHASE_OPEN,
    PHASE_FIRE,
    PHASE_CLOSE,
    PHASE_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyHisbe002::EnemyHisbe002(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Hisbe002", StatusReset(EnemyHisbe002)) {
        //VvEnemyActor<CubeMapMorphMeshActor>(prm_name, "HisbeCM", StatusReset(EnemyHisbe002)) {

    _class_name = "EnemyHisbe002";
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
    EnemyHisbeLaserChip003* pChip;
    for (int i = 0; i < 240; i++) { //���[�U�[�X�g�b�N
        std::stringstream name;
        name <<  "EnemyHisbeLaserChip003[" << i << "]";
        pChip = NEW EnemyHisbeLaserChip003(name.str().c_str());
        pLaserChipDepo_->put(pChip);
    }
    pLaserChipDepo_->config(240, 1); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
    appendGroupChild(pLaserChipDepo_);

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

}

void EnemyHisbe002::onCreateModel() {
}

void EnemyHisbe002::initialize() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setFaceAngVelo(AXIS_Y, 500);
    pVecVehicle->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 40000);
}

void EnemyHisbe002::onActive() {
    getStatus()->reset();
    getMorpher()->reset();
    getPhase()->reset(PHASE_WAIT);
}

void EnemyHisbe002::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_WAIT: {
            if (pLaserChipDepo_->_num_chip_active == 0) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 1.0, 120);
            }
            if (!getMorpher()->isTransitioning()) {
                //���S�ɊJ������
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                pLaser->setPositionAt(this);
                pLaser->getVecVehicle()->setRzRyMvAng(_rz, _ry);
                                   //���[�U�[�̃X�v���C����RELATIVE_COORD_DIRECTION�̂���MvAng�̐ݒ肪�K�v�B
                if (pLaser->getInfrontChip() == nullptr) {
                    getSeTransmitter()->play3D(SE_FIRE);
                }
            } else {
                pPhase->change(PHASE_CLOSE);
            }
            break;
        }
        case PHASE_CLOSE: { //�P�T�C�N�����[�U�[�ł��؂���
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 0.0, 120); //����
            }
            if (!getMorpher()->isTransitioning()) {
                //���S�ɕ�����
                pPhase->change(PHASE_WAIT);
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

void EnemyHisbe002::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbe002::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyHisbe002::onInactive() {
    //sayonara();
}

EnemyHisbe002::~EnemyHisbe002() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
