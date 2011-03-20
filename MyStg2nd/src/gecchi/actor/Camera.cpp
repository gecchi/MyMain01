#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name,
                      PI * 80.0f / 180.0f,
                      GGAFDX9_PROPERTY(GAME_SPACE_DEPTH)) {
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
