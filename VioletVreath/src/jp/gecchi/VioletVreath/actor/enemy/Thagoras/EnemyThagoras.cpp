#include "EnemyThagoras.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE01 ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

EnemyThagoras::EnemyThagoras(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Thagoras", StatusReset(EnemyThagoras)) {
    _class_name = "EnemyThagoras";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pVehicleLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    pActor4Sc_ = nullptr;
}

void EnemyThagoras::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyThagoras::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(2000);
    pLocusVehicle->forceMvVeloRange(PX_C(15));
}

void EnemyThagoras::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
    pActor4Sc_ = ((FormationThagoras*)(getFormation()))->pActor4Sc_;
}

void EnemyThagoras::processBehavior() {
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();

    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE01: {
            if (pPhase->hasJustChanged()) {
                pVehicleLeader_->start(RELATIVE_COORD,5);
            }
            pVehicleLeader_->behave();
            if (pVehicleLeader_->isFinished()) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pPhase->hasArrivedFrameAt(60)) {
                sayonara();
                pPhase->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }
    pAlphaFader->behave();
    getLocusVehicle()->behave();
    //鼓動を同期
    _sx = pActor4Sc_->_sx;
    _sy = pActor4Sc_->_sy;
    _sz = pActor4Sc_->_sz;
}

void EnemyThagoras::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyThagoras::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyThagoras::onInactive() {
    sayonara();
}

EnemyThagoras::~EnemyThagoras() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
