#include "LabelFont32x64.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"

using namespace GgafLib;
using namespace VioletVreath;

LabelFont32x64::LabelFont32x64(const char* prm_name) :
        FontBoardActor(prm_name, "Font32x64")
{
    _class_name = "LabelFont32x64";
}

void LabelFont32x64::onCreateModel() {
}

void LabelFont32x64::initialize() {
}

void LabelFont32x64::processBehavior() {
    getAlphaFader()->behave();
}

LabelFont32x64::~LabelFont32x64() {
}

