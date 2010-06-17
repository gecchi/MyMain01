#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParentGizmo::MyOptionParentGizmo(const char* prm_name) : DefaultMeshActor(prm_name, "Nothing") {
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
    //��ʊO���薳��
    return 0;
}

bool MyOptionParentGizmo::isOutOfGameSpace() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void MyOptionParentGizmo::drawHitArea() {
    //CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

MyOptionParentGizmo::~MyOptionParentGizmo() {
}
