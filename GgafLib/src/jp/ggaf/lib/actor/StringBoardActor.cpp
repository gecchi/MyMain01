#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

StringBoardActor::StringBoardActor(const char* prm_name, const char* prm_model , GgafStatus* prm_pStat) :
        GgafDxStringBoardActor(prm_name, prm_model)         //prm_pStat–³Ž‹
{
    _class_name = "StringBoardActor";
}

StringBoardActor::~StringBoardActor() {
}

