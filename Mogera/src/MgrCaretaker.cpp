#include "MgrCaretaker.h"

#include "actor/camera/MgrCamera.h"
#include "scene/MgrSpacetime.h"

using namespace Mogera;

MgrCaretaker::MgrCaretaker() :
        GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* MgrCaretaker::createSpacetime() {
    //この世の作成のサンプル
    MgrCamera* pCam = NEW MgrCamera("MOGERA_MGRCAMERA");                  //カメラ作成し、
    MgrSpacetime* pSpacetime = NEW MgrSpacetime("MOGERA_SPACETIME", pCam); //この世を生成。
    return pSpacetime;
}

MgrCaretaker::~MgrCaretaker() {
    calmDown();
}

