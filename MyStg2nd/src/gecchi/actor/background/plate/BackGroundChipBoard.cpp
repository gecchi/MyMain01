#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGroundChipBoard::BackGroundChipBoard(const char* prm_name, const char* prm_model) : DefaultBoardActor(prm_name, prm_model, "DefaultBoardTechnique") {
    _class_name = "BackGroundChipBoard";
}

BackGroundChipBoard::~BackGroundChipBoard() {
}
