#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultSpriteSetEffectActor::DefaultSpriteSetEffectActor(const char* prm_name) : DefaultSpriteSetActor(prm_name, "DefaultSpriteSetEffectTest") {
    _class_name = "DefaultSpriteSetEffectActor";
    setHitAble(false);
}

DefaultSpriteSetEffectActor::~DefaultSpriteSetEffectActor() {
}

