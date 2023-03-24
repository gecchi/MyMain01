#ifndef GGAF_LIB_CAMERAWORKERMANAGER_H_
#define GGAF_LIB_CAMERAWORKERMANAGER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/ResourceManager.hpp"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

namespace GgafLib {

/**
 * CameraWorker 管理クラス .
 * 生成済み CameraWorker オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2019/03/22
 * @author Masatoshi Tsuge
 */
class CameraWorkerManager : public GgafCore::ResourceManager<CameraWorker> {

    CameraWorkerChanger* _pCameraWorkerChanger;

public:
    CameraWorkerManager(const char* prm_manager_name, CameraWorkerChanger* prm_pCameraWorkerChanger);

    virtual CameraWorker* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<CameraWorker>* processCreateConnection(const char* prm_idstr, CameraWorker* prm_pResource) override;

    virtual ~CameraWorkerManager() {
    }
};

}
#endif /*GGAF_LIB_CAMERAWORKERMANAGER_H_*/
