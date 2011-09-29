#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultCamera::DefaultCamera(const char* prm_name, float prm_rad_fovX, float prm_dep) : GgafDxCamera(prm_name, prm_rad_fovX, prm_dep) {
    _class_name = "DefaultCamera";
}

DefaultCamera::~DefaultCamera() {
}
