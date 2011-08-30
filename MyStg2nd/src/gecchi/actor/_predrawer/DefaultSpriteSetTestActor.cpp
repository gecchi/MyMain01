#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultSpriteSetTestActor::DefaultSpriteSetTestActor(const char* prm_name) :
        DefaultSpriteSetActor(prm_name, "_chk_DefaultSpriteSetEffectTest", NULL) {
    _class_name = "DefaultSpriteSetTestActor";
    setHitAble(false);
}

DefaultSpriteSetTestActor::~DefaultSpriteSetTestActor() {
}

