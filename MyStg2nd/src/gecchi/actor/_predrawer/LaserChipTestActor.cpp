#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChipTestActor::LaserChipTestActor(const char* prm_name) :
        StraightLaserChip(prm_name, "_chk_LaserChipEffectTest", NULL) {
    _class_name = "LaserChipTestActor";
    setHitAble(false);
}

LaserChipTestActor::~LaserChipTestActor() {
}

