#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultCamera::DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep) : GgafDxCamera(prm_name, prm_rad_fovX, prm_dep) {
    _class_name = "DefaultCamera";
}

DefaultCamera::DefaultCamera(const char* prm_name, double prm_rad_fovX) :
        GgafDxCamera(prm_name, prm_rad_fovX, PROPERTY::GAME_SPACE_DEPTH) {
    _class_name = "DefaultCamera";
}

DefaultCamera::DefaultCamera(const char* prm_name) :
        GgafDxCamera(prm_name, PI * 90.0f / 180.0f, PROPERTY::GAME_SPACE_DEPTH) {
    _class_name = "DefaultCamera";
}


DefaultCamera::~DefaultCamera() {
}
