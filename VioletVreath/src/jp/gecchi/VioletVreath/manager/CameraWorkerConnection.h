#ifndef CAMERAWORKERCONNECTION_H_
#define CAMERAWORKERCONNECTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

namespace VioletVreath {

/**
 * CameraWorkerコネクション.
 * @version 1.00
 * @since 2009/01/30
 * @author Masatoshi Tsuge
 */
class CameraWorkerConnection : public GgafCore::ResourceConnection<GgafLib::CameraWorker> {

public:
    /**
     * コンストラクタ<BR>
     * @param prm_idstr 識別名
     * @param prm_pCamWorker デポジトリ
     */
    CameraWorkerConnection(const char* prm_idstr, GgafLib::CameraWorker* prm_pCamWorker);

    void processReleaseResource(GgafLib::CameraWorker* prm_pResource);

    virtual ~CameraWorkerConnection() {
    }
};

}
#endif /*DEPOSITORYCONNECTION_H_*/
