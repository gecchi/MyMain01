#include "jp/ggaf/lib/actor/camera/worker/DefaultCamWorker.h"

using namespace GgafLib;

DefaultCamWorker::DefaultCamWorker(const char* prm_name, DefaultCamera* prm_pCamera) : CameraWorker(prm_name, prm_pCamera) {
    _class_name = "DefaultCamWorker";
}

void DefaultCamWorker::processBehavior()  {
}

DefaultCamWorker::~DefaultCamWorker() {
}
