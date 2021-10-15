#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "scene/SmpSpacetime.h"

using GgafLib::DefaultMeshActor;
using GgafLib::VirtualButton;
using GgafDx::VecDriver;
using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void SmpActor::initialize() {
    //座標設定
    setPosition(0, 0, 0);

    //力車にキャラのZ軸回転の角速度を設定(毎フレーム2度)
    VecDriver* pVecDriver = getVecDriver();
    pVecDriver->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void SmpActor::processBehavior() {
    //キャラをボタン入力で移動
    static VirtualButton* pVb = ((SmpSpacetime*)pGOD->getSpacetime())->getVB();
    static const coord d = PX_C(2);
    if (pVb->isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(VB_UP)) {
            _z += d; //奥
        }
        if (pVb->isPressed(VB_DOWN)) {
            _z -= d; //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(VB_RIGHT)) {
            _x += d; //右
        }
        if (pVb->isPressed(VB_LEFT)) {
            _x -= d; //左
        }
        if (pVb->isPressed(VB_UP)) {
            _y += d; //上
        }
        if (pVb->isPressed(VB_DOWN)) {
            _y -= d; //下
        }
    }
    getVecDriver()->behave(); //力車を活動させる（Z軸回転する）
}

SmpActor::~SmpActor() {
}
