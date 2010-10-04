#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionControllerGizmo::MyOptionControllerGizmo(const char* prm_name) : DefaultMeshActor(prm_name, "Nothing") {
    _class_name = "MyOptionControllerGizmo";

    _ptn_no = 0;
}

void MyOptionControllerGizmo::initialize() {
    setHitAble(false);
    setAlpha(0.5);
}

void MyOptionControllerGizmo::onActive() {
}

void MyOptionControllerGizmo::processBehavior() {
    _pMover->behave();
}

void MyOptionControllerGizmo::processJudgement() {
}

int MyOptionControllerGizmo::isOffscreen() {
    //��ʊO���薳��
    return 0;
}

bool MyOptionControllerGizmo::isOutOfGameSpace() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void MyOptionControllerGizmo::drawHitArea() {
    //CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

MyOptionControllerGizmo::~MyOptionControllerGizmo() {
}