#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParentGizmo::MyOptionParentGizmo(const char* prm_name) : DefaultMeshActor(prm_name, "Gizmo") {
    _class_name = "MyOptionParentGizmo";

    _ptn_no = 0;
}

void MyOptionParentGizmo::initialize() {
    setHitAble(false);
    setAlpha(0.5);
}

void MyOptionParentGizmo::onActive() {
}

void MyOptionParentGizmo::processBehavior() {
    _pMover->behave();
}

void MyOptionParentGizmo::processJudgement() {
}

int MyOptionParentGizmo::isOffscreen() {
    //画面外判定無し
    return 0;
}

bool MyOptionParentGizmo::isOutOfGameSpace() {
    //ゲーム座標範囲外判定無し
    return false;
}

void MyOptionParentGizmo::drawHitArea() {
    //CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

MyOptionParentGizmo::~MyOptionParentGizmo() {
}
