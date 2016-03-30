#include "PauseCamWorker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

PauseCamWorker::PauseCamWorker(const char* prm_name, Camera* prm_pCamera) : AroundViewCamWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "PauseCamWorker";
//    pVPGuide_ = createInFactory(ViewPointGuide, "VPGuide");
}

PauseCamWorker::~PauseCamWorker() {
}
