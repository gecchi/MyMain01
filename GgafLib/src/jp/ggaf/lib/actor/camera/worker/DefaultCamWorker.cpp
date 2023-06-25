#include "jp/ggaf/lib/actor/camera/worker/DefaultCamWorker.h"

using namespace GgafLib;

DefaultCamWorker::DefaultCamWorker(const char* prm_name, DefaultCamera* prm_pCamera,
        frame prm_slide_frames, double prm_slide_p1, double prm_slide_p2)
            : CameraWorker(prm_name, prm_pCamera,
                           prm_slide_frames, prm_slide_p1, prm_slide_p2) {
    _class_name = "DefaultCamWorker";
}

void DefaultCamWorker::processBehavior()  {
}

DefaultCamWorker::~DefaultCamWorker() {
}
