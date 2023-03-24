#ifndef GGAF_LIB_AMERAWORKERCONNECTION_H_
#define GGAF_LIB_AMERAWORKERCONNECTION_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

namespace GgafLib {

/**
 * CameraWorkerコネクション.
 * @version 1.00
 * @since 2019/03/22
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
#endif /*GGAF_LIB_AMERAWORKERCONNECTION_H_*/
