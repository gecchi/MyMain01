#include "jp/ggaf/lib/manager/CameraWorkerManager.h"

#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/actor/camera/worker/DefaultCamWorker.h"
#include "jp/ggaf/lib/manager/CameraWorkerConnection.h"
#include "jp/ggaf/lib/actor/camera/CameraWorkerChanger.h"

using namespace GgafLib;

CameraWorkerManager::CameraWorkerManager(const char* prm_manager_name, CameraWorkerChanger* prm_pCameraWorkerChanger) :
    GgafCore::ResourceManager<CameraWorker> (prm_manager_name) {
    _pCameraWorkerChanger = prm_pCameraWorkerChanger;
}

CameraWorker* CameraWorkerManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    CameraWorker* pResource = nullptr;
    if (strcmp("DefaultCamWorker", prm_idstr) == 0) {
        //デフォルトの何もしないカメラマン
        pResource = NEW DefaultCamWorker("DefaultCamWorker", _pCameraWorkerChanger->_pCamera);
    } else {
        pResource = _pCameraWorkerChanger->createCameraWorker(prm_idstr, prm_pConnector);
    }
    return pResource;
}

GgafCore::ResourceConnection<CameraWorker>* CameraWorkerManager::processCreateConnection(const char* prm_idstr, CameraWorker* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    CameraWorkerConnection* pConne = NEW CameraWorkerConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}
