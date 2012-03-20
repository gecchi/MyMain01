#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectMagic001::EffectMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectMagic001", NULL) {
    _class_name = "EffectMagic001";
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.9);
}

void EffectMagic001::initialize() {
//    _pUvFlipper->forcePtnNoRange(0, 63);
    setHitAble(false);

}

void EffectMagic001::onActive() {
    _pKurokoA->setFaceAngVelo(AXIS_X, PX2CO(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, PX2CO(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, PX2CO(7));
}

void EffectMagic001::processBehavior() {
    _pKurokoA->behave();
    _pKurokoB->behave();
}

void EffectMagic001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectMagic001::onInactive() {
}

EffectMagic001::~EffectMagic001() {
}
