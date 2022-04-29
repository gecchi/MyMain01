#include "EnemyEmus.h"

#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

enum {
    PHASE_INIT       ,
    PHASE_INI_WAIT   ,
    PHASE_HATCH_CLOSE,
    PHASE_HATCH_OPEN ,
    PHASE_FIRE       ,
    PHASE_NOTHING    ,
    PHASE_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
};

EnemyEmus::EnemyEmus(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Emus", StatusReset(EnemyEmus)) {
    _class_name = "EnemyEmus";
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 5*60;
    frame_of_morph_interval_ = 120;

//    pConn_pDepoStore_laser_set = connectToDepositoryManager(
//             "EnemyEmusLaserChip001DepoStore"
//         );
//    pDepoStore_laser_set = (GgafCore::ActorDepositoryStore*)(pConn_pDepoStore_laser_set->peek());
    pDepo_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    ini_wait_ = 0;
}

void EnemyEmus::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyEmus::initialize() {
    setHitAble(true);
    getVecVehicle()->linkFaceAngByMvAng(true);
    getMorpher()->setRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 200000);
    setScale(1000);
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(1000, 1200);
    pScaler->beat(30, 5, 0, 20, -1);
}

void EnemyEmus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
    getPhase()->reset(PHASE_INIT);
}

void EnemyEmus::processBehavior() {
    changeGeoLocal(); //�v�Z�̓��[�J�����W�n
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_INI_WAIT);
            break;
        }
        case PHASE_INI_WAIT: {
            if (pPhase->hasArrivedFrameAt(ini_wait_+1)) {
                pPhase->change(PHASE_HATCH_CLOSE);
            }
            break;
        }
        case PHASE_HATCH_CLOSE: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           0.0f, frame_of_morph_interval_);
                pVecVehicle->setRollFaceAngVelo(0);
            }

            //����
            if (pPhase->getFrame() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pPhase->change(PHASE_HATCH_OPEN);
            }
            break;
        }
        case PHASE_HATCH_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pVecVehicle->setRollFaceAngVelo(3000);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_morph_interval_/2)) {
                //�J�����[�V�����������ȏ�܂œ��B�����Ȃ�
                pPhase->change(PHASE_FIRE);
            }
            break;
        }
        case PHASE_FIRE: {
            if (pPhase->hasJustChanged()) {
                if (!pDepo_) {
                    pDepo_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
                }
            }
            if (pPhase->getFrame() >= (frame_of_morph_interval_/2) + frame_of_open_interval_) {
                pDepo_ = nullptr;
                pPhase->change(PHASE_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    getMorpher()->behave();
    pVecVehicle->behave();
    changeGeoFinal(); //��΍��W�n�ɖ߂�
}

void EnemyEmus::processChangeGeoFinal() {
    //��΍��W�n�ł̑���
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_FIRE: {
            if(pDepo_) {
                GgafDx::FigureActor* pChip = (GgafDx::FigureActor*)pDepo_->dispatch();
                if (pChip) {
                    pChip->setPositionAt(this);
                    pChip->getVecVehicle()->setRzRyMvAng(_rz, _ry); //��΍��W�n�ł̌���
                } else {
                    pDepo_ = nullptr;
                }
            }
            break;
        }
        default:
            break;
    }
}

void EnemyEmus::processJudgement() {

    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
//        (*(_pActor_base->_pFunc_calc_rot_mv_world_matrix))(_pActor_base, _matWorld);
    } else {
        //�y�䂪�Ȃ���Ύ���������
        sayonara();
    }


//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyEmus::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //��j��
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyEmus::onInactive() {
    sayonara();
}

EnemyEmus::~EnemyEmus() {
//    pConn_pDepoStore_laser_set->close();
}
