#include "CameraWorkerManager.h"

#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/DefaultCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/PauseCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/TestCamWorker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraWorkerManager::CameraWorkerManager(const char* prm_manager_name) :
    GgafResourceManager<CameraWorker> (prm_manager_name) {
}

CameraWorker* CameraWorkerManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    CameraWorker* pResource = nullptr;

    if (strcmp("DefaultCamWorker", prm_idstr) == 0) {
        pResource = NEW DefaultCamWorker("DefaultCamWorker");
    }

    if (strcmp("VamSysCamWorker", prm_idstr) == 0) {
        pResource = NEW VamSysCamWorker("VamSysCamWorker");
    }

    if (strcmp("PauseCamWorker", prm_idstr) == 0) {
        pResource = NEW PauseCamWorker("PauseCamWorker");
    }

    if (strcmp("TestCamWorker", prm_idstr) == 0) {
        pResource = NEW TestCamWorker("TestCamWorker");
    }

    if (strcmp("MyShipDivingCamWorker", prm_idstr) == 0) {
        pResource = NEW MyShipDivingCamWorker("MyShipDivingCamWorker");
    }

    if (pResource == nullptr) {
        throwGgafCriticalException("CameraWorkerManager::processCreateResource("<<prm_idstr<<") �z��O��ID�ł��BCameraWorker���쐬�ł��܂���B");
    }

    pResource->inactivate();
    return pResource;
}

GgafResourceConnection<CameraWorker>* CameraWorkerManager::processCreateConnection(const char* prm_idstr, CameraWorker* prm_pResource) {
    _TRACE3_(" CameraWorkerManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    CameraWorkerConnection* pConne = NEW CameraWorkerConnection(prm_idstr, prm_pResource);
    _TRACE3_(" CameraWorkerManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}
