#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


LaserChipEffectActor::LaserChipEffectActor(const char* prm_name) : StraightLaserChip(prm_name, "12/MyCurveLaserChip001") {
    _class_name = "LaserChipEffectActor";
    setHitAble(false);
}

LaserChipEffectActor::~LaserChipEffectActor() {
}

