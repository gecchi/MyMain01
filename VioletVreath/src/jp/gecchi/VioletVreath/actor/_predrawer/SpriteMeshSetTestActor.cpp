#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


SpriteMeshSetTestActor::SpriteMeshSetTestActor(const char* prm_name) :
        SpriteMeshSetActor(prm_name, "_chk_DefaultMeshSetTestModel", nullptr) {
    _class_name = "DefaultMeshSetTestActor";
    setHitAble(false);
}

SpriteMeshSetTestActor::~SpriteMeshSetTestActor() {
}

