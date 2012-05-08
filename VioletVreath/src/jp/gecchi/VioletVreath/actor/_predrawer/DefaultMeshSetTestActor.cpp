#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


DefaultMeshSetTestActor::DefaultMeshSetTestActor(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "_chk_DefaultMeshTestModel", NULL) {
    _class_name = "DefaultMeshSetTestActor";
    setHitAble(false);
}

DefaultMeshSetTestActor::~DefaultMeshSetTestActor() {
}

