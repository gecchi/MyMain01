#include "EnemyEmus.h"

#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
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

EnemyEmus::EnemyEmus(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Emus", StatusReset(EnemyEmus)) {
    _class_name = "EnemyEmus";
    is_open_hatch_ = false;
    frame_of_open_interval_  = SEC_F(3);
    frame_of_close_interval_ = SEC_F(5);
    frame_of_morph_interval_ = SEC_F(4);

//    pConn_pDepoStore_laser_set = connectToDepositoryManager(
//             "EnemyEmusLaserChip001DepoStore"
//         );
//    pDepoStore_laser_set = (GgafCore::ActorDepositoryStore*)(pConn_pDepoStore_laser_set->peek());
    pDepo_ = nullptr;
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
    getLocusVehicle()->linkFaceAngByMvAng(true);
    getMorpher()->setRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
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
    changeGeoLocal(); //ŒvŽZ‚Íƒ[ƒJƒ‹À•WŒn
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
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
                pLocusVehicle->setRollFaceAngVelo(0);
            }

            //ŽŸ‚Ö
            if (pPhase->getFrame() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pPhase->change(PHASE_HATCH_OPEN);
            }
            break;
        }
        case PHASE_HATCH_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pLocusVehicle->setRollFaceAngVelo(3000);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_morph_interval_/2)) {
                //ŠJ‚­ƒ‚[ƒVƒ‡ƒ“‚ª”¼•ªˆÈã‚Ü‚Å“ž’B‚µ‚½‚È‚ç
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
    pLocusVehicle->behave();
    changeGeoFinal(); //â‘ÎÀ•WŒn‚É–ß‚·
}

void EnemyEmus::processChangeGeoFinal() {
    //â‘ÎÀ•WŒn‚Å‚Ì‘€ì
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_FIRE: {
            if(pDepo_) {
                GgafDx::FigureActor* pChip = (GgafDx::FigureActor*)pDepo_->dispatch();
                if (pChip) {
                    pChip->setPositionAt(this);
                    pChip->getLocusVehicle()->setRzRyMvAng(_rz, _ry); //â‘ÎÀ•WŒn‚Å‚ÌŒü‚«
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
        //“y‘ä‚ª‚È‚¯‚ê‚ÎŽ©•ª‚àŽ€‚Ê
        sayonara();
    }


//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyEmus::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //”j‰óŽž
        sayonara();
    } else {
        //”ñ”j‰óŽž
    }
}

void EnemyEmus::onInactive() {
    sayonara();
}

EnemyEmus::~EnemyEmus() {
//    pConn_pDepoStore_laser_set->close();
}
