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
    //��ʊO���薳��
    return 0;
}

bool MyOptionControllerGizmo::isOutOfUniverse() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void MyOptionControllerGizmo::drawHitArea() {
    //ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}

MyOptionControllerGizmo::~MyOptionControllerGizmo() {
}
