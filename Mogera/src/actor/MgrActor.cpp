#include "stdafx.h"
using namespace Mogera;

MgrActor::MgrActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void MgrActor::initialize() {
    //座標設定
    locate(0, 0, 0); //(0,0,0) は画面の中心
    //黒子AにキャラのZ軸回転の角速度を設定(毎フレーム2度)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void MgrActor::processBehavior() {
    _pKurokoA->behave(); //黒子Aを活動させる（Z軸回転する）
}

MgrActor::~MgrActor() {
}
