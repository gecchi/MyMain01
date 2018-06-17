#include "EnemyErelmanCore001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_WAIT01 ,
    PROG_LEAVE ,
    PROG_BANPEI,
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
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafDxAlphaFader* pAlphaFader = getAlphaFader();

    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->setRollFaceAngVelo(D_ANG(3));
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }

        case PROG_WAIT01: {
            if (pProg->hasJustChanged()) {
                pKuroko->setRollPitchYawFaceAngVelo(D_ANG(0.027), D_ANG(0.0031), D_ANG(0.0071));
            }
            if (pProg->hasArrivedAt(10*60*60)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //‚¨‚µ‚Ü‚¢I
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pKuroko->behave();
}

EnemyErelmanCore001::~EnemyErelmanCore001() {
}
