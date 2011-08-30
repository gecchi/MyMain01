#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

StringBoardTestActor::StringBoardTestActor(const char* prm_name) :
        StringBoardActor(prm_name, "_chk_StringBoardEffectTest", NULL) {

    _class_name = "StringBoardTestActor";
}

void StringBoardTestActor::processBehavior() {
}

StringBoardTestActor::~StringBoardTestActor() {
}

