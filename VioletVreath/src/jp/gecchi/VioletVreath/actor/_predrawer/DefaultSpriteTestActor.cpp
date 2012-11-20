#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


DefaultSpriteTestActor::DefaultSpriteTestActor(const char* prm_name) :
        DefaultSpriteActor(prm_name, "_chk_DefaultSpriteTestModel", nullptr) {
    _class_name = "DefaultSpriteTestActor";
    setHitAble(false);
}

DefaultSpriteTestActor::~DefaultSpriteTestActor() {
}

