#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultCamera::DefaultCamera(const char* prm_name, float prm_rad_fovX, float prm_dep) : GgafDx9Camera(prm_name, prm_rad_fovX, prm_dep) {
    _class_name = "DefaultCamera";
}

DefaultCamera::~DefaultCamera() {
}
