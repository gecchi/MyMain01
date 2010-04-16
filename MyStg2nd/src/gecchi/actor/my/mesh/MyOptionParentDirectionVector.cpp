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
    setAlpha(0.3);
    setHitAble(false);
}

void MyOptionParentDirectionVector::onActive() {
}

void MyOptionParentDirectionVector::processBehavior() {
    _pMover->behave();
}

void MyOptionParentDirectionVector::processJudgement() {
}

void MyOptionParentDirectionVector::onInactive() {
}

MyOptionParentDirectionVector::~MyOptionParentDirectionVector() {
}
