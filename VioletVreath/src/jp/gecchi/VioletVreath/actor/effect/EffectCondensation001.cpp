#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectCondensation001::EffectCondensation001(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "8/Lockon001", NULL) {
    _class_name = "EffectCondensation001";
    inactivateImmed();
    changeEffectTechnique("DestBlendOne"); //มZฌ
    defineRotMvWorldMatrix(GgafDxUtil::setWorldMatrix_RzBxyzMv); //r{[hRz๑]
    setHitAble(false); //ฝ่ป่ณต
}

void EffectCondensation001::initialize() {
    _pUvFlipper->forcePtnRange(0, 3);   //Ajออ๐O`PT
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //Aj

}

void EffectCondensation001::onActive() {
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(30000, 1000); //XP[OEออ
    _pScaler->setScale(30000);
    _pScaler->intoTargetScaleLinerUntil(1000, 30);//XP[OE60F๏โตฤ1000ษkฌ
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //๑]
}

void EffectCondensation001::processBehavior() {
    if (getAlpha() < 1.0) {
        addAlpha(0.05);
    }

    if (_pScaler->_method[0] == NOSCALE) {
        //kฌฎนใABeat
        _pScaler->forceScaleRange(1000, 2000);
        _pScaler->beat(30, 2, 2, -1); //ณภ[v
    }
    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();
}

void EffectCondensation001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectCondensation001::onInactive() {
}

EffectCondensation001::~EffectCondensation001() {
}
