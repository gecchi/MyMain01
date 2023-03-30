#include "VvCaretaker.h"

#include "jp/gecchi/VioletVrain/actor/camera/VvCamera.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"

using namespace VioletVrain;

VvCaretaker::VvCaretaker() :
        GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* VvCaretaker::createSpacetime() {
    VvCamera* pCam = NEW VvCamera("CAMERA");
    VvSpacetime* pSpacetime = NEW VvSpacetime("SPACETIME", pCam);
    return pSpacetime;
}

VvCaretaker::~VvCaretaker() {
    calmDown();
}

