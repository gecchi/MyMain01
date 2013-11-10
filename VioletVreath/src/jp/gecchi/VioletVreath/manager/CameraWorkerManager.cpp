#include "stdafx.h"
#include "CameraWorkerManager.h"

#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/DefaultCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/PauseCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/TestCamWorker.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraWorkerManager::CameraWorkerManager(const char* prm_manager_name) :
    GgafResourceManager<CameraWorker> (prm_manager_name) {
}

CameraWorker* CameraWorkerManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    CameraWorker* pResource = nullptr;

    if (UTIL::strcmp_ascii("DefaultCamWorker", prm_idstr) == 0) {
        pResource = NEW DefaultCamWorker("DefaultCamWorker");
    }

    if (UTIL::strcmp_ascii("VamSysCamWorker", prm_idstr) == 0) {
        pResource = NEW VamSysCamWorker("VamSysCamWorker");
    }

    if (UTIL::strcmp_ascii("PauseCamWorker", prm_idstr) == 0) {
        pResource = NEW PauseCamWorker("PauseCamWorker");
    }

    if (UTIL::strcmp_ascii("TestCamWorker", prm_idstr) == 0) {
        pResource = NEW TestCamWorker("TestCamWorker");
    }

    if (UTIL::strcmp_ascii("MyShipDivingCamWorker", prm_idstr) == 0) {
        pResource = NEW MyShipDivingCamWorker("MyShipDivingCamWorker");
    }

    if (pResource == nullptr) {
        throwGgafCriticalException("CameraWorkerManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。CameraWorkerが作成できません。");
    }

    pResource->inactivate();
    return pResource;
}

GgafResourceConnection<CameraWorker>* CameraWorkerManager::processCreateConnection(char* prm_idstr, CameraWorker* prm_pResource) {
    TRACE3(" CameraWorkerManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    CameraWorkerConnection* pConne = NEW CameraWorkerConnection(prm_idstr, prm_pResource);
    TRACE3(" CameraWorkerManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}
