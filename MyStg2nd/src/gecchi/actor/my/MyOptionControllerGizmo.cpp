#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MyOptionControllerGizmo::MyOptionControllerGizmo(const char* prm_name) :
        DefaultMeshActor(prm_name, "Nothing", NULL) {
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
    _pKurokoA->behave();
}

void MyOptionControllerGizmo::processJudgement() {
}

int MyOptionControllerGizmo::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool MyOptionControllerGizmo::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void MyOptionControllerGizmo::drawHitArea() {
    //ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}

MyOptionControllerGizmo::~MyOptionControllerGizmo() {
}
