#include "stdafx.h"
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void SmpActor::initialize() {
    //座標設定
    locate(0, 0, 0); //(0,0,0) は画面の中心
    //黒衣AにキャラのZ軸回転の角速度を設定(毎フレーム2度)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    _pKurokoA->behave(); //黒衣Aを活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
