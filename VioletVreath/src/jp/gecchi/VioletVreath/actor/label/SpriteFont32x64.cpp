#include "SpriteFont32x64.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"



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
    setCullingDraw(false);
}

void SpriteFont32x64::processBehavior() {
}

SpriteFont32x64::~SpriteFont32x64() {
}

