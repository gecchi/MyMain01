#include "SpriteFont32x64.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SpriteFont32x64::SpriteFont32x64(const char* prm_name) :
        FontSpriteActor(prm_name, "Font32x64")
{
    _class_name = "SpriteFont32x64";
}

void SpriteFont32x64::onCreateModel() {
}

void SpriteFont32x64::initialize() {
    setAlpha(0.9);
}

void SpriteFont32x64::processBehavior() {
}

SpriteFont32x64::~SpriteFont32x64() {
}

