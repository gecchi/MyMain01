#include "HgrCamera.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

HgrCamera::HgrCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "HgrCamera";
}


HgrCamera::~HgrCamera() {
}
