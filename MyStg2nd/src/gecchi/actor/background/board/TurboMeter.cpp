#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TurboMeter::TurboMeter(const char* prm_name) : DefaultBoardSetActor(prm_name, "5/TurboMeter") {
    _class_name = "TurboMeter";
    //_z = 0.99;//ÇΩÇ‘ÇÒç≈îwñ  Åi0 <= _z < 1.0ÅjZ=(0Å`+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
}

TurboMeter::~TurboMeter() {
}
