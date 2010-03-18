#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionParentDirectionVector::MyOptionParentDirectionVector(const char* prm_name) : DefaultMeshActor(prm_name, "Gizmo") {
    _class_name = "MyOptionParentDirectionVector";

    _ptn_no = 0;
}

void MyOptionParentDirectionVector::initialize() {
    setHitAble(false);
}

void MyOptionParentDirectionVector::onActive() {
}

void MyOptionParentDirectionVector::processBehavior() {
    _pMover->behave();
}

void MyOptionParentDirectionVector::processJudgement() {
}

int MyOptionParentDirectionVector::isOffscreen() {
    //��ʊO���薳��
    return 0;
}

bool MyOptionParentDirectionVector::isOutOfGameSpace() {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

void MyOptionParentDirectionVector::drawHitArea() {
    //CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

MyOptionParentDirectionVector::~MyOptionParentDirectionVector() {
}
