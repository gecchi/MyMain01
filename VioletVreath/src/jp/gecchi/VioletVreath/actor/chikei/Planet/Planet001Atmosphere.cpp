#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Planet001Atmosphere::Planet001Atmosphere(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001Atmosphere", nullptr) {
    _class_name = "Planet001Atmosphere";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-2);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RzBxyzMv); //XYZ軸ビルボード
    drawAnyFar(true); //遠くても表示
}
void Planet001Atmosphere::onCreateModel() {
}

void Planet001Atmosphere::initialize() {
    setAlpha(0.9);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);
}

void Planet001Atmosphere::processBehavior() {
    _pScaler->behave();
    _pKurokoA->behave();
}

Planet001Atmosphere::~Planet001Atmosphere() {
}

