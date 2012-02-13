#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


DefaultSpriteTestActor::DefaultSpriteTestActor(const char* prm_name) :
        DefaultSpriteActor(prm_name, "_chk_DefaultSpriteTestModel", NULL) {
    _class_name = "DefaultSpriteTestActor";
    setHitAble(false);
}

DefaultSpriteTestActor::~DefaultSpriteTestActor() {
}

