#include "EnemyHisbe.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectLaserRefraction001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hisbe/EnemyHisbeLaserChip002.h"

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

EnemyHisbe::EnemyHisbe(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Hisbe", StatusReset(EnemyHisbe)) {
        //VvEnemyActor<CubeMapMorphMeshActor>(prm_name, "HisbeCM", StatusReset(EnemyHisbe)) {
    _class_name = "EnemyHisbe";
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;

//    //���t���N�V����------>
//    GgafCore::ActorDepository* pDepoEffect = NEW GgafCore::ActorDepository("HisbeLaser");
//    EffectLaserRefraction001* pEffect;
//    for (int i = 0; i < 100; i++) {
//        std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
//        pEffect = NEW EffectLaserRefraction001(name.c_str());
//        pDepoEffect->put(pEffect);
//    }
//    appendGroupChild(pDepoEffect);
//
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(100, 1); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyHisbeLaserChip002["+XTOS(i)+"]";
//        EnemyHisbeLaserChip002* pChip = NEW EnemyHisbeLaserChip002(name.c_str());
//        int num_refraction = pChip->pVehicleLeader_->getPointNum();
//        pChip->config(num_refraction, 1, 1, false, pDepoEffect);
//        pLaserChipDepo_->put(pChip);
//    }
//    appendGroupChild(pLaserChipDepo_);
//    //<---------------------

//    //�z�[�~���O------>
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(300, 1); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 300; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyHisbeLaserChip001["+XTOS(i)+"]";
//        EnemyHisbeLaserChip001* pChip = NEW EnemyHisbeLaserChip001(name.c_str());
//        pChip->_is_fix_begin_pos = false;
//        pLaserChipDepo_->appendChild(pChip);
//    }
//    appendGroupChild(pLaserChipDepo_);
//    //<---------------------

//    //��------>
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(100, 1); //Hisbe�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyHisbeLaserChip003["+XTOS(i)+"]";
//        EnemyHisbeLaserChip003* pChip = NEW EnemyHisbeLaserChip003(name.c_str());
//        pLaserChipDepo_->appendChild(pChip);
//    }
//    appendGroupChild(pLaserChipDepo_);
//    //<---------------------


    //�z�[�~���O(���|�W�g��)------>
    pConn_pDepoStore_laser_set = connectToDepositoryManager("EnemyHisbeLaserChip001DepoStore");
    pLaserChipDepo_ = nullptr;
    //<---------------------

    //���t���N�V����(���|�W�g��)------>
//    pConn_pDepoStore_laser_set = connectToDepositoryManager("EnemyHisbeLaserChip002DepoStore");
//    pLaserChipDepo_ = nullptr;
    //<---------------------

    //���ʂ̃��[�U�[


    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

}

void EnemyHisbe::onCreateModel() {
}

void EnemyHisbe::initialize() {
//    getVecVehicle()->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, 40000);

//    if (pConn_pDepoStore_laser_set->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_pDepoStore_laser_set�́A���V"<<NODE_INFO<<"����Ă��G�w���I")
//        getPlatformScene()->bringSceneMediator()->appendGroupChild(
//                pConn_pDepoStore_laser_set->peek()->extract()
//                );
//    }
}

void EnemyHisbe::onActive() {
    getStatus()->reset();
    getMorpher()->reset();
    getPhase()->reset(PHASE_WAIT);
}

void EnemyHisbe::processBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_WAIT: {
            if (pLaserChipDepo_) {
                if (pLaserChipDepo_->_num_chip_active == 0) {
                    pLaserChipDepo_ = nullptr;
                }
            } else {
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
            if (pPhase->hasJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pConn_pDepoStore_laser_set->peek()->dispatch()); //���[�U�[�Z�b�g��{�؂�܂��B
            }
            if (pLaserChipDepo_) {
                LaserChip* pLaser = pLaserChipDepo_->dispatch();
                if (pLaser) {
                    pLaser->setPositionAt(this);
                    pLaser->setFaceAngAs(this); //���[�U�[�̃X�v���C����RELATIVE_COORD_DIRECTION�̂��ߌ����ݒ肪�K�v�B
                    if (pLaser->getInfrontChip() == nullptr) {
                        getSeTransmitter()->play3D(SE_FIRE);
                    }
                } else {
                    pPhase->changeNext();
                }
            } else {
                //�؂��Ȃ������I
                pPhase->changeNext();
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
    getVecVehicle()->behave();
    getMorpher()->behave();
    getSeTransmitter()->behave();
}

void EnemyHisbe::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbe::onHit(const GgafCore::Actor* prm_pOtherActor) {
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

void EnemyHisbe::onInactive() {
    //sayonara();
}

EnemyHisbe::~EnemyHisbe() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    pConn_pDepoStore_laser_set->close();
    //pConn_pRefractionEffectDepository_->close();
}
