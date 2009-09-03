#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultSpriteEnemyActor::DefaultSpriteEnemyActor(const char* prm_name, const char* prm_model) : DefaultSpriteSetActor(prm_name, prm_model) {
    _class_name = "DefaultSpriteEnemyActor";
}

DefaultSpriteEnemyActor::~DefaultSpriteEnemyActor() {
}
