#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

StringBoardEffectActor::StringBoardEffectActor(const char* prm_name) :
        StringBoardActor(prm_name, "Gecchi_8Font")
{
    _class_name = "StringBoardEffectActor";
}

void StringBoardEffectActor::processBehavior() {
}

StringBoardEffectActor::~StringBoardEffectActor() {
}

