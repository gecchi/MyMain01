#include "VvvGod.h"

#include "actor/VvvCamera.h"
#include "scene/VvvUniverse.h"

using namespace VVViewer;

bool VvvGod::is_wm_dropfiles_ = false;
char VvvGod::dropfiles_[2048];

VvvGod::VvvGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* VvvGod::createUniverse() {
    //この世の作成のサンプル
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //カメラ作成し、
    VvvUniverse* pUniverse = new VvvUniverse("SIMPLE_UNIVERSE", pCam); //この世を生成。
    return pUniverse;
}

VvvGod::~VvvGod() {
}

