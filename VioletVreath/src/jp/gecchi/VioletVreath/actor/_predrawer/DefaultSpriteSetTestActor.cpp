#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


DefaultSpriteSetTestActor::DefaultSpriteSetTestActor(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "_chk_DefaultSpriteSetTestModel", nullptr) {
    _class_name = "DefaultSpriteSetTestActor";
    setHitAble(false);
}

DefaultSpriteSetTestActor::~DefaultSpriteSetTestActor() {
}

