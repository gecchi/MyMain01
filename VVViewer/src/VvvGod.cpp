#include "VvvGod.h"

#include "actor/VvvCamera.h"

using namespace VVViewer;

bool VvvGod::is_wm_dropfiles_ = false;
char VvvGod::dropfiles_[2048];

VvvGod::VvvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::Spacetime* VvvGod::createSpacetime() {
    //この世の作成のサンプル
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //カメラ作成し、
    VvvSpacetime* pSpacetime = new VvvSpacetime("SIMPLE_SPACETIME", pCam); //この世を生成。
    return pSpacetime;
}

VvvGod::~VvvGod() {
}

