#include "MgrGod.h"

#include "actor/MgrCamera.h"
#include "scene/MgrUniverse.h"

using namespace Mogera;

MgrGod::MgrGod() :
        GgafLib::DefaultGod() {
}

GgafCore::GgafUniverse* MgrGod::createUniverse() {
    //この世の作成のサンプル
    MgrCamera* pCam = NEW MgrCamera("MOGERA_CAMERA");                  //カメラ作成し、
    MgrUniverse* pUniverse = NEW MgrUniverse("MOGERA_UNIVERSE", pCam); //この世を生成。
    return pUniverse;
}

MgrGod::~MgrGod() {
}

