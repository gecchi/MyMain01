#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraViewPoint::GgafDxCameraViewPoint() : GgafDxGeometricActor("ViewPoint", NULL, NULL) {
    _class_name = "GgafDxCameraViewPoint";
}

void GgafDxCameraViewPoint::initialize() {
    _pKurokoA->setMvVelo(0);
}

void GgafDxCameraViewPoint::processBehavior() {
//    _pKurokoA->behave();
}


GgafDxCameraViewPoint::~GgafDxCameraViewPoint() {
}
