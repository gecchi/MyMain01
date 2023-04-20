#include "EnemyErelmanCore003.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_ENTRY ,
    PHASE_WAIT01 ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyErelmanCore003::EnemyErelmanCore003(const char* prm_name, EnemyErelmanController* prm_pController) :
        EnemyErelmanCore(prm_name, prm_pController) {
    _class_name = "EnemyErelmanCore003";
}

void EnemyErelmanCore003::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
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
                pAlphaFader->transitionLinearUntil(0.5, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_WAIT01: {
            if (pPhase->hasJustChanged()) {
                //pLocoVehicle->turnFaceAng(AXIS_X, D_ANG(90), D_ANG(0.5));
                pLocoVehicle->setRollPitchYawFaceAngVelo(D_ANG(0.00717), D_ANG(0.0031), D_ANG(0.0057));
            }
            if (pPhase->hasArrivedFrameAt(10*60*60)) {
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
                pPhase->changeNothing(); //‚¨‚µ‚Ü‚¢I
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pLocoVehicle->behave();
}

EnemyErelmanCore003::~EnemyErelmanCore003() {
}
