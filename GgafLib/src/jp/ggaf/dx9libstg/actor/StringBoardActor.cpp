#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

StringBoardActor::StringBoardActor(const char* prm_name, const char* prm_model) :
        GgafDx9StringBoardActor(prm_name, prm_model)
{
    _class_name = "StringBoardActor";
}

StringBoardActor::~StringBoardActor() {
}

