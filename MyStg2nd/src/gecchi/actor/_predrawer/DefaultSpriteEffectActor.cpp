#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultSpriteEffectActor::DefaultSpriteEffectActor(const char* prm_name) : DefaultSpriteActor(prm_name, "_chk_DefaultSpriteEffectTest") {
    _class_name = "DefaultSpriteEffectActor";
    setHitAble(false);
}

DefaultSpriteEffectActor::~DefaultSpriteEffectActor() {
}

