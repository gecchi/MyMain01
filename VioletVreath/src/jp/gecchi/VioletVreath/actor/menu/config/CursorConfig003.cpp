#include "CursorConfig003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CursorConfig003::CursorConfig003(const char* prm_name) : DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "CursorConfig003";
}

void CursorConfig003::initialize() {
    getUvFlipper()->exec(FLIP_OSCILLATE_LOOP, 10);
}

void CursorConfig003::onActive() {
    setAlpha(0.0);
    getAlphaFader()->transitionLinearToTop(60);
}

void CursorConfig003::processBehavior() {
    getUvFlipper()->behave();
    getAlphaFader()->behave();
}

void CursorConfig003::processJudgement() {
}

CursorConfig003::~CursorConfig003() {
}
