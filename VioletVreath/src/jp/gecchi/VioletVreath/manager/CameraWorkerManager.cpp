#include "CameraWorkerManager.h"

#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/DefaultCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/PauseCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/TestCamWorker.h"



using namespace GgafLib;
using namespace VioletVreath;

CameraWorkerManager::CameraWorkerManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<CameraWorker> (prm_manager_name) {
}

CameraWorker* CameraWorkerManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    CameraWorker* pResource = nullptr;

    Camera* pCamera = (Camera*)prm_pConnector;

    if (strcmp("DefaultCamWorker", prm_idstr) == 0) {
        pResource = NEW DefaultCamWorker("DefaultCamWorker", pCamera);
    }
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

GgafCore::ResourceConnection<CameraWorker>* CameraWorkerManager::processCreateConnection(const char* prm_idstr, CameraWorker* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    CameraWorkerConnection* pConne = NEW CameraWorkerConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}
