#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "scene/SmpSpacetime.h"

using GgafLib::DefaultMeshActor;
using GgafLib::VirtualButton;
using GgafDx::Kuroko;
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void SmpActor::initialize() {
    //座標設定
    setPosition(0, 0, 0);

    //黒衣にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    Kuroko* kuroko = getKuroko();
    kuroko->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //キャラをボタン入力で移動
    VirtualButton* vb = pGOD->getVB();
    static const coord d = PX_C(2);
    if (vb->isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb->isPressed(VB_UP)) {
            _z += d; //奥
        }
        if (vb->isPressed(VB_DOWN)) {
            _z -= d; //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb->isPressed(VB_RIGHT)) {
            _x += d; //右
        }
        if (vb->isPressed(VB_LEFT)) {
            _x -= d; //左
        }
        if (vb->isPressed(VB_UP)) {
            _y += d; //上
        }
        if (vb->isPressed(VB_DOWN)) {
            _y -= d; //下
        }
    }
    getKuroko()->behave(); //黒衣を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
