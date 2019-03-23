#include "VVCameraWorkerChanger.h"

#include "Camera.h"
#include "worker/MyShipDivingCamWorker.h"
#include "worker/PauseCamWorker.h"
#include "worker/TestCamWorker.h"
#include "worker/VamSysCamWorker.h"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"
#include "jp/ggaf/core/exception/CriticalException.h"

using namespace VioletVreath;

VVCameraWorkerChanger::VVCameraWorkerChanger(const char* prm_name, Camera* prm_pCamera) :
        GgafLib::CameraWorkerChanger(prm_name, prm_pCamera) {
}

GgafLib::CameraWorker* VVCameraWorkerChanger::createCameraWorker(const char* prm_idstr, void* prm_pConnector) {
    GgafLib::CameraWorker* pResource = nullptr;

    Camera* pCamera = (Camera*)prm_pConnector;

//    if (strcmp("DefaultCamWorker", prm_idstr) == 0) {
//        pResource = NEW DefaultCamWorker("DefaultCamWorker", pCamera);
//    }
    if (strcmp("VamSysCamWorker", prm_idstr) == 0) {
        pResource = NEW VamSysCamWorker("VamSysCamWorker", pCamera);
    }
    if (strcmp("PauseCamWorker", prm_idstr) == 0) {
        pResource = NEW PauseCamWorker("PauseCamWorker", pCamera);
    }

    if (strcmp("TestCamWorker", prm_idstr) == 0) {
        pResource = NEW TestCamWorker("TestCamWorker", pCamera);
    }

    if (strcmp("MyShipDivingCamWorker", prm_idstr) == 0) {
        pResource = NEW MyShipDivingCamWorker("MyShipDivingCamWorker", pCamera);
    }

    if (pResource == nullptr) {
        throwCriticalException("想定外のIDです。CameraWorkerが作成できません。");
    }

    pResource->inactivate();
    return pResource;
}
VVCameraWorkerChanger::~VVCameraWorkerChanger() {
}
