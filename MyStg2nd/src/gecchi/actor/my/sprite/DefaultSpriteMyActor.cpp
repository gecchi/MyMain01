#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultSpriteMyActor::DefaultSpriteMyActor(const char* prm_name, const char* prm_model, const char* prm_technique) : DefaultSpriteActor(prm_name, prm_model, prm_technique) {
    _class_name = "DefaultSpriteMyActor";
}

DefaultSpriteMyActor::~DefaultSpriteMyActor() {
}
