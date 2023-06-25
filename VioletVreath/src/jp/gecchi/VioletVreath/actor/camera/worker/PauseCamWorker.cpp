#include "PauseCamWorker.h"



using namespace GgafLib;
using namespace VioletVreath;

PauseCamWorker::PauseCamWorker(const char* prm_name, Camera* prm_pCamera)
  : AroundViewCamWorker(prm_name, (DefaultCamera*)prm_pCamera, 8, 0.2, 0.8) {
    _class_name = "PauseCamWorker";
//    pVPGuide_ = desireActor(ViewPointGuide, "VPGuide");
}

PauseCamWorker::~PauseCamWorker() {
}
