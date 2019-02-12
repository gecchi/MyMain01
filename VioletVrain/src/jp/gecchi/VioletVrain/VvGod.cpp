#include "VvGod.h"

#include "jp/gecchi/VioletVrain/actor/camera/VvCamera.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"

using namespace VioletVrain;

VvGod::VvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::Spacetime* VvGod::createSpacetime() {
    VvCamera* pCam = NEW VvCamera("CAMERA");
    VvSpacetime* pSpacetime = NEW VvSpacetime("SPACETIME", pCam);
    return pSpacetime;
}

VvGod::~VvGod() {
}

