#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


DefaultSpriteSetTestActor::DefaultSpriteSetTestActor(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "_chk_DefaultSpriteSetTestModel", NULL) {
    _class_name = "DefaultSpriteSetTestActor";
    setHitAble(false);
}

DefaultSpriteSetTestActor::~DefaultSpriteSetTestActor() {
}

