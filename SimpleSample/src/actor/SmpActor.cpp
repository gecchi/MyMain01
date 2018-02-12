#include "SmpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "scene/SmpSpacetime/SmpWorld.h"

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
    //キャラをボタン入力で移動
    GgafLib::VirtualButton* vb = ((SmpWorld::Mediator*)getMySceneMediator())->getVB();
    if (vb->isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb->isPressed(VB_UP)) {
            _z += PX_C(2); //奥
        }
        if (vb->isPressed(VB_DOWN)) {
            _z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb->isPressed(VB_RIGHT)) {
            _x += PX_C(2); //右
        }
        if (vb->isPressed(VB_LEFT)) {
            _x -= PX_C(2); //左
        }
        if (vb->isPressed(VB_UP)) {
            _y += PX_C(2); //上
        }
        if (vb->isPressed(VB_DOWN)) {
            _y -= PX_C(2); //下
        }
    }
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
