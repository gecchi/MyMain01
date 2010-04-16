#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGroundChipBoard::BackGroundChipBoard(const char* prm_name, const char* prm_model) : DefaultBoardSetActor(prm_name, prm_model) {
    _class_name = "BackGroundChipBoard";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0〜+1)
    _z = 0.9999999f;
}

BackGroundChipBoard::~BackGroundChipBoard() {
}
