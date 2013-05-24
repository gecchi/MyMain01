#include "stdafx.h"
#include "LaserChipTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


LaserChipTestActor::LaserChipTestActor(const char* prm_name) :
        StraightLaserChip(prm_name, "_chk_LaserChipTestModel", nullptr) {
    _class_name = "LaserChipTestActor";
    setHitAble(false);
}

LaserChipTestActor::~LaserChipTestActor() {
}

