#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CameraViewPoint::GgafDx9CameraViewPoint() : GgafDx9GeometricActor("ViewPoint", NULL) {

    _class_name = "GgafDx9CameraViewPoint";
}

void GgafDx9CameraViewPoint::initialize() {
    _pMover->setMvVelo(0);
}

void GgafDx9CameraViewPoint::processBehavior() {
}


GgafDx9CameraViewPoint::~GgafDx9CameraViewPoint() {
}
