#include "LabelFont16x32.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"

using namespace GgafLib;
using namespace VioletVreath;

LabelFont16x32::LabelFont16x32(const char* prm_name) :
        FontBoardActor(prm_name, "Font16x32")
{
    _class_name = "LabelFont16x32";
}

void LabelFont16x32::onCreateModel() {
}

void LabelFont16x32::initialize() {
}

void LabelFont16x32::processBehavior() {
    getAlphaFader()->behave();
}

LabelFont16x32::~LabelFont16x32() {
}

