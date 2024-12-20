#include "LabelMenuItemFont01.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"

using namespace GgafLib;
using namespace VioletVreath;

LabelMenuItemFont01::LabelMenuItemFont01(const char* prm_name) :
        FontBoardActor(prm_name, "MenuItemFont01") {
    _class_name = "LabelMenuItemFont01";
}

void LabelMenuItemFont01::onCreateModel() {
}

void LabelMenuItemFont01::initialize() {
}

void LabelMenuItemFont01::onActive() {
    getAlphaFader()->setRange(0.0, 1.0);
    setAlpha(0.0);
    getAlphaFader()->transitionLinearToTop(60);
}

void LabelMenuItemFont01::onUpdate() {
    getAlphaFader()->setRange(0.0, 1.0);
    setAlpha(0.0);
    getAlphaFader()->beat(15, 5, 5, 5, 3.5);
}

void LabelMenuItemFont01::processBehavior() {
    getAlphaFader()->behave();
}

LabelMenuItemFont01::~LabelMenuItemFont01() {
}

