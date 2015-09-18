#include "DefaultCamWorker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

DefaultCamWorker::DefaultCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "DefaultCamWorker";
}

void DefaultCamWorker::processBehavior()  {
    targetAutoCamup();
}

DefaultCamWorker::~DefaultCamWorker() {
}
