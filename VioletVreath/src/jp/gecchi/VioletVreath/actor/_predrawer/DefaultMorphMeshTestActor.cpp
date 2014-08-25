#include "DefaultMorphMeshTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultMorphMeshTestActor::DefaultMorphMeshTestActor(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "0/_chk_DefaultMorphMeshTestModel", nullptr) {
    _class_name = "DefaultMorphMeshTestActor";
    setHitAble(false);
}

DefaultMorphMeshTestActor::~DefaultMorphMeshTestActor() {
}

