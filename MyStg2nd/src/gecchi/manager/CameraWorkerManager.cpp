#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CameraWorkerManager::CameraWorkerManager(const char* prm_manager_name) :
    GgafResourceManager<CameraWorker> (prm_manager_name) {
}

CameraWorker* CameraWorkerManager::processCreateResource(char* prm_idstr) {
    CameraWorker* pResource = NULL;

    if (GgafUtil::strcmp_ascii("DefaultCamWorker", prm_idstr) == 0) {
        pResource = NEW DefaultCamWorker("DefaultCamWorker");
    }

    if (GgafUtil::strcmp_ascii("VamSysCamWorker", prm_idstr) == 0) {
        pResource = NEW VamSysCamWorker("VamSysCamWorker");
    }

    if (GgafUtil::strcmp_ascii("PauseCamWorker", prm_idstr) == 0) {
        pResource = NEW PauseCamWorker("PauseCamWorker");
    }

    if (pResource == NULL) {
        throwGgafCriticalException("CameraWorkerManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。CameraWorkerが作成できません。");
    } else {
        return pResource;
    }
}

GgafResourceConnection<CameraWorker>* CameraWorkerManager::processCreateConnection(char* prm_idstr, CameraWorker* prm_pResource) {
    TRACE3(" CameraWorkerManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    CameraWorkerConnection* pConnection = NEW CameraWorkerConnection(prm_idstr, prm_pResource);
    TRACE3(" CameraWorkerManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}
