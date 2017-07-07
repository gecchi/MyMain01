#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"

using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void SmpActor::initialize() {
    //座標設定
    setPosition(0, 0, 0);
    //黒衣にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    getKuroko()->setFaceAngVelo(AXIS_Z, D_ANG(2));
    getKuroko()->asstFaceAng()->twist(AXIS_Y, D_ANG(180), D_ANG(0), -1,
                                      TURN_COUNTERCLOCKWISE, 30,
                                      0.49, 0.51, 0,
                                      true);
}

void SmpActor::processBehavior() {
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
