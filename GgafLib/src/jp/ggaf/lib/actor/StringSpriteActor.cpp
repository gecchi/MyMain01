#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StringSpriteActor::StringSpriteActor(const char* prm_name, const char* prm_model , GgafStatus* prm_pStat) :
        GgafDxStringSpriteActor(prm_name, prm_model, prm_pStat)         //prm_pStat–³Ž‹
{
    _class_name = "StringSpriteActor";
}

StringSpriteActor::~StringSpriteActor() {
}

