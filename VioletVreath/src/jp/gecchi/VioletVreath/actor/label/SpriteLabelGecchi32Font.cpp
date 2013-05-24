#include "stdafx.h"
#include "SpriteLabelGecchi32Font.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteLabelGecchi32Font::SpriteLabelGecchi32Font(const char* prm_name) :
        StringSpriteActor(prm_name, "Gecchi_32Font")
{
    _class_name = "SpriteLabelGecchi32Font";
}

void SpriteLabelGecchi32Font::onCreateModel() {
}

void SpriteLabelGecchi32Font::initialize() {
    setAlpha(0.9);
}

void SpriteLabelGecchi32Font::processBehavior() {
}

SpriteLabelGecchi32Font::~SpriteLabelGecchi32Font() {
}

