#include "DefaultD3DXMeshTestActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultD3DXMeshTestActor::DefaultD3DXMeshTestActor(const char* prm_name) :
        DefaultD3DXMeshActor(prm_name, "_chk_DefaultD3DXMeshTestModel", nullptr) {
    _class_name = "DefaultD3DXMeshTestActor";
    setHitAble(false);
}

DefaultD3DXMeshTestActor::~DefaultD3DXMeshTestActor() {
}

