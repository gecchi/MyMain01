#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Camera::Camera(const char* prm_name, float prm_rad_fovX, float prm_dep) : DefaultCamera(prm_name, prm_rad_fovX, prm_dep) {
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
