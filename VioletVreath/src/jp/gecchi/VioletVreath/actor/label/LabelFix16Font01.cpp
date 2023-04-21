#include "LabelFix16Font01.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"



using namespace GgafLib;
using namespace VioletVreath;

LabelFix16Font01::LabelFix16Font01(const char* prm_name) :
        FontBoardActor(prm_name, "MSX_16Font")
{
    _class_name = "LabelFix16Font01";
}

void LabelFix16Font01::onCreateModel() {
}

void LabelFix16Font01::initialize() {
    addModel("Ranking_16Font");
}

void LabelFix16Font01::processBehavior() {
    getAlphaFader()->behave();
}

void LabelFix16Font01::dispDefaultFont() {
    changeModelByIndex(0);
}

void LabelFix16Font01::dispChangesFont() {
    changeModelByIndex(1);
}

LabelFix16Font01::~LabelFix16Font01() {
}

