#include "EffectCondensation001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectCondensation001::EffectCondensation001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "8,Lockon001", nullptr) {
    _class_name = "EffectCondensation001";
    inactivate();
    effectBlendOne(); //มZฌ
    defineRotMvWorldMatrix_Billboard(); //r{[hRz๑]
    setHitAble(false); //ฝ่ป่ณต
}

void EffectCondensation001::initialize() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //Ajออ๐O`PT
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //Aj
}

void EffectCondensation001::onActive() {
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    getScaler()->setRange(30000, 1000); //XP[OEออ
    setScale(30000);
    getScaler()->transitionLinearUntil(1000, 30);//XP[OE60F๏โตฤ1000ษkฌ
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //๑]
}

void EffectCondensation001::processBehavior() {
    GgafDxScaler* const pScaler = getScaler();

    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (!pScaler->isTransitioning()) {
        //kฌฎนใABeat
        pScaler->setRange(1000, 2000);
        pScaler->beat(30, 2, 0, 26, -1); //ณภ[v
    }
    getUvFlipper()->behave();
    getKuroko()->behave();
    pScaler->behave();
}

void EffectCondensation001::processJudgement() {
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
}

