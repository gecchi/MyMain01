#include "VvvCamWorker.h"

using namespace GgafLib;
using namespace VVViewer;

VvvCamWorker::VvvCamWorker(const char* prm_name, VvvCamera* prm_pCamera)
  : AroundViewCamWorker(prm_name, (DefaultCamera*)prm_pCamera, 5, 0.3, 0.7) {
    _class_name = "VvvCamWorker";
}

VvvCamWorker::~VvvCamWorker() {
}
