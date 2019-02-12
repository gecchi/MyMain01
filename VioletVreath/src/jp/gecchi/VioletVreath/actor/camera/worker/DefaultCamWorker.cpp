#include "DefaultCamWorker.h"



using namespace GgafLib;
using namespace VioletVreath;

DefaultCamWorker::DefaultCamWorker(const char* prm_name, Camera* prm_pCamera) : CameraWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "DefaultCamWorker";
}

void DefaultCamWorker::processBehavior()  {
//    targetAutoCamup();
}

DefaultCamWorker::~DefaultCamWorker() {
}
