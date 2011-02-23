#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionControllerDirectionVector::MyOptionControllerDirectionVector(const char* prm_name) : DefaultMeshActor(prm_name, "Nothing") {
    _class_name = "MyOptionControllerDirectionVector";

    _ptn_no = 0;
}

void MyOptionControllerDirectionVector::initialize() {
    setAlpha(0.3);
    setHitAble(false);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
}

void MyOptionControllerDirectionVector::onActive() {
}

void MyOptionControllerDirectionVector::processBehavior() {
    _pKuroko->behave();
}

void MyOptionControllerDirectionVector::processJudgement() {
}

void MyOptionControllerDirectionVector::onInactive() {
}

MyOptionControllerDirectionVector::~MyOptionControllerDirectionVector() {
}
