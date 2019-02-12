#include "VvCamera.h"



using namespace GgafLib;
using namespace VioletVrain;

VvCamera::VvCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VvCamera";
}


VvCamera::~VvCamera() {
}
