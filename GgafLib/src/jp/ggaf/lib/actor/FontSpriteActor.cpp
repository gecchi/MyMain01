#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontSpriteActor::FontSpriteActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        DefaultSpriteActor(prm_name, prm_model, prm_pStat) {
    _class_name = "FontSpriteActor";
}

FontSpriteActor::~FontSpriteActor() {
}
