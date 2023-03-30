#include "HgrCaretaker.h"

#include "actor/camera/HgrCamera.h"
#include "scene/HgrSpacetime.h"

using namespace Hogera;

HgrCaretaker::HgrCaretaker() :
        GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* HgrCaretaker::createSpacetime() {
    //この世の作成のサンプル
    HgrCamera* pCam = NEW HgrCamera("HOGERA_HGRCAMERA");                  //カメラ作成し、
    HgrSpacetime* pSpacetime = NEW HgrSpacetime("HOGERA_SPACETIME", pCam); //この世を生成。
    return pSpacetime;
}

HgrCaretaker::~HgrCaretaker() {
    calmDown();
}

