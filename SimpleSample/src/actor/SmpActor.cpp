#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpCaretaker.h"
#include "scene/SmpSpacetime.h"

using GgafLib::DefaultMeshActor;
using GgafLib::VirtualButton;
using GgafDx::VecVehicle;
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void SmpActor::initialize() {
    //座標設定
    setPosition(0, 0, 0);

    //力車にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //キャラをボタン入力で移動
    static VirtualButton* pVb = ((SmpSpacetime*)pCARETAKER->getSpacetime())->getVB();
    static const coord d = PX_C(2);
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(0, VB_UP)) {
            _z += d; //奥
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= d; //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += d; //右
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= d; //左
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += d; //上
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= d; //下
        }
    }
    getVecVehicle()->behave(); //力車を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
