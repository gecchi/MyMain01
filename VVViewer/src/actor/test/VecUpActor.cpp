#include "VecUpActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"

#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;


VecUpActor::VecUpActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "VecUp") {
    up_face_no_ = TN(0,1,0);
    up_face_no_prev_ = -1;
}

void VecUpActor::initialize() {
    setScaleR(3.0);
}

void VecUpActor::processBehavior() {
    if(up_face_no_ != up_face_no_prev_) {
        float vx,vy,vz;
        GgafDxDirectionUtil::cnvFaceNo2Vec(up_face_no_, vx, vy, vz);
        getKuroko()->asstB()->turnFaceAngByVdTwd(
                D_ANG(2),
                vx * PX_C(100), vy * PX_C(100), vz* PX_C(100), TURN_CLOSE_TO, true,
                0.3, 0.7, 0, true);
    }
    getKuroko()->behave();
    up_face_no_prev_ = up_face_no_;
}

VecUpActor::~VecUpActor() {
}
