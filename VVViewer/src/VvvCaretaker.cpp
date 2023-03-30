#include "VvvCaretaker.h"

#include "actor/VvvCamera.h"

using namespace VVViewer;

bool VvvCaretaker::is_wm_dropfiles_ = false;
char VvvCaretaker::dropfiles_[2048];

VvvCaretaker::VvvCaretaker() :
        GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* VvvCaretaker::createSpacetime() {
    //この世の作成のサンプル
    VvvCamera* pCam = new VvvCamera("SIMPLE_CAMERA");                  //カメラ作成し、
    VvvSpacetime* pSpacetime = new VvvSpacetime("SIMPLE_SPACETIME", pCam); //この世を生成。
    return pSpacetime;
}

VvvCaretaker::~VvvCaretaker() {
    calmDown();
}

