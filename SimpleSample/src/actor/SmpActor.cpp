#include "SmpActor.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpCaretaker.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpActor::SmpActor(const char* prm_name) :
    GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.modelx が参照される。
}

void SmpActor::initialize() {
    //座標設定
    setPosition(0, 0, 0);
}

void SmpActor::processBehavior() {
    //キャラをボタン入力で移動
    static GgafLib::VirtualButton* pVb = ((SmpSpacetime*)pCARETAKER->getSpacetime())->getVB();
    //移動量(初期カメラ位置で2ピクセル分)
    static const coord d = PX_C(2);
    if (pVb->isPressed(0, VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (pVb->isPressed(0, VB_UP)) {
            _z += d; //奥移動
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _z -= d; //手前移動
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (pVb->isPressed(0, VB_RIGHT)) {
            _x += d; //右移動
        }
        if (pVb->isPressed(0, VB_LEFT)) {
            _x -= d; //左移動
        }
        if (pVb->isPressed(0, VB_UP)) {
            _y += d; //上移動
        }
        if (pVb->isPressed(0, VB_DOWN)) {
            _y -= d; //下移動
        }
    }
    //回転アニメーションする(Z軸回転角度に1度加算する)
    addRzFaceAng(D_ANG(1));
}

SmpActor::~SmpActor() {
}
