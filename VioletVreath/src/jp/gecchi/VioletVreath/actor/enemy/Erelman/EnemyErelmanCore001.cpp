#include "EnemyErelmanCore001.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"




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

EnemyErelmanCore001::EnemyErelmanCore001(const char* prm_name, EnemyErelmanController* prm_pController) :
        EnemyErelmanCore(prm_name, prm_pController) {
    _class_name = "EnemyErelmanCore001";
}

void EnemyErelmanCore001::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();

    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
//            pLocoVehicle->setRollFaceAngVelo(D_ANG(1));
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

        case PHASE_WAIT01: {
            if (pPhase->hasJustChanged()) {
//                pLocoVehicle->setRollPitchYawFaceAngVelo(D_ANG(0.027), D_ANG(0.0031), D_ANG(0.0071));
//                pLocoVehicle->turnFaceAngTwd(0,0,0,D_ANG(2));
                setRzFaceAng(D_ANG(89));
                pLocoVehicle->setRyFaceAngVelo(D_ANG(0.01));
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

EnemyErelmanCore001::~EnemyErelmanCore001() {
}
