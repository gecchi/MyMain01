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

    position(0,0,0);
}
void DefaultMeshTestActor::processBehavior() {
    if (GgafDxInput::isBeingPressedKey(DIK_O)) {
        _x += PX_C(1);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_L)) {
        _x -= PX_C(1);
    }
}

void DefaultMeshTestActor::processJudgement() {
    //_TRACE_((-_dest_from_vppln_front)<<"\t"<<_now_drawdepth<<"\t"<<"("<<_x<<","<<_y<<","<<_z<<")");
}
DefaultMeshTestActor::~DefaultMeshTestActor() {
}

