#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


DefaultSpriteTestActor::DefaultSpriteTestActor(const char* prm_name) : DefaultSpriteActor(prm_name, "_chk_DefaultSpriteEffectTest") {
    _class_name = "DefaultSpriteTestActor";
    setHitAble(false);
}

DefaultSpriteTestActor::~DefaultSpriteTestActor() {
}

