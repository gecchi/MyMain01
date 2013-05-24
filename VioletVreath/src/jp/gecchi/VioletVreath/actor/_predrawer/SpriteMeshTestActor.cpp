#include "stdafx.h"
#include "SpriteMeshTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


SpriteMeshTestActor::SpriteMeshTestActor(const char* prm_name) :
        SpriteMeshActor(prm_name, "_chk_SpriteMeshTestModel", nullptr) {
    _class_name = "SpriteMeshTestActor";
    setHitAble(false);
}

SpriteMeshTestActor::~SpriteMeshTestActor() {
}

