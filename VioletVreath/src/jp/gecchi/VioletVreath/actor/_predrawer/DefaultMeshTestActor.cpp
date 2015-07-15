#include "DefaultMeshTestActor.h"

#include "jp/ggaf/dxcore/util/GgafDxInput.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultMeshTestActor::DefaultMeshTestActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "_chk_DefaultMeshTestModel", nullptr) {
    _class_name = "DefaultMeshTestActor";
    setHitAble(false);
}

void DefaultMeshTestActor::processBehavior() {
}

void DefaultMeshTestActor::processJudgement() {
}

DefaultMeshTestActor::~DefaultMeshTestActor() {
}

