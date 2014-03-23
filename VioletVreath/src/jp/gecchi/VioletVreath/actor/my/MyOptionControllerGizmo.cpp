#include "stdafx.h"
#include "MyOptionControllerGizmo.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyOptionControllerGizmo::MyOptionControllerGizmo(const char* prm_name) :
        DefaultMeshActor(prm_name, "Gizmo", nullptr) {
    _class_name = "MyOptionControllerGizmo";
    ptn_no_ = 0;
}

void MyOptionControllerGizmo::initialize() {
    setHitAble(false);
    //setAlpha(0.5);
}

void MyOptionControllerGizmo::onActive() {
}

void MyOptionControllerGizmo::processBehavior() {
    getKuroko()->behave();
}

void MyOptionControllerGizmo::processJudgement() {
}

int MyOptionControllerGizmo::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool MyOptionControllerGizmo::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}

void MyOptionControllerGizmo::drawHitArea() {
    //ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

MyOptionControllerGizmo::~MyOptionControllerGizmo() {
}
