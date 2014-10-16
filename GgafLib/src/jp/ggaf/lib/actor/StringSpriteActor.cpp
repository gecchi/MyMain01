#include "jp/ggaf/lib/actor/StringSpriteActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StringSpriteActor::StringSpriteActor(const char* prm_name, const char* prm_model , GgafStatus* prm_pStat) :
        GgafDxStringSpriteActor(prm_name, prm_model,256, prm_pStat)
{
    _class_name = "StringSpriteActor";
}
StringSpriteActor::StringSpriteActor(const char* prm_name, const char* prm_model, int prm_max_len , GgafStatus* prm_pStat) :
        GgafDxStringSpriteActor(prm_name, prm_model, prm_max_len, prm_pStat)
{
    _class_name = "StringSpriteActor";
}

StringSpriteActor::~StringSpriteActor() {
}

