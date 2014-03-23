#include "stdafx.h"
#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void SmpActor::initialize() {
    //座標設定
    position(0, 0, 0); //(0,0,0) は画面の中心
    //黒衣にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    getKuroko()->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
