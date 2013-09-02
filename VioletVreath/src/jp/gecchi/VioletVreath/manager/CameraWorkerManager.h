#ifndef CAMERAWORKERMANAGER_H_
#define CAMERAWORKERMANAGER_H_
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/gecchi/VioletVreath/actor/camera_worker/CameraWorker.h"

namespace VioletVreath {

/**
 * CameraWorker 管理クラス .
 * 生成済み CameraWorker オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CameraWorkerManager : public GgafCore::GgafResourceManager<CameraWorker> {

public:
    CameraWorkerManager(const char* prm_manager_name);

    CameraWorker* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<CameraWorker>* processCreateConnection(char* prm_idstr, CameraWorker* prm_pResource) override;

    virtual ~CameraWorkerManager() {
    }
};

}
#endif /*CAMERAWORKERMANAGER_H_*/
