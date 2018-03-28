#include "VvGod.h"

#include "actor/camera/VvCamera.h"
#include "scene/VvSpacetime.h"

using namespace VioletVrain;

VvGod::VvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafSpacetime* VvGod::createSpacetime() {
    //この世の作成のサンプル
    VvCamera* pCam = NEW VvCamera("VIOLETVRAIN_VVCAMERA");                  //カメラ作成し、
    VvSpacetime* pSpacetime = NEW VvSpacetime("VIOLETVRAIN_SPACETIME", pCam); //この世を生成。
    return pSpacetime;
}

VvGod::~VvGod() {
}

