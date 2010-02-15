#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TruboMeter::TruboMeter(const char* prm_name, const char* prm_model) : DefaultBoardSetActor(prm_name, prm_model) {
    _class_name = "TruboMeter";
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0〜+1)
    //_z = 0.9999999f;
    _z = 0.00000001f;
}

TruboMeter::~TruboMeter() {
}
