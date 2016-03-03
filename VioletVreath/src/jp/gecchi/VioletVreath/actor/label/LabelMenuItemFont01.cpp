#include "LabelMenuItemFont01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LabelMenuItemFont01::LabelMenuItemFont01(const char* prm_name) :
        FontBoardActor(prm_name, "MenuItemFont01") {
    _class_name = "LabelMenuItemFont01";
    _pAFader = NEW GgafDxAlphaFader(this);
}

void LabelMenuItemFont01::onCreateModel() {
}

void LabelMenuItemFont01::initialize() {
}

void LabelMenuItemFont01::onActive() {
    _pAFader->setRange(0.0, 1.0);
    setAlpha(0.0);
    _pAFader->transitionLinerToTop(60);
}

void LabelMenuItemFont01::onUpdate() {
    _pAFader->setRange(0.0, 1.0);
    setAlpha(0.0);
    _pAFader->beat(15, 5, 5, 5, 3.5);
}

void LabelMenuItemFont01::processBehavior() {
    _pAFader->behave();
}

LabelMenuItemFont01::~LabelMenuItemFont01() {
    GGAF_DELETE(_pAFader);
}

