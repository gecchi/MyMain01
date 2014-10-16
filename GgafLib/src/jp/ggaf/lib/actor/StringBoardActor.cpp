#include "jp/ggaf/lib/actor/StringBoardActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StringBoardActor::StringBoardActor(const char* prm_name, const char* prm_model) :
        GgafDxStringBoardActor(prm_name, prm_model, 1024)
{
    _class_name = "StringBoardActor";
}

StringBoardActor::StringBoardActor(const char* prm_name, const char* prm_model, int prm_max_len) :
        GgafDxStringBoardActor(prm_name, prm_model, prm_max_len)
{
    _class_name = "StringBoardActor";
}

StringBoardActor::~StringBoardActor() {
}

