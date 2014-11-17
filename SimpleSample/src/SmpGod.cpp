#include "SmpGod.h"

#include "actor/SmpCamera.h"
#include "scene/SmpUniverse.h"

using namespace SimpleSample;

SmpGod::SmpGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* SmpGod::createUniverse() {
    //この世の作成のサンプル
    SmpCamera* pCam = new SmpCamera("SMP_CAM");                 //カメラ作成し、
    SmpUniverse* pUniverse = new SmpUniverse("SMP_UNIV", pCam); //カメラを引数にこの世を生成。
    return pUniverse;
}

SmpGod::~SmpGod() {
}

