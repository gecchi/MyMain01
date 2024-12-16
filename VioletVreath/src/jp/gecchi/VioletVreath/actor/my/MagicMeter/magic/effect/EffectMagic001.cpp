#include "EffectMagic001.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectMagic001::EffectMagic001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectMagic001") {
    _class_name = "EffectMagic001";
    effectBlendOne(); //加算合成するTechnique指定
    useZBufferDrawing(true);        //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
}

void EffectMagic001::initialize() {
    setCullingDraw(false);
//    getUvFlipper()->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectMagic001::onActive() {
    getLocusVehicle()->setRollPitchYawFaceAngVelo(PX_C(3), PX_C(5), PX_C(7));
}

void EffectMagic001::processBehavior() {
    getLocusVehicle()->behave();
}

void EffectMagic001::processJudgement() {
}

void EffectMagic001::onInactive() {
}

EffectMagic001::~EffectMagic001() {
}
