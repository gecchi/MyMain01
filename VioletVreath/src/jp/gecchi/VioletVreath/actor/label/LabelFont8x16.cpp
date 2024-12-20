#include "LabelFont8x16.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"

using namespace GgafLib;
using namespace VioletVreath;

LabelFont8x16::LabelFont8x16(const char* prm_name) :
        FontBoardActor(prm_name, "Font8x16")
{
    _class_name = "LabelFont8x16";
}

void LabelFont8x16::onCreateModel() {
}

void LabelFont8x16::initialize() {
}

void LabelFont8x16::processBehavior() {
    getAlphaFader()->behave();
}

LabelFont8x16::~LabelFont8x16() {
}

