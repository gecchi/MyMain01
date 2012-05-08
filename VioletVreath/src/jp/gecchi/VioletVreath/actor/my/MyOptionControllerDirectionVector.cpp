#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyOptionControllerDirectionVector::MyOptionControllerDirectionVector(const char* prm_name) :
        DefaultMeshActor(prm_name, "Nothing", NULL) {
    _class_name = "MyOptionControllerDirectionVector";

    ptn_no_ = 0;
}

void MyOptionControllerDirectionVector::initialize() {
    setAlpha(0.3);
    setHitAble(false);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void MyOptionControllerDirectionVector::onActive() {
}

void MyOptionControllerDirectionVector::processBehavior() {
    _pKurokoA->behave();
}

void MyOptionControllerDirectionVector::processJudgement() {
}

void MyOptionControllerDirectionVector::onInactive() {
}

MyOptionControllerDirectionVector::~MyOptionControllerDirectionVector() {
}
