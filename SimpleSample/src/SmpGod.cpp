#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpSpacetime.h"

using namespace SimpleSample;

SmpGod::SmpGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafSpacetime* SmpGod::createSpacetime() {
    //この世の作成のサンプル
    SmpCamera* pCam = new SmpCamera("SMP_CAM");                 //カメラ作成し、
    SmpSpacetime* pSpacetime = new SmpSpacetime("SMP_UNIV", pCam); //カメラを引数にこの世を生成。
    return pSpacetime;
}

SmpGod::~SmpGod() {
}

