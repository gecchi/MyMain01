#ifndef CAMERAWORKERMANAGER_H_
#define CAMERAWORKERMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * CameraWorker 管理クラス .
 * 生成済み CameraWorker オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CameraWorkerManager : public GgafCore::ResourceManager<GgafLib::CameraWorker> {

public:
    CameraWorkerManager(const char* prm_manager_name);

    GgafLib::CameraWorker* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<GgafLib::CameraWorker>* processCreateConnection(const char* prm_idstr, GgafLib::CameraWorker* prm_pResource) override;

    virtual ~CameraWorkerManager() {
    }
};

}
#endif /*CAMERAWORKERMANAGER_H_*/
