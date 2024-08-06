#include "EffectLaserRefraction001.h"

#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001") {
    _class_name = "EffectLaserRefraction001";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
}

void EffectLaserRefraction001::initialize() {
    setHitAble(false);
}

void EffectLaserRefraction001::onActive() {
    //getUvFlipper()->setActivePtnToTop();
    //getUvFlipper()->exec(FLIP_ORDER_LOOP, 1); //パラパラアニメ無し
    setAlpha(0.5);
    setScale(R_SC(6));
    getLocusVehicle()->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
}

void EffectLaserRefraction001::processBehavior() {
    addScale(100);

    //getUvFlipper()->behave();
    getLocusVehicle()->behave();
    getScaler()->behave();
}

void EffectLaserRefraction001::processJudgement() {
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
}
