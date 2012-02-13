#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


LaserChipTestActor::LaserChipTestActor(const char* prm_name) :
        StraightLaserChip(prm_name, "_chk_LaserChipTestModel", NULL) {
    _class_name = "LaserChipTestActor";
    setHitAble(false);
}

LaserChipTestActor::~LaserChipTestActor() {
}

