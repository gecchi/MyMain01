#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name,
                      PI * 90.0f / 180.0f,
                      CFG_PROPERTY(GAME_SPACE_DEPTH)) {
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
