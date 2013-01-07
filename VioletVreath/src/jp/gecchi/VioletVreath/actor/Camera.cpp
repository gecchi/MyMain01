#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "Camera";
}

void Camera::initialize() {
    DefaultCamera::initialize();
}

void Camera::processBehavior() {
    DefaultCamera::processBehavior();
}

Camera::~Camera() {
}
